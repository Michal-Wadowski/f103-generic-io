/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_GPIOINIT_H_
#define CORE_SRC_COMMAND_GPIOINIT_H_

#include "GenericCommand.h"
#include "stm32f1xx_hal.h"

class GPIOInit: public GenericCommand
{
public:
	static void receivedCommand(BytesReader * bytesReader) {

		GPIO_TypeDef * port;
		switch (bytesReader->popUInt8()) {
		case 0:
			port = GPIOA;
			break;
		case 1:
			port = GPIOB;
			break;
		case 2:
			port = GPIOC;
			break;
		case 3:
			port = GPIOD;
			break;
		case 4:
			port = GPIOE;
			break;
		default:
			return;
		}

		if (port != NULL) {
			uint16_t pin = bytesReader->popUInt16();
			uint32_t mode = bytesReader->popUInt32();
			uint32_t pull = bytesReader->popUInt32();
			uint32_t speed = bytesReader->popUInt32();

			GPIO_InitTypeDef GPIO_InitStruct = {pin, mode, pull, speed};

			if (!bytesReader->isOverrun()) {
				HAL_GPIO_Init(port, &GPIO_InitStruct);

				sendOk(GPIO_INIT_RESPONSE);
			}
		}

	}

};

#endif /* CORE_SRC_COMMAND_GPIOINIT_H_ */
