/*
 * SolenoidClaspCommand.cpp
 *
 *  Created on: Feb 22, 2017
 *      Author: Liao_Family
 */

#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "SolenoidClaspCommand.h"
#include "RobotMap.h"

SolenoidClaspCommand::SolenoidClaspCommand(int solenoidCommand, int solenoidReference): Command(){
  //Requires(RobotMap::ClaspSolenoid->Get());
	command=solenoidCommand;//0 for true
							//1 for false
	solenoid = solenoidReference;//0 for clasp solenoid
								 //1 for arm solenoid
}

void SolenoidClaspCommand::Initialize(){

}
void SolenoidClaspCommand::Execute(){
	if(solenoid == 0){//clasp solenoid
		if(command == 0)
			RobotMap::ClaspSolenoid->Set(true);
		else if(command == 1)
			RobotMap::ClaspSolenoid->Set(false);
	}
	else if(solenoid == 1){//arm solenoid
		if(command == 0)
			RobotMap::ArmSolenoid->Set(true);
		else if(command == 1)
			RobotMap::ArmSolenoid->Set(false);
	}

	DriverStation::ReportError(" SolenoidClaspCommand:" +std::to_string(solenoid) + "command "+std::to_string(command));


}
bool SolenoidClaspCommand::IsFinished(){

	return true;
}
void SolenoidClaspCommand::End(){

}
void SolenoidClaspCommand::Interrupted(){
	End();
}



