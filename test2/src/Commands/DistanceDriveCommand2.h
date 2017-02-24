/*
 * DistanceDriveCommand2.h
 *
 *  Created on: Feb 24, 2017
 *      Author: Liao_Family
 */

#ifndef SRC_COMMANDS_DISTANCEDRIVECOMMAND2_H_
#define SRC_COMMANDS_DISTANCEDRIVECOMMAND2_H_


#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class DistanceDriveCommand2: public Command , public PIDOutput
{
public:
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR
	DistanceDriveCommand2(double);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual void PIDWrite(double);

	double getDriveDistance();
	int getPosition();

private:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=VARIABLES

	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=VARIABLES

	Timer* m_resetTimer;
	double deltaT = 0.0;
	double m_distance=0.0;
    double kDefaultPeriod = .05;
	double kGravity = 32.174;

	 double  lastAccelEst[2];
	 double  lastVelEst[2];
	 double lastPosEst[2] ;

		PIDController *turnController;      // PID Controller

		double rotateToAngleRate;

		int initEncPosition=0;
};


#endif /* SRC_COMMANDS_DISTANCEDRIVECOMMAND2_H_ */
