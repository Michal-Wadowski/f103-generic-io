/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_NVIC_ENABLEIRQ_H_
#define CORE_SRC_COMMAND_NVIC_ENABLEIRQ_H_

#include "GenericCommand.h"
#include "stm32f1xx_hal.h"

extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;

extern uint8_t adcDataBuffer[64];

class NVIC_EnableIRQ: public GenericCommand
{
public:
	static void receivedCommand(BytesReader * bytesReader) {

		IRQn_Type irq = (IRQn_Type)bytesReader->popUInt32();
		uint8_t enable = bytesReader->popUInt8();

		if (bytesReader->isOverrun()) {
			return;
		}

		if (enable) {
			HAL_NVIC_EnableIRQ(irq);
		} else {
			HAL_NVIC_DisableIRQ(irq);
		}

		sendOk(NVIC_ENABLE_IRQ_RESPONSE);
	}
};

#endif /* CORE_SRC_COMMAND_NVIC_ENABLEIRQ_H_ */
