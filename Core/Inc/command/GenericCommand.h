/*
 * GenericCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_GENERICCOMMAND_H_
#define CORE_SRC_COMMAND_GENERICCOMMAND_H_

#include "stm32f1xx_hal.h"

typedef enum {
	PING_COMMAND,
	PONG_COMMAND,
	WRITE_PIN,
	WRITE_PIN_OK,
	READ_PIN,
	READ_PIN_RESULT,
	GPIO_INIT,
	GPIO_INIT_OK
} CommandIds;

class GenericCommand
{
public:
	virtual ~GenericCommand() {};
	virtual void receivedCommand(BytesReader * bytesReader) = 0;

protected:
	virtual void sendResponse(uint8_t * data, uint16_t size) {
		while (CDC_Transmit_FS((uint8_t*) (data), size) != USBD_OK);
	}
};

#endif /* CORE_SRC_COMMAND_GENERICCOMMAND_H_ */
