/*
 * Climbe.h
 *
 *  Created on: Feb 27, 2017
 *      Author: Liao_Family
 */

#ifndef SRC_COMMANDS_CLIMB_H_
#define SRC_COMMANDS_CLIMB_H_

#include "Commands/Subsystem.h"
#include "../Robot.h"


class Climb: public Command
{
public:
	Climb(double);

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

	double m_speed = 0.0;

};

#endif /* SRC_COMMANDS_CLIMB_H_ */
