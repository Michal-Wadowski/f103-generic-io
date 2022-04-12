/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_WRITEPIN_H_
#define CORE_SRC_COMMAND_WRITEPIN_H_

#include "GenericCommand.h"
#include "usbd_cdc_if.h"

class WritePin: public GenericCommand
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
			GPIO_PinState set = bytesReader->popUInt8() ? GPIO_PIN_SET : GPIO_PIN_RESET;

			if (!bytesReader->isOverrun()) {
				HAL_GPIO_WritePin(port, pin, set);
				sendOk(WRITE_PIN_RESPONSE);
			}
		}
	}
};

#endif /* CORE_SRC_COMMAND_WRITEPIN_H_ */
