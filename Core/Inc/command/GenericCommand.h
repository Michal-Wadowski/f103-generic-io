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

	WRITE_PIN,

	READ_PIN,

	GPIO_INIT,

	TIM_START,

	TIM_STOP,

	TIM_INIT,

	TIM_DEINIT,

	TIM_CONFIG_CHANNEL,

	TIM_INSTANCE_UPDATE,

	TIM_INSTANCE_READ
} CommandIds;

typedef enum {
	PONG_COMMAND,

	WRITE_PIN_RESPONSE,

	READ_PIN_RESPONSE,

	GPIO_INIT_RESPONSE,

	TIM_START_RESPONSE,

	TIM_STOP_RESPONSE,

	TIM_INIT_RESPONSE,

	TIM_DEINIT_RESPONSE,

	TIM_CONFIG_CHANNEL_RESPONSE,

	TIM_INSTANCE_UPDATE_RESPONSE,

	TIM_INSTANCE_READ_RESPONSE
} CommandResponseIds;

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
