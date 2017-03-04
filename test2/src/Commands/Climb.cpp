/*
 * Climb.cpp
 *
 *  Created on: Feb 27, 2017
 *      Author: Liao_Family
 */


#include "Climb.h"
#include "ahrs.h"
#include "../RobotMap.h"

const double maxCurrent = 15.0;
int spikeCounter = 0;
int maxSpikeCounter = 0;

Climb::Climb(double speed): Command() {
	m_speed=speed;
}

void Climb::Initialize() {
	DriverStation::ReportError("Climb initialize" + std::to_string(m_speed));

}


// Called repeatedly when this Command is scheduled to run
void Climb::Execute() {
	RobotMap::cantalonClimb->Set(m_speed);
	//DriverStation::ReportError("Climb execute" + std::to_string(m_speed));
	//double current = RobotMap::cantalonClimb->GetOutputCurrent();
	//DriverStation::ReportError("Output current of motor: " + std::to_string(current));
}

// Make this return true when this Command no longer needs to run execute()
bool Climb::IsFinished() {
	double currentNow = RobotMap::cantalonClimb->GetOutputCurrent();
	if (currentNow > maxCurrent) {
		spikeCounter++;
		DriverStation::ReportError("Spike Counter: " + std::to_string(spikeCounter));
	} else {
		if (spikeCounter > maxSpikeCounter) {
			maxSpikeCounter = spikeCounter;
		}
		spikeCounter = 0;
	}
	DriverStation::ReportError("Output current of motor: " + std::to_string(currentNow));
	DriverStation::ReportError("pike Counter: " + std::to_string(spikeCounter));
	DriverStation::ReportError("maxSpike Counter: " + std::to_string(maxSpikeCounter));
	if (spikeCounter > 8) {
		m_speed = 0.0;
		return true;
	}

	return false;
}

// Called once after isFinished returns true
void Climb::End() {
	DriverStation::ReportError("Climb end"+ std::to_string(m_speed));
	RobotMap::cantalonClimb->Set(0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Climb::Interrupted() {
	End();
}





