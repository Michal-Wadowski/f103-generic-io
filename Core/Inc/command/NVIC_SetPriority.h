/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_NVIC_SETPRIORITY_H_
#define CORE_SRC_COMMAND_NVIC_SETPRIORITY_H_

#include "GenericCommand.h"
#include "stm32f1xx_hal.h"


class NVIC_SetPriority: public GenericCommand
{
public:
	static void receivedCommand(BytesReader * bytesReader) {

		IRQn_Type irq = (IRQn_Type)bytesReader->popUInt32();
		uint32_t preemptPriority = bytesReader->popUInt32();
		uint32_t subPriority = bytesReader->popUInt32();

		if (bytesReader->isOverrun()) {
			return;
		}

		HAL_NVIC_SetPriority(irq, preemptPriority, subPriority);

		sendOk(NVIC_SET_PRIORITY_RESPONSE);
	}
};

#endif /* CORE_SRC_COMMAND_NVIC_SETPRIORITY_H_ */
