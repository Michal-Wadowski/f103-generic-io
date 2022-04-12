/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_READPIN_H_
#define CORE_SRC_COMMAND_READPIN_H_

#include "GenericCommand.h"

class ReadPin: public GenericCommand
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

			if (!bytesReader->isOverrun()) {
				GPIO_PinState set = HAL_GPIO_ReadPin(port, pin);
				sendResult(set & 0x1);
			}
		}

	}

	static void sendResult(uint8_t result)
	{
		uint8_t txBuf[16];

		BytesWriter bw = BytesWriter(txBuf);
		bw.pushUInt16(READ_PIN_RESPONSE);
		bw.pushUInt8(result);

		sendResponse(txBuf, bw.getTotalSize());
	}
};

#endif /* CORE_SRC_COMMAND_READPIN_H_ */
