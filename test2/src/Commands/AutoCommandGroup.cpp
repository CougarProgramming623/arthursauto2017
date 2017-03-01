

#include "AutoCommandGroup.h"
#include "DistanceDriveCommand.h"
#include "SolenoidClaspCommand.h"
#include "DistanceDriveCommand2.h"
#include "Turn.h"
#include "WaitTime.h"

const static int BIG_TIME_OUT=100;
//this is for stopping the robot in case we never run enough distance to drop the Gear
const static int SMALL_TIME_OUT=3;

AutoCommandGroup::AutoCommandGroup(int option1) : CommandGroup() {
	option=option1;
	if(option==-1){
		AddSequential(new DistanceDriveCommand2(60.0, BIG_TIME_OUT));
		AddSequential(new Turn(59.9f));
		AddSequential(new DistanceDriveCommand2(24.0, BIG_TIME_OUT));
		return;

	}


	/*
..
	    AddSequential(new SolenoidClaspCommand(0, 0));
		AddSequential(new WaitTime(0.5));
		AddSequential(new SolenoidClaspCommand(0, 1));
		AddSequential(new WaitTime(0.5));
		AddSequential(new DistanceDriveCommand2(24));
		AddSequential(new Turn(59.9f));
		AddSequential(new DistanceDriveCommand2(12));
		AddSequential(new WaitTime(0.5));
		AddSequential(new SolenoidClaspCommand(1, 0));

		*/

		//if(1==1)
		//	return;

		//REAL SCENORY
		if(option==0) //in the field left sided, and try to turn right
		{
			    AddSequential(new SolenoidClaspCommand(0, 0));
				AddSequential(new WaitTime(0.5));
				AddSequential(new SolenoidClaspCommand(0, 1));
				AddSequential(new WaitTime(0.5));
				AddSequential(new DistanceDriveCommand2(100.6 , BIG_TIME_OUT));
				AddSequential(new Turn(59.9f));
				AddSequential(new DistanceDriveCommand2(15.18, SMALL_TIME_OUT));
				AddSequential(new WaitTime(0.5));
				AddSequential(new SolenoidClaspCommand(1, 0));
				AddSequential(new WaitTime(0.5));
				AddSequential(new DistanceDriveCommand2(-15.18, BIG_TIME_OUT));
				AddSequential(new Turn(-59.9f));
				AddSequential(new DistanceDriveCommand2(16, BIG_TIME_OUT));

		}
		else if(option==1)
		{
		    AddSequential(new SolenoidClaspCommand(0, 0));
			AddSequential(new WaitTime(0.5));
			AddSequential(new SolenoidClaspCommand(0, 1));
			AddSequential(new WaitTime(0.5));
			AddSequential(new DistanceDriveCommand2(100.6+8, BIG_TIME_OUT));
			AddSequential(new WaitTime(0.5));
			AddSequential(new SolenoidClaspCommand(1, 0));
			AddSequential(new DistanceDriveCommand2(-20, BIG_TIME_OUT));

		}
		else if(option==2)
		{
		    AddSequential(new SolenoidClaspCommand(0, 0));
			AddSequential(new WaitTime(0.5));
			AddSequential(new SolenoidClaspCommand(0, 1));
			AddSequential(new WaitTime(0.5));
			AddSequential(new DistanceDriveCommand2(100.6,BIG_TIME_OUT));
			AddSequential(new Turn(-59.9f));
			AddSequential(new DistanceDriveCommand2(15.18, SMALL_TIME_OUT));
			AddSequential(new WaitTime(0.5));
			AddSequential(new SolenoidClaspCommand(1, 0));
			AddSequential(new WaitTime(0.5));
			AddSequential(new DistanceDriveCommand2(-15.18,BIG_TIME_OUT));
			AddSequential(new Turn(59.9f));
			AddSequential(new DistanceDriveCommand2(16,BIG_TIME_OUT));
		}



}


