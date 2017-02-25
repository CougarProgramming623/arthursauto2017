/*
 * DistanceDriveCommand2.cpp
 *

 */


#include "DistanceDriveCommand2.h"
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

	const static double FEET_PER_REV = 0.472;

	int counter=0;



DistanceDriveCommand2::DistanceDriveCommand2(double distance): Command() {
	m_distance=distance;
	Requires(Robot::subsystemDrive.get());

	//for now
	//SetTimeout(2);
}
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void DistanceDriveCommand2::Initialize() {

	//SetTimeout(2);

	try {
		DriverStation::ReportError("DistanceDriveCommand init");
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

			for(int i=0; i<2;i++)
			{
				 lastPosEst[i] =0;
				 lastVelEst[i] =0;
				 lastAccelEst[i]=0;
			}

			rotateToAngleRate=0;
			initEncPosition=getPosition();

}

double  DistanceDriveCommand2::getDriveDistance()
{
	return (getPosition()-initEncPosition)*FEET_PER_REV/(1440*4.0);

}

int DistanceDriveCommand2::getPosition()
{
	return RobotMap::cantalonLeftFront->GetEncPosition();
}

// Called repeatedly when this Command is scheduled to run
void DistanceDriveCommand2::Execute() {

	DriverStation::ReportError(" distanceDrive yawn is:" +std::to_string( RobotMap::ahrs->GetYaw()));
	DriverStation::ReportError(" encoderposition:" +std::to_string(getPosition())+ " "+std::to_string(initEncPosition));
	DriverStation::ReportError(" rev is:" +std::to_string((getPosition()-initEncPosition)/(1440*4.0)));


	  double angle = RobotMap::ahrs->GetYaw();
	  //Robot::subsystemDrive->ArcadeDrive(1,  -angle * kP, true);
	  if(m_distance<0)
	    Robot::subsystemDrive->ArcadeDrive(-0.75, rotateToAngleRate, true);
	  else
		  Robot::subsystemDrive->ArcadeDrive(0.75, rotateToAngleRate, true);

}

// Make this return true when this Command no longer needs to run execute()
bool DistanceDriveCommand2::IsFinished() {
	if(fabs(getDriveDistance())>fabs(m_distance))
		return true;

    return false;
}

// Called once after isFinished returns true
void DistanceDriveCommand2::End() {
	DriverStation::ReportError("DistanceDriveCommand end");

	initEncPosition=getPosition();
	m_distance=0;

	Robot::subsystemDrive->ArcadeDrive(0, 0, true);

	if(turnController != nullptr)
	{	turnController->Disable();
		delete turnController;
	}
	if(m_resetTimer != nullptr)
	{ m_resetTimer->Reset();
	  delete m_resetTimer;
	}

	for(int i=0; i<2;i++)
	{
		 lastPosEst[i] =0;
		 lastVelEst[i] =0;
		 lastAccelEst[i]=0;
	}
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DistanceDriveCommand2::Interrupted() {
	End();
}

/* This function is invoked periodically by the PID Controller, */
   /* based upon navX-MXP yaw angle input and PID Coefficients.    */
   void DistanceDriveCommand2::PIDWrite(double output) {
       rotateToAngleRate = output;
   }

   //virtual void frc::PIDOutput::PIDWrite(double)





