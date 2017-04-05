#include "AutoCommandGroup.h"
#include "DistanceDriveCommand.h"
#include "SolenoidClaspCommand.h"
#include "DistanceDriveCommand2.h"
#include "Turn.h"
#include "WaitTime.h"

const static int BIG_TIME_OUT = 10;
//this is for stopping the robot in case we never run enough distance to drop the Gear
const static int SMALL_TIME_OUT = 3;
const static double DRIVE_TO_TURN = 93.0+3.0; // measured at 94.0
const static double DRIVE_TO_PEG = 72.25+2+2+2+2+3-15; // measured at 72.25
const static double DRIVE_TO_MIDDLE = 111.0; // measured at 111.0
const static double FRONT_HALF_LENGTH = 21.25;
const static double BACK_HALF_LENGTH = 17.25;
const static double TURN_DEGREES = 60.0f;

AutoCommandGroup::AutoCommandGroup(int option1) :
		CommandGroup() {

	//AddSequential(new DistanceDriveCommand2(100 ,0.5, BIG_TIME_OUT));
	//return;

	//option=option1;
	option = -1;
	if (RobotMap::digitalInput0->Get() == 0) {
		option = 0;
	} else if (RobotMap::digitalInput1->Get() == 0) {
		option = 1;
	} else if (RobotMap::digitalInput2->Get() == 0) {
		option = 2;
	}

	if (option == -1) {
		//AddSequential(new DistanceDriveCommand2(48, 1.0, BIG_TIME_OUT));
		AddSequential(new Turn(90.0f));
		return;

	}
	//AddSequential(new DistanceDriveCommand2(120.0, 0.5, BIG_TIME_OUT));
	//REAL SCENARIO
	if (option == 0) //in the field left sided, and try to turn right
			{
		AddSequential(new SolenoidClaspCommand(0, SPEED_SOLENOID)); //high gear
		AddSequential(new SolenoidClaspCommand(0, OPENCLOSE_SOLENOID)); //clasp gear;
		AddSequential(new SolenoidClaspCommand(0, UPDOWN_SOLENOID)); //lift gear
		AddSequential(new DistanceDriveCommand2(DRIVE_TO_TURN - BACK_HALF_LENGTH, 1.0, BIG_TIME_OUT)); //Haven't yet figured out why 0 and 2 are traveling different distances
		AddSequential(new SolenoidClaspCommand(1, SPEED_SOLENOID));//slow down for turn
		AddSequential(new Turn(TURN_DEGREES));
		//AddSequential(new Turn(RobotMap::angleFromCamera));
		AddSequential(new DistanceDriveCommand2(DRIVE_TO_PEG - FRONT_HALF_LENGTH + 4, 0.75 , BIG_TIME_OUT));
		//AddSequential(new WaitTime(.5));
		//AddSequential(new SolenoidClaspCommand(1, OPENCLOSE_SOLENOID)); //let go of gear
		//AddSequential(new WaitTime(.5));
		//AddSequential(new DistanceDriveCommand2(-1 * (DRIVE_TO_PEG - FRONT_HALF_LENGTH), 0.5,BIG_TIME_OUT)); // don't back up too much.  Stay in front of baseline

	} else if (option == 1) {
		AddSequential(new SolenoidClaspCommand(0, SPEED_SOLENOID));
		AddSequential(new SolenoidClaspCommand(0, OPENCLOSE_SOLENOID)); //close
		AddSequential(new SolenoidClaspCommand(0, UPDOWN_SOLENOID)); //up
		AddSequential(new DistanceDriveCommand2(DRIVE_TO_MIDDLE - FRONT_HALF_LENGTH - BACK_HALF_LENGTH + 7.5, 1.0, BIG_TIME_OUT)); //go to peg
		AddSequential(new SolenoidClaspCommand(0, GEAR_PUSHER_SOLENOID)); //push gear
		AddSequential(new WaitTime(0.5));
		AddSequential(new SolenoidClaspCommand(1, OPENCLOSE_SOLENOID)); //open
		AddSequential(new WaitTime(0.5));
		AddSequential(new DistanceDriveCommand2(-40, 0.75, BIG_TIME_OUT)); //drive back
		AddSequential(new SolenoidClaspCommand(1, GEAR_PUSHER_SOLENOID)); //unpush gear
	} else if (option == 2) {
		AddSequential(new SolenoidClaspCommand(0, SPEED_SOLENOID)); //high gear
		AddSequential(new SolenoidClaspCommand(0, OPENCLOSE_SOLENOID)); //close gear
		AddSequential(new SolenoidClaspCommand(0, UPDOWN_SOLENOID)); //gear up
		AddSequential(new DistanceDriveCommand2(DRIVE_TO_TURN - BACK_HALF_LENGTH, 1.0, BIG_TIME_OUT)); //drive to pivot point
		AddSequential(new SolenoidClaspCommand(1, SPEED_SOLENOID)); //low gear
		AddSequential(new Turn(-1*TURN_DEGREES)); //turn robot
		AddSequential(new DistanceDriveCommand2(DRIVE_TO_PEG - FRONT_HALF_LENGTH + 4, 0.75, BIG_TIME_OUT)); //drive to peg
		//AddSequential(new WaitTime(.5)); //wait
		//AddSequential(new SolenoidClaspCommand(1, OPENCLOSE_SOLENOID)); //open
		//AddSequential(new WaitTime(.5)); //wait
		//AddSequential(new DistanceDriveCommand2(-1 * (DRIVE_TO_PEG - FRONT_HALF_LENGTH), 0.5, BIG_TIME_OUT)); //drive back
		/*
		 AddSequential(new Turn(59.9f));
		 AddSequential(new DistanceDriveCommand2(110, 0.5, BIG_TIME_OUT));
		 */

	}

}
