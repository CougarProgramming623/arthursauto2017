#include "Turn.h"
#include "AHRS.h"
#include "../RobotMap.h"

const static double kP = RobotMap::turnP;
const static double kI = RobotMap::turnI;
const static double kD = RobotMap::turnD;
const static double kF = 0.00f;

/* This tuning parameter indicates how close to "on target" the    */
/* PID Controller will attempt to get.                             */

const static double kToleranceDegrees = RobotMap::toleranceDegrees;

Turn::Turn(double setpoint) :
		Command() {
	m_angle = setpoint;
	Requires(Robot::subsystemDrive.get());
}

// Called just before this Command runs the first time
void Turn::Initialize() {
	rotateToAngleRate = 0.0f;
	try {
		/* Communicate w/navX-MXP via the MXP SPI Bus.                                       */
		/* Alternatively:  I2C::Port::kMXP, SerialPort::Port::kMXP or SerialPort::Port::kUSB */
		/* See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface/ for details.   */

		RobotMap::ahrs->ZeroYaw();
		//initialAngle = RobotMap::ahrs->GetYaw();

		//DriverStation::ReportError("First time:"+std::to_string(initialAngle)+" "+std::to_string(m_angle));

	} catch (std::exception ex) {
		std::string err_string = "Error instantiating navX-MXP:  ";
		err_string += ex.what();
		//DriverStation::ReportError(err_string.c_str());
	}

	turnController = new PIDController(RobotMap::turnP, RobotMap::turnI, RobotMap::turnD, kF, RobotMap::ahrs, this);
	turnController->SetInputRange(-180.0f, 180.0f);
	turnController->SetOutputRange(-0.75, 0.75);
	turnController->SetAbsoluteTolerance(RobotMap::toleranceDegrees);
	turnController->SetContinuous(true);

	turnController->SetSetpoint(m_angle);
	turnController->Enable();

//  SetTimeout(5*1000);
	turnTimer = new Timer();
	turnTimer->Start();
}

// Called repeatedly when this Command is scheduled to run
void Turn::Execute() {
	//ahrs->ZeroYaw();
	double finishAngle = RobotMap::ahrs->GetYaw();
	DriverStation::ReportError("running:"+ std::to_string(finishAngle));

	double currentRotationRate = rotateToAngleRate;
	/*if (abs(finishAngle - m_angle) <= 10) {
	 currentRotationRate = 0.3;
	 } else {
	 currentRotationRate = 0.3;
	 }*/
	//if (m_angle < 0) {
		//Robot::subsystemDrive->ArcadeDrive(0, -currentRotationRate, true);
	//} else {
		//DriverStation::ReportError("current rot rate: " + std::to_string(currentRotationRate));
		Robot::subsystemDrive->ArcadeDrive(0, currentRotationRate, true);
	//}
	SmartDashboard::PutNumber("Current Rotation Rate: ", currentRotationRate);
	SmartDashboard::PutNumber("Finish Angle: ", finishAngle);
	SmartDashboard::PutNumber("P: ", RobotMap::turnP);
	SmartDashboard::PutNumber("I: ", RobotMap::turnI);
	SmartDashboard::PutNumber("D: ", RobotMap::turnD);
}

// Make this return true when this Command no longer needs to run execute()
bool Turn::IsFinished() {
/*	double angle = RobotMap::ahrs->GetYaw();
	double difference = m_angle - angle;
	DriverStation::ReportError("angle: " + std::to_string(angle));
	if (m_angle > 0 && difference <= 0) {
		return true;
	}
	if (m_angle <= 0 && difference >= 0) {
		return true;
	}
	return false;

	/*
	 if(angle >= m_angle && m_angle > 0){
	 return true;
	 }
	 else if (angle <= m_angle && m_angle <= 0) {
	 return true;
	 }
	*/
	if	(turnController->OnTarget()) {
		return true;
	}
	 return false;
}

// Called once after isFinished returns true
void Turn::End() {
	turnTimer->Stop();
	double time = turnTimer->Get();
	SmartDashboard::PutNumber("Time: ", time);
	turnTimer->Reset();
	Robot::subsystemDrive->ArcadeDrive(0, 0, true);
	DriverStation::ReportError("Turn complete.");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Turn::Interrupted() {

}

/* This function is invoked periodically by the PID Controller, */
/* based upon navX-MXP yaw angle input and PID Coefficients.    */

