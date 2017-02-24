/*
 * SolenoidClaspCommand.h
 *
 *  Created on: Feb 22, 2017
 *      Author: Liao_Family
 */

#ifndef SRC_COMMANDS_SOLENOIDCLASPCOMMAND_H_
#define SRC_COMMANDS_SOLENOIDCLASPCOMMAND_H_

#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "WPILib.h"

class SolenoidClaspCommand: public Command
{
public:

	SolenoidClaspCommand(int, int);

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	int command;
	int solenoid;
};



#endif /* SRC_COMMANDS_SOLENOIDCLASPCOMMAND_H_ */
