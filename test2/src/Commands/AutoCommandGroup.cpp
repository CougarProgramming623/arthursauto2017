

#include "AutoCommandGroup.h"
#include "DistanceDriveCommand.h"
#include "SolenoidClaspCommand.h"
#include "DistanceDriveCommand2.h"



AutoCommandGroup::AutoCommandGroup() {

//	AddSequential(new DistanceDriveCommand2(1.0));


//	AddSequential(new DistanceDriveCommand(1.0));

	//AddSequential(new DistanceDriveCommand(-3.0));


	//AddSequential(new DistanceDriveCommand(1.0));



	AddSequential(new SolenoidClaspCommand(0, 0));//set clasp solenoid to true

	Wait(10*1000);//wait 1s

	AddSequential(new SolenoidClaspCommand(0, 1));//set arm solenoid to true

	//AddSequential(new DistanceDriveCommand(1.0));

	AddSequential(new SolenoidClaspCommand(1, 0));//set clasp solenoid to true

	//AddSequential(new SolenoidClaspCommand(1, 1));//set clasp solenoid to true



}
