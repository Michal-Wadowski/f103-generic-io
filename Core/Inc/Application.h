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
#include "command/TIM_InstanceRead.h"
#include "command/DMA_Init.h"
#include "command/ADC_ConfigChannel.h"
#include "command/ADC_Start.h"
#include "command/ADC_Init.h"
#include "command/NVIC_SetPriority.h"
#include "command/NVIC_EnableIRQ.h"
#include "command/CommandUtils.h"

class Application
{
public:
	Application() : commands()
	{
		commands[PING_COMMAND] = PingCommand::receivedCommand;
		commands[WRITE_PIN] = WritePin::receivedCommand;
		commands[READ_PIN] = ReadPin::receivedCommand;
		commands[GPIO_INIT] = GPIOInit::receivedCommand;
		commands[TIM_START] = TIM_Start::receivedCommand;
		commands[TIM_STOP] = TIM_Stop::receivedCommand;
		commands[TIM_INIT] = TIM_Init::receivedCommand;
		commands[TIM_DEINIT] = TIM_DeInit::receivedCommand;
		commands[TIM_CONFIG_CHANNEL] = TIM_ConfigChannel::receivedCommand;
		commands[TIM_INSTANCE_UPDATE] = TIM_InstanceUpdate::receivedCommand;
		commands[TIM_INSTANCE_READ] = TIM_InstanceRead::receivedCommand;
		commands[DMA_INIT] = DMA_Init::receivedCommand;
		commands[ADC_INIT] = ADC_Init::receivedCommand;
		commands[ADC_CONFIG_CHANNEL] = ADC_ConfigChannel::receivedCommand;
		commands[ADC_START] = ADC_Start::receivedCommand;
		commands[NVIC_SET_PRIORITY] = NVIC_SetPriority::receivedCommand;
		commands[NVIC_ENABLE_IRQ] = NVIC_EnableIRQ::receivedCommand;
		commands[COMMAND_UTILS] = CommandUtils::receivedCommand;
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
						(*commands[command])(dataItem);
					}
				}
			}

		} while (true);
	}

	void adcConversionComplete(ADC_HandleTypeDef* hadc, uint8_t part) {
		CommandUtils::adcConversionCompleteHandler(hadc, part);
	}

protected:
	UsbBuffer usbBuffer;

	receivedCommand commands[16];
};


#endif /* CORE_SRC_APPLICATION_H_ */
