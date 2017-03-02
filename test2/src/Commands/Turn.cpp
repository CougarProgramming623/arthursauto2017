#include "Turn.h"
#include "AHRS.h"
#include "RobotMap.h"


const static double kP = 0.01f;
const static double kI = 0.00f;
const static double kD = 0.00f;
const static double kF = 0.00f;

/* This tuning parameter indicates how close to "on target" the    */
/* PID Controller will attempt to get.                             */

const static double kToleranceDegrees = 2.0f;

Turn::Turn(double setpoint): Command() {
    m_angle=setpoint;
    Requires(Robot::subsystemDrive.get());
}

// Called just before this Command runs the first time
void Turn::Initialize() {
  try {
    /* Communicate w/navX-MXP via the MXP SPI Bus.                                       */
    /* Alternatively:  I2C::Port::kMXP, SerialPort::Port::kMXP or SerialPort::Port::kUSB */
    /* See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface/ for details.   */

//    RobotMap::ahrs->ZeroYaw();
    initialAngle = RobotMap::ahrs->GetYaw();

    DriverStation::ReportError("First time:"+std::to_string(initialAngle)+" "+std::to_string(m_angle));


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

  turnController->SetSetpoint(m_angle);
     turnController->Enable();

//  SetTimeout(5*1000);
}

// Called repeatedly when this Command is scheduled to run
void Turn::Execute() {
    //ahrs->ZeroYaw();
	double finishAngle = RobotMap::ahrs->GetYaw();
	DriverStation::ReportError("running:"+ std::to_string(finishAngle));

	double currentRotationRate = 0.3;
	/*if (abs(finishAngle - m_angle) <= 10) {
		currentRotationRate = 0.3;
	} else {
		currentRotationRate = 0.3;
	}*/
	if (m_angle < 0) {
		Robot::subsystemDrive->ArcadeDrive(0, -currentRotationRate, true);
	} else {
	    Robot::subsystemDrive->ArcadeDrive(0,  currentRotationRate, true);
	}
    SmartDashboard::PutNumber("Finish Angle: ",finishAngle);
}

// Make this return true when this Command no longer needs to run execute()
bool Turn::IsFinished() {
	double angle = RobotMap::ahrs->GetYaw()-initialAngle;
	double difference=abs(abs(m_angle)-abs(angle));
	if(difference<=1)
	   return true;
	   else
		   return false;
	/*
  if(angle >= m_angle && m_angle > 0){
    return true;
  }
  else if (angle <= m_angle && m_angle <= 0) {
	  return true;
  }
  return false;
  */
}

// Called once after isFinished returns true
void Turn::End() {
	Robot::subsystemDrive->ArcadeDrive(0, 0, true);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Turn::Interrupted() {

}

/* This function is invoked periodically by the PID Controller, */
/* based upon navX-MXP yaw angle input and PID Coefficients.    */
 void Turn::PIDWrite(double output) {
    rotateToAngleRate = output;
}
