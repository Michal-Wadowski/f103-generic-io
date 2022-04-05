/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_GPIOINIT_H_
#define CORE_SRC_COMMAND_GPIOINIT_H_

#include "GenericCommand.h"
#include "usbd_cdc_if.h"

class GPIOInit: public GenericCommand
{
public:
	virtual ~GPIOInit() {};
	virtual void receivedCommand(uint8_t * data, uint16_t size) {
		if (size == 15+2) {
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
			default:
				return;
			}

			if (port != NULL) {
				uint16_t pin = *((uint16_t*)&data[1]);
				uint32_t mode = *((uint32_t*)&data[3]);
				uint32_t pull = *((uint32_t*)&data[7]);
				uint32_t speed = *((uint32_t*)&data[11]);

				GPIO_InitTypeDef GPIO_InitStruct = {pin, mode, pull, speed};


				HAL_GPIO_Init(port, &GPIO_InitStruct);

				sendOk();
			}
		}
	}

	void sendOk()
	{
		uint8_t txBuf[4];
		((uint16_t*) (txBuf))[0] = 2; // size
		((uint16_t*) (txBuf))[1] = GPIO_INIT_OK;
		sendResponse(txBuf, 4);
	}
};

#endif /* CORE_SRC_COMMAND_GPIOINIT_H_ */
