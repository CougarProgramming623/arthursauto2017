/*
 * Wait.cpp
 *
 *  Created on: Feb 25, 2017
 *      Author: admin
 */

#include "WaitTime.h"
#include "WPILib.h"

WaitTime::WaitTime(double time): Command() {
	m_time = time;
}

void WaitTime::Initialize() {
	DriverStation::ReportError("Starting Timer: ");
	timer = new Timer();
	timer->Start();
	initialTime = timer->Get();
}
void WaitTime::Execute() {

}

bool WaitTime::IsFinished() {
	double timeZero = timer->Get();
	if (timeZero - initialTime >= m_time) {
		return true;
	}
	return false;
}
void WaitTime::End() {

}


WaitTime::~WaitTime() {
delete timer;
}

