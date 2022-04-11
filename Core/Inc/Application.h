/*
 * Application.h
 *
 *  Created on: Apr 2, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_APPLICATION_H_
#define CORE_SRC_APPLICATION_H_

#include "UsbBuffer.h"
#include "usbd_cdc_if.h"
#include <string.h>
#include "command/GenericCommand.h"
#include "command/GPIOInit.h"
#include "command/PingCommand.h"
#include "command/WritePin.h"
#include "command/ReadPin.h"
#include "command/TIM_Start.h"
#include "command/TIM_Stop.h"
#include "command/TIM_Init.h"
#include "command/TIM_DeInit.h"
#include "command/TIM_ConfigChannel.h"
#include "command/TIM_InstanceUpdate.h"

class Application
{
public:
	Application() : commands()
	{
		commands[PING_COMMAND] = new PingCommand();
		commands[WRITE_PIN] = new WritePin();
		commands[READ_PIN] = new ReadPin();
		commands[GPIO_INIT] = new GPIOInit();
		commands[TIM_START] = new TIM_Start();
		commands[TIM_STOP] = new TIM_Stop();
		commands[TIM_INIT] = new TIM_Init();
		commands[TIM_DEINIT] = new TIM_DeInit();
		commands[TIM_CONFIG_CHANNEL] = new TIM_ConfigChannel();
		commands[TIM_INSTANCE_UPDATE] = new TIM_InstanceUpdate();
	}

	void usbDataReceived(uint8_t * buf, uint32_t len)
	{
		usbBuffer.append(buf, len);
	}

	void loopIteration()
	{
		do
		{
			BytesReader * dataItem = usbBuffer.ingest();
			if (dataItem == NULL)
			{
				break;
			}

			if (dataItem->size() > 2) {
				uint16_t size = dataItem->popUInt16();
				if (size >= 2 && dataItem->dataLeft() >= size)
				{
					uint16_t command = dataItem->popUInt16();
					if (commands[command] != NULL)
					{
						commands[command]->receivedCommand(dataItem);
					}
				}
			}

			delete dataItem;

		} while (true);
	}

protected:
	UsbBuffer usbBuffer;

	GenericCommand * commands[16];
};


#endif /* CORE_SRC_APPLICATION_H_ */
