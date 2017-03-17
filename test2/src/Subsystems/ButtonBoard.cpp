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
	gearPush = new JoystickButton(this, PORT_GEAR_PUSH);
	//robotUp = new JoystickButton(this, PORT_ROBOT_UP);

	gearClose->WhenPressed(new SolenoidClaspCommand(0, SPEED_SOLENOID));
	gearOpen->WhenPressed(new SolenoidClaspCommand(1, SPEED_SOLENOID));

	armUp->WhenPressed(new SolenoidClaspCommand(0, UPDOWN_SOLENOID));
	armDown->WhenPressed(new SolenoidClaspCommand(1, UPDOWN_SOLENOID));

	fastSpeed->WhenPressed(new SolenoidClaspCommand(0, OPENCLOSE_SOLENOID));
	slowSpeed->WhenPressed(new SolenoidClaspCommand(1, OPENCLOSE_SOLENOID));

	climbRope->WhileHeld(new Climb(1));
	//climbRope->WhenReleased(new Climb(0.0));

	gearPush->WhenPressed(new SolenoidClaspCommand(0, GEAR_PUSHER_SOLENOID));
	gearPush->WhenReleased(new SolenoidClaspCommand(1, GEAR_PUSHER_SOLENOID));

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








