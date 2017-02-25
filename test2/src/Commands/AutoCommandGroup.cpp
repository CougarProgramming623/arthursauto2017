#include <Commands/WaitTime.h>
#include "AutoCommandGroup.h"
#include "DistanceDriveCommand.h"
#include "Turn.h"
#include "SolenoidClaspCommand.h"


AutoCommandGroup::AutoCommandGroup() {

	AddSequential(new SolenoidClaspCommand(0, 0));
	AddSequential(new WaitTime(2));
	AddSequential(new SolenoidClaspCommand(0, 1));
	AddSequential(new WaitTime(3));
	AddSequential(new DistanceDriveCommand(2.0));
	AddSequential(new Turn(-59.9f));
	AddSequential(new DistanceDriveCommand(1.0));
	//AddSequential(new SolenoidClaspCommand())
	//AddSequential(new Turn())






	//AddSequential(new SolenoidClaspCommand(1));


}
