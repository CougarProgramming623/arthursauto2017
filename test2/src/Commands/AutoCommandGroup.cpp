

#include "AutoCommandGroup.h"
#include "DistanceDriveCommand.h"
#include "SolenoidClaspCommand.h"
#include "DistanceDriveCommand2.h"
#include "Turn.h"
#include "WaitTime.h"



AutoCommandGroup::AutoCommandGroup(int option1) : CommandGroup() {
	option=option1;
	if(option==-1)
		return;

	AddSequential(new DistanceDriveCommand2(24.0)); //24 inches
		AddSequential(new Turn(59.9f));
		AddSequential(new DistanceDriveCommand2(12.0));

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

		if(1==1)
			return;

		//REAL SCENORY
		if(option==0) //in the field left sided, and try to turn right
		{
			    AddSequential(new SolenoidClaspCommand(0, 0));
				AddSequential(new WaitTime(0.5));
				AddSequential(new SolenoidClaspCommand(0, 1));
				AddSequential(new WaitTime(0.5));
				AddSequential(new DistanceDriveCommand2(100.6));
				AddSequential(new Turn(59.9f));
				AddSequential(new DistanceDriveCommand2(15.18));
				AddSequential(new WaitTime(0.5));
				AddSequential(new SolenoidClaspCommand(1, 0));
				AddSequential(new WaitTime(0.5));
				AddSequential(new DistanceDriveCommand2(-15.18));
				AddSequential(new Turn(-59.9f));
				AddSequential(new DistanceDriveCommand2(16));

		}
		else if(option==1)
		{
		    AddSequential(new SolenoidClaspCommand(0, 0));
			AddSequential(new WaitTime(0.5));
			AddSequential(new SolenoidClaspCommand(0, 1));
			AddSequential(new WaitTime(0.5));
			AddSequential(new DistanceDriveCommand2(100.6+8));
			AddSequential(new WaitTime(0.5));
			AddSequential(new SolenoidClaspCommand(1, 0));
			AddSequential(new DistanceDriveCommand2(-20));

		}
		else if(option==2)
		{
		    AddSequential(new SolenoidClaspCommand(0, 0));
			AddSequential(new WaitTime(0.5));
			AddSequential(new SolenoidClaspCommand(0, 1));
			AddSequential(new WaitTime(0.5));
			AddSequential(new DistanceDriveCommand2(100.6));
			AddSequential(new Turn(-59.9f));
			AddSequential(new DistanceDriveCommand2(15.18));
			AddSequential(new WaitTime(0.5));
			AddSequential(new SolenoidClaspCommand(1, 0));
			AddSequential(new WaitTime(0.5));
			AddSequential(new DistanceDriveCommand2(-15.18));
			AddSequential(new Turn(59.9f));
			AddSequential(new DistanceDriveCommand2(16));
		}



}


