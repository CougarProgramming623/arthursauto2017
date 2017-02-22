
// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "DistanceDriveCommand.h"
#include "ahrs.h"
#include "RobotMap.h"

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR


	const static double kP = 0.03f;
	const static double kI = 0.00f;
	const static double kD = 0.00f;
	const static double kF = 0.00f;

	/* This tuning parameter indicates how close to "on target" the    */
	/* PID Controller will attempt to get.                             */

	const static double kToleranceDegrees = 2.0f;

	PIDController *turnController;      // PID Controller

	double rotateToAngleRate;

DistanceDriveCommand::DistanceDriveCommand(double distance): Command() {
	m_distance=distance;
	Requires(Robot::subsystemDrive.get());
}
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void DistanceDriveCommand::Initialize() {


	try {
	            /* Communicate w/navX-MXP via the MXP SPI Bus.                                       */
	            /* Alternatively:  I2C::Port::kMXP, SerialPort::Port::kMXP or SerialPort::Port::kUSB */
	            /* See http://navx-mxp.kauailabs.com/guidance/selecting-an-interface/ for details.   */

	            RobotMap::RobotMap::ahrs->ZeroYaw();

	        } catch (std::exception ex ) {
	            std::string err_string = "Error instantiating navX-MXP:  ";
	            err_string += ex.what();
	            DriverStation::ReportError(err_string.c_str());
	        }

	        m_resetTimer =new Timer();
	        m_resetTimer->Start();

	        turnController = new PIDController(kP, kI, kD, kF, RobotMap::ahrs, this);
			turnController->SetInputRange(-180.0f,  180.0f);
			turnController->SetOutputRange(-1.0, 1.0);
			turnController->SetAbsoluteTolerance(kToleranceDegrees);
			turnController->SetContinuous(true);

			//to keep it run straight
			turnController->SetSetpoint(0.0f);

}

// Called repeatedly when this Command is scheduled to run
void DistanceDriveCommand::Execute() {

	DriverStation::ReportError("execution in distanceDrive");

	std::ostringstream ss;
	ss << RobotMap::ahrs->GetYaw();
	std::string yaw(ss.str());


	DriverStation::ReportError(yaw);

	  deltaT = m_resetTimer->Get();
	  m_resetTimer->Reset();
	   if (RobotMap::ahrs->IsCalibrating()) {
	  	  m_resetTimer->Reset();
	  	  return;
	   }

	  double accelGyro[2]={0,0};
	  accelGyro[0] = -1*RobotMap::ahrs->GetWorldLinearAccelX()*kGravity;
	  //GetDisplacementY
	  accelGyro[1] = -1*RobotMap::ahrs->GetWorldLinearAccelY()*kGravity;

	  for ( int i = 0; i < 2; i++ ) {
		  lastPosEst[i] = lastPosEst[i] + lastVelEst[i]*deltaT + 0.5*deltaT*deltaT*lastAccelEst[i];
	  }
	  SmartDashboard::PutNumber("WorldLinearAccelY", RobotMap::ahrs->GetWorldLinearAccelY());
	  SmartDashboard::PutNumber("Last Position X", lastPosEst[0]);
	  SmartDashboard::PutNumber("Last Position Y", lastPosEst[1]);
	  SmartDashboard::PutNumber("Accel Gyro X", accelGyro[0]);
	  SmartDashboard::PutNumber("Accel Gyro Y", accelGyro[1]);

		std::ostringstream s1;
		s1 << lastPosEst[1];
		std::string lastPosY(s1.str());
	  DriverStation::ReportError(lastPosY);

	  for ( int i = 0; i < 2; i++ ) {
		  if(abs(accelGyro[i])<20){
			  lastVelEst[i]=lastVelEst[i]+lastAccelEst[i]*deltaT;
			  lastAccelEst[i]=accelGyro[i];
		  }
	  }

	  double angle = RobotMap::ahrs->GetYaw();
	  //Robot::subsystemDrive->ArcadeDrive(1,  -angle * kP, true);

	  Robot::subsystemDrive->ArcadeDrive(0.75, rotateToAngleRate, true);

}

// Make this return true when this Command no longer needs to run execute()
bool DistanceDriveCommand::IsFinished() {

	if(lastPosEst[1]>m_distance)
		return true;
    return false;
}

// Called once after isFinished returns true
void DistanceDriveCommand::End() {
	Robot::subsystemDrive->ArcadeDrive(0, 0, true);
	m_distance=0;
	turnController->Disable();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DistanceDriveCommand::Interrupted() {
	End();
}

/* This function is invoked periodically by the PID Controller, */
   /* based upon navX-MXP yaw angle input and PID Coefficients.    */
   void DistanceDriveCommand::PIDWrite(double output) {
       rotateToAngleRate = output;
   }

   //virtual void frc::PIDOutput::PIDWrite(double)



