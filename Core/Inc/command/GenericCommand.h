/*
 * GenericCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_GENERICCOMMAND_H_
#define CORE_SRC_COMMAND_GENERICCOMMAND_H_

#include "stm32f1xx_hal.h"

class GenericCommand
{
public:
	virtual ~GenericCommand() {};
	virtual void receivedCommand(uint8_t * data, uint16_t size) = 0;
};

#endif /* CORE_SRC_COMMAND_GENERICCOMMAND_H_ */
