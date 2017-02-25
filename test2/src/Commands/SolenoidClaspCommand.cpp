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
							     //2 for speed solenoid
}

void SolenoidClaspCommand::Initialize(){

}
void SolenoidClaspCommand::Execute(){
	if(solenoid == 0){//clasp solenoid
		if(command == 0){
			RobotMap::ClaspSolenoid->Set(true);
			RobotMap::buttonBoard->SetOutput(5, true);
			RobotMap::buttonBoard->SetOutput(9, false);
		}

		else if(command == 1){
			RobotMap::ClaspSolenoid->Set(false);
			RobotMap::buttonBoard->SetOutput(9, true);
			RobotMap::buttonBoard->SetOutput(5, false);
		}

	}
	else if(solenoid == 1){//arm solenoid
		if(command == 0){
			RobotMap::buttonBoard->SetOutput(3, true);
			RobotMap::buttonBoard->SetOutput(4, false);
			RobotMap::ArmSolenoid->Set(true);
		}

		else if(command == 1){
			RobotMap::buttonBoard->SetOutput(4, true);
			RobotMap::buttonBoard->SetOutput(3, false);
			RobotMap::ArmSolenoid->Set(false);
		}

	}
	else if(solenoid == 2){//speed solenoid
		if(command == 0){
			RobotMap::buttonBoard->SetOutput(10, true);
			RobotMap::buttonBoard->SetOutput(11, false);
			RobotMap::SpeedSolenoid->Set(true);
		}

		else if(command == 1){
			RobotMap::buttonBoard->SetOutput(11, true);
			RobotMap::buttonBoard->SetOutput(10, false);
			RobotMap::SpeedSolenoid->Set(false);
		}

	}

	DriverStation::ReportError(" Solenoid:" +std::to_string(solenoid) + "command "+std::to_string(command));


}
bool SolenoidClaspCommand::IsFinished(){

	return true;
}
void SolenoidClaspCommand::End(){
	/*if(solenoid == 0){//clasp solenoid
			RobotMap::ClaspSolenoid->Set(false);
	}
	else if(solenoid == 1){//arm solenoid
			RobotMap::ArmSolenoid->Set(false);
	}
	else if(solenoid == 2){//speed solenoid
			RobotMap::SpeedSolenoid->Set(false);
	}*/
}
void SolenoidClaspCommand::Interrupted(){
	End();
}



