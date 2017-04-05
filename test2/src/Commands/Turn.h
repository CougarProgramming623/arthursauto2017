#ifndef Turn_H
#define Turn_H

#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "AHRS.h"
#include "../RobotMap.h"

class Turn : public Command, public PIDOutput {
public:

    AHRS *ahrs;                         // navX-MXP
    PIDController *turnController;// PID Controller
    double rotateToAngleRate;           // Current rotation rate
    double initialAngle;
  Turn(double);
  void Initialize();
  void Execute();
  bool IsFinished();
  void End();
  void Interrupted();
  virtual void PIDWrite(double output) {
  	this->rotateToAngleRate = output;
  }

private:
  double m_angle = 0.0;
  Timer *turnTimer;
};

#endif  // Turn_H
