#ifndef WAIT_H
#define WAIT_H
#include "WPILib.h"

class WaitTime: public Command {
public:
	WaitTime(double);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual ~WaitTime();
	Timer *timer;
private:
	double m_time;
	double initialTime;
};

#endif /* SRC_COMMANDS_WAIT_H_ */
