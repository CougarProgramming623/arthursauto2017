/*
 * AutoCommandGroup.h
 *
 *  Created on: Feb 22, 2017
 *      Author: Liao_Family
 */

#ifndef SRC_COMMANDS_AUTOCOMMANDGROUP_H_
#define SRC_COMMANDS_AUTOCOMMANDGROUP_H_


#include "Commands/Command.h"
#include "Commands/CommandGroup.h"


class AutoCommandGroup : public CommandGroup
{

  public:
   AutoCommandGroup(int);
   int option;// will be 0, 1, 2 or nothing

};



#endif /* SRC_COMMANDS_AUTOCOMMANDGROUP_H_ */
