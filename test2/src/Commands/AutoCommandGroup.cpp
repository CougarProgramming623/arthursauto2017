#include "AutoCommandGroup.h"
#include "DistanceDriveCommand.h"
//#include "SolenoidClaspCommand.h"


AutoCommandGroup::AutoCommandGroup() {

	AddSequential(new DistanceDriveCommand(2.0));
	AddSequential(new DistanceDriveCommand(-2.0));

	//AddSequential(new SolenoidClaspCommand(1));


}
