#include "AutoCommandGroup.h"
#include "DistanceDriveCommand.h"
#include "SolenoidClaspCommand.h"
#include "DistanceDriveCommand2.h"
#include "Turn.h"
#include "WaitTime.h"

const static int BIG_TIME_OUT = 10;
//this is for stopping the robot in case we never run enough distance to drop the Gear
const static int SMALL_TIME_OUT = 3;

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
	//REAL SCENORY
	if (option == 0) //in the field left sided, and try to turn right
			{
		AddSequential(new SolenoidClaspCommand(0, SPEED_SOLENOID));
		AddSequential(new SolenoidClaspCommand(1, OPENCLOSE_SOLENOID)); //open gear
		AddSequential(new WaitTime(.5));
		AddSequential(new DistanceDriveCommand2(2, 0.4, BIG_TIME_OUT));
		AddSequential(new SolenoidClaspCommand(0, OPENCLOSE_SOLENOID)); //clasp gear

		AddSequential(new WaitTime(.5));
		AddSequential(new SolenoidClaspCommand(0, UPDOWN_SOLENOID)); //lift gear
		AddSequential(new WaitTime(.5));
		AddSequential(new DistanceDriveCommand2(76.75 - 2 - 6, 0.5, BIG_TIME_OUT));
		AddSequential(new WaitTime(.5));
		AddSequential(new SolenoidClaspCommand(1, SPEED_SOLENOID));
		AddSequential(new Turn(59.9f));
		AddSequential(new WaitTime(.5));

		//AddSequential(new Turn(RobotMap::angleFromCamera));

		AddSequential(new DistanceDriveCommand2(48.67 + 5, 0.6, BIG_TIME_OUT));
		AddSequential(new WaitTime(.5));
		AddSequential(new SolenoidClaspCommand(1, OPENCLOSE_SOLENOID)); //let go of gear
		AddSequential(new WaitTime(.5));
		AddSequential(
				new DistanceDriveCommand2(-48.67 - 12, 0.4, BIG_TIME_OUT));
		/*
		 AddSequential(new WaitTime(.5));
		 AddSequential(new Turn(-59.9f));
		 AddSequential(new WaitTime(.5));
		 AddSequential(new DistanceDriveCommand2(110, 1.0, BIG_TIME_OUT));
		 */
	} else if (option == 1) {
		AddSequential(new SolenoidClaspCommand(1, OPENCLOSE_SOLENOID)); //open gear
		AddSequential(new WaitTime(.5));
		AddSequential(new DistanceDriveCommand2(2, 0.4, BIG_TIME_OUT));
		AddSequential(new SolenoidClaspCommand(0, OPENCLOSE_SOLENOID)); //close
		AddSequential(new WaitTime(.5)); //wait
		AddSequential(new SolenoidClaspCommand(0, UPDOWN_SOLENOID)); //up
		AddSequential(new WaitTime(.5)); //wait
		AddSequential(new DistanceDriveCommand2(66 + 3, 0.5, BIG_TIME_OUT)); //go to peg
		AddSequential(new WaitTime(.5)); //wait
		AddSequential(new SolenoidClaspCommand(1, OPENCLOSE_SOLENOID));//open
		AddSequential(new WaitTime(1.0));
		AddSequential(new DistanceDriveCommand2(-40, 0.5, BIG_TIME_OUT)); //drive back

	} else if (option == 2) {
		AddSequential(new SolenoidClaspCommand(0, SPEED_SOLENOID));
		AddSequential(new SolenoidClaspCommand(1, OPENCLOSE_SOLENOID)); //open gear
		AddSequential(new WaitTime(.5));
		AddSequential(new DistanceDriveCommand2(2, 0.4, BIG_TIME_OUT));
		AddSequential(new SolenoidClaspCommand(0, OPENCLOSE_SOLENOID));

		AddSequential(new WaitTime(.5));
		AddSequential(new SolenoidClaspCommand(0, UPDOWN_SOLENOID));
		AddSequential(new WaitTime(.5));
		AddSequential(new DistanceDriveCommand2(76.75 - 2 - 6, 0.5, BIG_TIME_OUT));
		AddSequential(new SolenoidClaspCommand(1, SPEED_SOLENOID));
		AddSequential(new Turn(-59.9f));
		//AddSequential(new Turn(RobotMap::angleFromCamera));
		AddSequential(new DistanceDriveCommand2(48.67+5, 0.6, BIG_TIME_OUT));
		AddSequential(new WaitTime(.5));
		AddSequential(new SolenoidClaspCommand(1, OPENCLOSE_SOLENOID));
		AddSequential(new WaitTime(.5));
		AddSequential(new DistanceDriveCommand2(-48.67 - 12, 0.4, BIG_TIME_OUT));
		/*
		 AddSequential(new Turn(59.9f));
		 AddSequential(new DistanceDriveCommand2(110, 0.5, BIG_TIME_OUT));
		 */

	}

}
