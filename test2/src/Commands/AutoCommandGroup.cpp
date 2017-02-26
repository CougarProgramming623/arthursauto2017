

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
//		AddSequential(new Turn(-59.9f));
		AddSequential(new DistanceDriveCommand2(12.0));

	/*AddSequential(new SolenoidClaspCommand(0, 0));
	AddSequential(new WaitTime(2));
	AddSequential(new SolenoidClaspCommand(0, 1));
	AddSequential(new WaitTime(3));
	AddSequential(new DistanceDriveCommand2(2.0));
	AddSequential(new Turn(-59.9f));
	AddSequential(new DistanceDriveCommand2(1.0));

	*/
    //option will be 0, 1, 2

//	AddSequential(new DistanceDriveCommand2(1.0));


//	AddSequential(new DistanceDriveCommand2(1.0));

	//AddSequential(new DistanceDriveCommand2(-3.0));


	//AddSequential(new DistanceDriveCommand2(1.0));



	//AddSequential(new SolenoidClaspCommand(0, 0));//set clasp solenoid to true

	//Wait(10*1000);//wait 1s

	//AddSequential(new SolenoidClaspCommand(0, 1));//set arm solenoid to true

	//AddSequential(new DistanceDriveCommand2(1.0));

	//AddSequential(new SolenoidClaspCommand(1, 0));//set clasp solenoid to false

	//AddSequential(new SolenoidClaspCommand(1, 1));//set arm solenoid to false



}
