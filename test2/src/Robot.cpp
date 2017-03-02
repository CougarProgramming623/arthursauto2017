// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.
#include "RobotMap.h"
#include "Robot.h"
#include "Commands/SolenoidClaspCommand.h"
#include "Commands/AutoCommandGroup.h"
#include "NetworkTables/NetworkTable.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION dfgsuifhsgadfuhsvbhj
std::shared_ptr<SubsystemDrive> Robot::subsystemDrive;
std::unique_ptr<OI> Robot::oi;

std::shared_ptr<NetworkTable> networkTable;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION

void Robot::RobotInit() {
	RobotMap::init();
	CameraServer::GetInstance()->StartAutomaticCapture(0);
	//CameraServer::GetInstance()->StartAutomaticCapture(1);

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS

	networkTable = NetworkTable::GetTable("GRIP/myContoursReport");


	RobotMap::ClaspSolenoid->Set(false);
	RobotMap::ArmSolenoid->Set(false);
	RobotMap::SpeedSolenoid->Set(false);
    subsystemDrive.reset(new SubsystemDrive());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.
	oi.reset(new OI());

	// instantiate the command used for the autonomous period
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	//autonomousCommand.reset(new AutonomousCommand());


	DriverStation::ReportError("digital input 0 is:" +std::to_string( RobotMap::digitalInput0->Get()));
	DriverStation::ReportError("digital input 1 is:" +std::to_string( RobotMap::digitalInput1->Get()));
	DriverStation::ReportError("digital input 2 is:" +std::to_string( RobotMap::digitalInput2->Get()));


	int option=-1;
	if(RobotMap::digitalInput0->Get()==0)
	{
		option=0;
	}
	else if(RobotMap::digitalInput1->Get()==0)
	{
		option=1;
	}
	else if(RobotMap::digitalInput2->Get()==0)
	{
		option=2;
	}
	autonomousCommand.reset(new AutoCommandGroup(option));




    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
  }

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();
}

void Robot::DisabledPeriodic() {


	Scheduler::GetInstance()->Run();
}

void Robot::AutonomousInit() {

	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Start();

}

void Robot::AutonomousPeriodic() {
	Scheduler::GetInstance()->Run();

	//DriverStation::ReportError("digital input 0 is:" +std::to_string( RobotMap::digitalInput0->Get()));
	//DriverStation::ReportError("digital input 1 is:" +std::to_string( RobotMap::digitalInput1->Get()));
	//DriverStation::ReportError("digital input 2 is:" +std::to_string( RobotMap::digitalInput2->Get()));
}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
	if (autonomousCommand.get() != nullptr)
		autonomousCommand->Cancel();
}

void Robot::TeleopPeriodic() {
	Scheduler::GetInstance()->Run();


	std::vector<double> tempArray = networkTable->GetNumberArray("width", llvm::ArrayRef<double>());
	for(unsigned int i = 0; i < tempArray.size(); i++){
		DriverStation::ReportError("width " + std::to_string(tempArray[i]));
	}

//	DriverStation::ReportError("encoder  is:" +std::to_string( RobotMap::cantalonLeftFront->GetEncPosition()));

}

void Robot::TestPeriodic() {
	lw->Run();
}

START_ROBOT_CLASS(Robot);

