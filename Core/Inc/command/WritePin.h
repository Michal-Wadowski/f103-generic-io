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
	virtual ~WritePin() {};
	virtual void receivedCommand(uint8_t * data, uint16_t size) {
		if (size == 4+2) {
			GPIO_TypeDef * port;
			switch (data[0]) {
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
			}

			if (port != NULL) {
				uint16_t pin = *((uint16_t*)&data[1]);
				GPIO_PinState set = data[3] ? GPIO_PIN_SET : GPIO_PIN_RESET;

				HAL_GPIO_WritePin(port, pin, set);

				sendOk();
			}
		}
	}

	void sendOk()
	{
		uint8_t txBuf[4];
		((uint16_t*) (txBuf))[0] = 2; // size
		((uint16_t*) (txBuf))[1] = WRITE_PIN_OK;
		sendResponse(txBuf, 4);
	}
};

#endif /* CORE_SRC_COMMAND_WRITEPIN_H_ */
