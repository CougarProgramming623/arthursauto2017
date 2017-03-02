

#include "AutoCommandGroup.h"
#include "DistanceDriveCommand.h"
#include "SolenoidClaspCommand.h"
#include "DistanceDriveCommand2.h"
#include "Turn.h"
#include "WaitTime.h"

const static int BIG_TIME_OUT=10;
//this is for stopping the robot in case we never run enough distance to drop the Gear
const static int SMALL_TIME_OUT=3;

AutoCommandGroup::AutoCommandGroup(int option1) : CommandGroup() {

	//AddSequential(new DistanceDriveCommand2(100 ,0.5, BIG_TIME_OUT));
	//return;

	//option=option1;
	option=-1;
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

	if(option==-1){
		AddSequential(new DistanceDriveCommand2(60.0, 0.5, BIG_TIME_OUT));
		AddSequential(new Turn(59.9f));
		AddSequential(new DistanceDriveCommand2(24.0, 0.5,  BIG_TIME_OUT));
		return;

	}

		//REAL SCENORY
		if(option==0) //in the field left sided, and try to turn right
		{
			    AddSequential(new SolenoidClaspCommand(0, 0));
				AddSequential(new WaitTime(0.5));
				AddSequential(new SolenoidClaspCommand(0, 1));
				AddSequential(new WaitTime(0.5));
				AddSequential(new DistanceDriveCommand2(100.6 , 0.5, BIG_TIME_OUT));
				AddSequential(new WaitTime(0.5));
				AddSequential(new Turn(59.9f));
				AddSequential(new WaitTime(0.5));

				//AddSequential(new Turn(RobotMap::angleFromCamera));

				AddSequential(new DistanceDriveCommand2(15.18,  0.6,  BIG_TIME_OUT));
				AddSequential(new WaitTime(0.5));
				AddSequential(new SolenoidClaspCommand(1, 0));
				AddSequential(new WaitTime(0.5));
				AddSequential(new DistanceDriveCommand2(-15.18,  0.5,  BIG_TIME_OUT));
				AddSequential(new WaitTime(0.5));
				AddSequential(new Turn(-59.9f));
				AddSequential(new WaitTime(0.5));
				AddSequential(new DistanceDriveCommand2(16,  0.5, BIG_TIME_OUT));

		}
		else if(option==1)
		{
		    AddSequential(new SolenoidClaspCommand(0, 0));
			AddSequential(new WaitTime(0.5));
			AddSequential(new SolenoidClaspCommand(0, 1));
			AddSequential(new WaitTime(0.5));
			AddSequential(new DistanceDriveCommand2(100.6+8,  0.5, BIG_TIME_OUT));
			AddSequential(new WaitTime(0.5));
			AddSequential(new SolenoidClaspCommand(1, 0));
			AddSequential(new DistanceDriveCommand2(-20,  0.5, BIG_TIME_OUT));

		}
		else if(option==2)
		{
		    AddSequential(new SolenoidClaspCommand(0, 0));
			AddSequential(new WaitTime(0.5));
			AddSequential(new SolenoidClaspCommand(0, 1));
			AddSequential(new WaitTime(0.5));
			AddSequential(new DistanceDriveCommand2(100.6, 0.5, BIG_TIME_OUT));
			AddSequential(new Turn(-59.9f));

			//AddSequential(new Turn(RobotMap::angleFromCamera));

			AddSequential(new DistanceDriveCommand2(15.18,  0.6, BIG_TIME_OUT));
			AddSequential(new WaitTime(0.5));
			AddSequential(new SolenoidClaspCommand(1, 0));
			AddSequential(new WaitTime(0.5));
			AddSequential(new DistanceDriveCommand2(-15.18, 0.5, BIG_TIME_OUT));
			AddSequential(new Turn(59.9f));
			AddSequential(new DistanceDriveCommand2(16, 0.5, BIG_TIME_OUT));
		}

}


