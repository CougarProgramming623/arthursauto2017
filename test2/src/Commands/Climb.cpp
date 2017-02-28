/*
 * Climb.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: Liao_Family
 */


#include "Climb.h"
#include "ahrs.h"
#include "RobotMap.h"


Climb::Climb(double speed): Command() {
	m_speed=speed;
}

void Climb::Initialize() {


}


// Called repeatedly when this Command is scheduled to run
void Climb::Execute() {
	RobotMap::cantalonClimb->Set(m_speed);

}

// Make this return true when this Command no longer needs to run execute()
bool Climb::IsFinished() {

    return false;
}

// Called once after isFinished returns true
void Climb::End() {
	RobotMap::cantalonClimb->Set(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Climb::Interrupted() {
	End();
}








