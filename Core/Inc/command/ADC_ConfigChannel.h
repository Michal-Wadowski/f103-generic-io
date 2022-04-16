/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_ADCCONFIGCHANNEL_H_
#define CORE_SRC_COMMAND_ADCCONFIGCHANNEL_H_

#include "GenericCommand.h"
#include "stm32f1xx_hal.h"

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

extern uint8_t adcDataBuffer[64];

class ADC_ConfigChannel: public GenericCommand
{
public:
	static void receivedCommand(BytesReader * bytesReader) {

		uint8_t adcInstance = bytesReader->popUInt8();

		ADC_ChannelConfTypeDef sConfig = {
				bytesReader->popUInt32(), bytesReader->popUInt32(), bytesReader->popUInt32()
		};

		if (bytesReader->isOverrun()) {
			return;
		}

		if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
		{
			Error_Handler();
		}

		sendOk(ADC_CONFIG_CHANNEL_RESPONSE);

	}
};

#endif /* CORE_SRC_COMMAND_ADCCONFIGCHANNEL_H_ */
