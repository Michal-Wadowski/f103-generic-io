/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_DMA_INIT_H_
#define CORE_SRC_COMMAND_DMA_INIT_H_

#include "GenericCommand.h"
#include "stm32f1xx_hal.h"

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

extern uint8_t adcDataBuffer[64];

class DMA_Init: public GenericCommand
{
public:
	static void receivedCommand(BytesReader * bytesReader) {


		uint8_t channel = bytesReader->popUInt8();

		switch (channel) {
		case 1:
			hdma_adc1.Instance = DMA1_Channel1;
			break;

		case 2:
			hdma_adc1.Instance = DMA1_Channel2;
			break;

		case 3:
			hdma_adc1.Instance = DMA1_Channel3;
			break;

		case 4:
			hdma_adc1.Instance = DMA1_Channel4;
			break;

		case 5:
			hdma_adc1.Instance = DMA1_Channel5;
			break;

		case 6:
			hdma_adc1.Instance = DMA1_Channel6;
			break;

		case 7:
			hdma_adc1.Instance = DMA1_Channel7;
			break;

		default:
			return;
		}

		hdma_adc1.Init.Direction = bytesReader->popUInt32();
		hdma_adc1.Init.PeriphInc = bytesReader->popUInt32();
		hdma_adc1.Init.MemInc = bytesReader->popUInt32();
		hdma_adc1.Init.PeriphDataAlignment = bytesReader->popUInt32();
		hdma_adc1.Init.MemDataAlignment = bytesReader->popUInt32();
		hdma_adc1.Init.Mode = bytesReader->popUInt32();
		hdma_adc1.Init.Priority = bytesReader->popUInt32();


		if (bytesReader->isOverrun()) {
			return;
		}


		if (HAL_DMA_Init(&hdma_adc1) != HAL_OK)
		{
			Error_Handler();
		}


		sendOk(DMA_INIT_RESPONSE);
	}
};

#endif /* CORE_SRC_COMMAND_DMA_INIT_H_ */
