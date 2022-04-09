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
#include "command/PingCommand.h"
#include "command/WritePin.h"
#include "command/ReadPin.h"
#include "command/GPIOInit.h"

class Application
{
public:
	Application() : commands()
	{
		commands[PING_COMMAND] = new PingCommand();
		commands[WRITE_PIN] = new WritePin();
		commands[READ_PIN] = new ReadPin();
		commands[GPIO_INIT] = new GPIOInit();
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
