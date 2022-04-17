/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_ADCSTART_H_
#define CORE_SRC_COMMAND_ADCSTART_H_

#include "GenericCommand.h"
#include "stm32f1xx_hal.h"

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

extern uint8_t * adcDataBuffer;
extern uint8_t * adcResponseBuffer;
extern uint32_t adcDataBufferSize;

enum ADC_Start_Mode {
	ADC_MODE_DMA
};

class ADC_Start: public GenericCommand
{
public:
	static void receivedCommand(BytesReader * bytesReader) {

		uint8_t adcInstance = bytesReader->popUInt8();
		ADC_Start_Mode mode = (ADC_Start_Mode)bytesReader->popUInt8();
		bool start = (bool)bytesReader->popUInt8();
		uint32_t size = (uint32_t)bytesReader->popUInt32();

		if (bytesReader->isOverrun()) {
			return;
		}

		if (adcDataBufferSize != 0) {
			free(adcDataBuffer);
			free(adcResponseBuffer);
			adcDataBuffer = NULL;
			adcResponseBuffer = NULL;
		}
		if (size > 0) {
			adcDataBuffer = (uint8_t*)malloc(size);
			adcResponseBuffer = (uint8_t*)malloc(size);
		}
		adcDataBufferSize = size;

		if (mode == ADC_MODE_DMA) {
			if (adcDataBufferSize > 0) {
				HAL_ADCEx_Calibration_Start(&hadc1);

				__HAL_LINKDMA(&hadc1, DMA_Handle, hdma_adc1);

				if (start) {
					if (HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adcDataBuffer, adcDataBufferSize / 2)  != HAL_OK) {
						Error_Handler();
					}
				} else {
					HAL_ADC_Stop_DMA(&hadc1);
				}

				sendOk(ADC_START_RESPONSE);
			}
		}

	}
};

#endif /* CORE_SRC_COMMAND_ADCSTART_H_ */
