#include "Turn.h"
#include "AHRS.h"
#include "RobotMap.h"


const static double kP = 0.03f;
const static double kI = 0.00f;
const static double kD = 0.00f;
const static double kF = 0.00f;

/* This tuning parameter indicates how close to "on target" the    */
/* PID Controller will attempt to get.                             */

const static double kToleranceDegrees = 2.0f;

Turn::Turn(double angle): Command() {
    m_angle=angle;
    Requires(Robot::subsystemDrive.get());
}

// Called just before this Command runs the first time
void Turn::Initialize() {
	try {
		/* Communicate w/navX-MXP via the MXP SPI Bus.                                       */
		/* Alternatively:  I2C::Port::kMXP, SerialPort::Port::kMXP or SerialPort::Port::kUSB */
		/* See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface/ for details.   */
		 DriverStation::ReportError("First time for distance command");

		RobotMap::RobotMap::ahrs->ZeroYaw();

		} catch (std::exception ex ) {
		std::string err_string = "Error instantiating navX-MXP:  ";
		err_string += ex.what();
		DriverStation::ReportError(err_string.c_str());
	}

	turnController = new PIDController(kP, kI, kD, kF, RobotMap::ahrs, this);
	turnController->SetInputRange(-180.0f,  180.0f);
	turnController->SetOutputRange(-1.0, 1.0);
	turnController->SetAbsoluteTolerance(kToleranceDegrees);
	turnController->SetContinuous(true);
}

// Called repeatedly when this Command is scheduled to run
void Turn::Execute() {
    ahrs->ZeroYaw();
    double currentRotationRate;
    turnController->SetSetpoint(m_angle);
    turnController->Enable();
    currentRotationRate = rotateToAngleRate;
//	  double angle = RobotMap::ahrs->GetYaw();
//	  Robot::subsystemDrive->ArcadeDrive(0,  -angle * kP, true);
    Robot::subsystemDrive->ArcadeDrive(0,  currentRotationRate, true);

}

// Make this return true when this Command no longer needs to run execute()
bool Turn::IsFinished() {
	if(rotateToAngleRate==0){
		return true;
	}
	return false;
}

// Called once after isFinished returns true
void Turn::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Turn::Interrupted() {

}

/* This function is invoked periodically by the PID Controller, */
/* based upon navX-MXP yaw angle input and PID Coefficients.    */
virtual void Turn::PIDWrite(double output) {
    rotateToAngleRate = output;
}
