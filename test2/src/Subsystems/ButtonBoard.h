#ifndef SUBSYSTEMS_BUTTONBOARD_H_
#define SUBSYSTEMS_BUTTONBOARD_H_

#include "JoyStick.h"
#include "Buttons/JoystickButton.h"

#define PORT_GEAR_CLOSE 5
#define PORT_GEAR_OPEN 6
#define PORT_ARM_UP 1
#define PORT_ARM_DOWN 2
#define PORT_FAST_SPEED 3
#define PORT_SLOW_SPEED 4
#define PORT_CLIMB_ROPE 7
#define PORT_ROBOT_UP 8//not sure if this will be implemented yet

class ButtonBoard: public Joystick{
private:
	JoystickButton *gearOpen;
	JoystickButton *gearClose;
	JoystickButton *armUp;
	JoystickButton *armDown;
	JoystickButton *fastSpeed;
	JoystickButton *slowSpeed;
	JoystickButton *climbRope;
	//JoystickButton *robotUp;

public:
	ButtonBoard(int);
	~ButtonBoard();
};




#endif /* SUBSYSTEMS_BUTTONBOARD_H_ */
