// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "DriveWithJoysticks.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

DriveWithJoysticks::DriveWithJoysticks(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::subsystemDrive.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	YAxis = 0;
	RotAxis = 0;
}

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called just before this Command runs the first time
void DriveWithJoysticks::Initialize() {
	YAxis = 0;
	RotAxis = 0;
}

// Called repeatedly when this Command is scheduled to run
void DriveWithJoysticks::Execute() {
	YAxis = Robot::oi->getdriverJoystick()->GetRawAxis(1);
	RotAxis = Robot::oi->getdriverJoystick()->GetRawAxis(2);

	if (YAxis > -0.20 && YAxis < 0.20) {
		YAxis = 0;
	}


	/*if (RotAxis > -0.20 && RotAxis < 0.20) {
		RotAxis = 0;
	}*/

	Robot::subsystemDrive->ArcadeDrive(YAxis, RotAxis, true);

	/*std::ostringstream ss;
	ss << RobotMap::ahrs->GetPitch();
	std::string pitch(ss.str());


	DriverStation::ReportError(pitch);
    */
}

// Make this return true when this Command no longer needs to run execute()
bool DriveWithJoysticks::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void DriveWithJoysticks::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveWithJoysticks::Interrupted() {

}
