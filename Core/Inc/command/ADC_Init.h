/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_ADCINIT_H_
#define CORE_SRC_COMMAND_ADCINIT_H_

#include "GenericCommand.h"
#include "stm32f1xx_hal.h"

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

extern uint8_t adcDataBuffer[64];

class ADC_Init: public GenericCommand
{
public:
	static void receivedCommand(BytesReader * bytesReader) {

		switch (bytesReader->popUInt8()) {
		case 0:
			hadc1.Instance = ADC1;
			break;

		case 1:
			hadc1.Instance = ADC2;
			break;

		default:
			return;
		}

		hadc1.Init.ScanConvMode = bytesReader->popUInt32();
		hadc1.Init.ContinuousConvMode = (FunctionalState)bytesReader->popUInt8();
		hadc1.Init.DiscontinuousConvMode = (FunctionalState)bytesReader->popUInt8();
		hadc1.Init.ExternalTrigConv = bytesReader->popUInt32();
		hadc1.Init.DataAlign = bytesReader->popUInt32();
		hadc1.Init.NbrOfConversion = bytesReader->popUInt32();

		if (hadc1.Init.NbrOfConversion >= 1 && hadc1.Init.NbrOfConversion <= 16) {

			if (HAL_ADC_Init(&hadc1) != HAL_OK) {
				Error_Handler();
			}

			if (bytesReader->isOverrun()) {
				return;
			}

			sendOk(ADC_INIT_RESPONSE);
		}

	}
};

#endif /* CORE_SRC_COMMAND_ADCINIT_H_ */
