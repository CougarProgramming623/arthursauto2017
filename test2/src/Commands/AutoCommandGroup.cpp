#include "AutoCommandGroup.h"
#include "DistanceDriveCommand.h"
#include "SolenoidClaspCommand.h"
#include "DistanceDriveCommand2.h"
#include "Turn.h"
#include "WaitTime.h"

const static int BIG_TIME_OUT = 10;
//this is for stopping the robot in case we never run enough distance to drop the Gear
const static int SMALL_TIME_OUT = 3;
const static double DRIVE_TO_TURN = 93.0; // measured at 94.0
const static double DRIVE_TO_PEG = 72.25+2+2+2+2; // measured at 72.25
const static double DRIVE_TO_MIDDLE = 111.0; // measured at 111.0
const static double FRONT_HALF_LENGTH = 21.25;
const static double BACK_HALF_LENGTH = 17.25;
const static double TURN_DEGREES = 49.0f;

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
		//	AddSequential(new DistanceDriveCommand2(60.0, 0.5, BIG_TIME_OUT));
		//	AddSequential(new Turn(59.9f));
		//	AddSequential(new DistanceDriveCommand2(24.0, 0.5,  BIG_TIME_OUT));
		return;

	}
	//AddSequential(new DistanceDriveCommand2(120.0, 0.5, BIG_TIME_OUT));
	//REAL SCENARIO
	if (option == 0) //in the field left sided, and try to turn right
			{
		AddSequential(new SolenoidClaspCommand(0, SPEED_SOLENOID));
		// No longer need to open and close to grab gear.  It will start grabbed
		//AddSequential(new SolenoidClaspCommand(1, OPENCLOSE_SOLENOID)); //open gear
		//AddSequential(new WaitTime(.5));
		//AddSequential(new DistanceDriveCommand2(4, 0.4, BIG_TIME_OUT));
		AddSequential(new SolenoidClaspCommand(0, OPENCLOSE_SOLENOID)); //clasp gear
		AddSequential(new WaitTime(.5));

		AddSequential(new SolenoidClaspCommand(0, UPDOWN_SOLENOID)); //lift gear
		AddSequential(new WaitTime(.5));
		AddSequential(
				new DistanceDriveCommand2(DRIVE_TO_TURN - BACK_HALF_LENGTH,
						0.5, BIG_TIME_OUT));
		AddSequential(new WaitTime(.5));
		AddSequential(new SolenoidClaspCommand(1, SPEED_SOLENOID));//slow down for turn
		AddSequential(new Turn(TURN_DEGREES));
		AddSequential(new WaitTime(.5));

		//AddSequential(new Turn(RobotMap::angleFromCamera));

		AddSequential(
				new DistanceDriveCommand2(DRIVE_TO_PEG - FRONT_HALF_LENGTH + 4,
						0.6, BIG_TIME_OUT));
		AddSequential(new WaitTime(.5));
		AddSequential(new SolenoidClaspCommand(1, OPENCLOSE_SOLENOID)); //let go of gear
		AddSequential(new WaitTime(.5));
		AddSequential(new DistanceDriveCommand2(-1 * (DRIVE_TO_PEG - FRONT_HALF_LENGTH), 0.5,BIG_TIME_OUT)); // don't back up too much.  Stay in front of baseline

	} else if (option == 1) {
		AddSequential(new SolenoidClaspCommand(0, SPEED_SOLENOID));
		// No longer need to open and close to grab gear.  It will start grabbed
		//AddSequential(new SolenoidClaspCommand(1, OPENCLOSE_SOLENOID)); //open gear
		//AddSequential(new WaitTime(.5));
		//AddSequential(new DistanceDriveCommand2(4, 0.4, BIG_TIME_OUT));
		AddSequential(new SolenoidClaspCommand(0, OPENCLOSE_SOLENOID)); //close
		AddSequential(new WaitTime(.5)); //wait

		AddSequential(new SolenoidClaspCommand(0, UPDOWN_SOLENOID)); //up
		AddSequential(new WaitTime(.5)); //wait
		AddSequential(new DistanceDriveCommand2(DRIVE_TO_MIDDLE - FRONT_HALF_LENGTH - BACK_HALF_LENGTH, 0.5, BIG_TIME_OUT)); //go to peg
		AddSequential(new WaitTime(.5)); //wait
		AddSequential(new SolenoidClaspCommand(1, OPENCLOSE_SOLENOID)); //open
		AddSequential(new WaitTime(1.0));
		AddSequential(new DistanceDriveCommand2(-40, 0.5, BIG_TIME_OUT)); //drive back

	} else if (option == 2) {
		AddSequential(new SolenoidClaspCommand(0, SPEED_SOLENOID)); //high gear
		// No longer need to open and close to grab gear.  It will start grabbed
		//AddSequential(new SolenoidClaspCommand(1, OPENCLOSE_SOLENOID)); //open gear
		//AddSequential(new WaitTime(.5)); //wait
		//AddSequential(new DistanceDriveCommand2(4, 0.4, BIG_TIME_OUT)); //slight forward
		AddSequential(new SolenoidClaspCommand(0, OPENCLOSE_SOLENOID)); //close gear
		AddSequential(new WaitTime(.5)); //wait

		AddSequential(new SolenoidClaspCommand(0, UPDOWN_SOLENOID)); //gear up
		AddSequential(new WaitTime(.5)); //wait
		AddSequential(
				new DistanceDriveCommand2(DRIVE_TO_TURN - BACK_HALF_LENGTH,
						0.5, BIG_TIME_OUT)); //drive to pivot point
		AddSequential(new WaitTime(.5));
		AddSequential(new SolenoidClaspCommand(1, SPEED_SOLENOID)); //low gear
		AddSequential(new Turn(-1*TURN_DEGREES)); //turn robot
		//AddSequential(new Turn(RobotMap::angleFromCamera));
		AddSequential(new WaitTime(.5));
		AddSequential(
				new DistanceDriveCommand2(DRIVE_TO_PEG - FRONT_HALF_LENGTH + 4,
						0.6, BIG_TIME_OUT)); //drive to peg
		AddSequential(new WaitTime(.5)); //wait
		AddSequential(new SolenoidClaspCommand(1, OPENCLOSE_SOLENOID)); //open
		AddSequential(new WaitTime(.5)); //wait
		AddSequential(
				new DistanceDriveCommand2(
						-1 * (DRIVE_TO_PEG - FRONT_HALF_LENGTH), 0.5,
						BIG_TIME_OUT)); //drive back
		/*
		 AddSequential(new Turn(59.9f));
		 AddSequential(new DistanceDriveCommand2(110, 0.5, BIG_TIME_OUT));
		 */

	}

}
