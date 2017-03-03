/*
 * ButtonBoard.cpp
 *
 *  Created on: Feb 25, 2017
 *      Author: Liao_Family
 */
#include "ButtonBoard.h"
#include "../RobotMap.h"
#include "../Commands/SolenoidClaspCommand.h"
#include "../Commands/Climb.h"

ButtonBoard::ButtonBoard(int port):Joystick(port){
	gearClose = new JoystickButton(this, PORT_GEAR_CLOSE);
	gearOpen = new JoystickButton(this, PORT_GEAR_OPEN);
	armUp = new JoystickButton(this, PORT_ARM_UP);
	armDown = new JoystickButton(this, PORT_ARM_DOWN);
	fastSpeed = new JoystickButton(this, PORT_FAST_SPEED);
	slowSpeed = new JoystickButton(this, PORT_SLOW_SPEED);
	climbRope = new JoystickButton(this, PORT_CLIMB_ROPE);
	//robotUp = new JoystickButton(this, PORT_ROBOT_UP);

	gearClose->WhenPressed(new SolenoidClaspCommand(0, 0));
	gearOpen->WhenPressed(new SolenoidClaspCommand(1, 0));

	armUp->WhenPressed(new SolenoidClaspCommand(0, 1));
	armDown->WhenPressed(new SolenoidClaspCommand(1, 1));

	fastSpeed->WhenPressed(new SolenoidClaspCommand(0, 2));
	slowSpeed->WhenPressed(new SolenoidClaspCommand(1, 2));

	climbRope->WhileHeld(new Climb(0.50));
	//climbRope->WhenReleased(new Climb(0.0));

}
ButtonBoard::~ButtonBoard(){
	delete gearClose;
	delete gearOpen;
	delete armUp;
	delete armDown;
	delete fastSpeed;
	delete slowSpeed;
	delete climbRope;
}








