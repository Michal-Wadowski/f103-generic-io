/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_TIM_DEINIT_H_
#define CORE_SRC_COMMAND_TIM_DEINIT_H_

#include "GenericCommand.h"
#include "usbd_cdc_if.h"

extern TIM_HandleTypeDef * htim[4];

class TIM_DeInit: public GenericCommand
{
public:
	virtual ~TIM_DeInit() {};
	virtual void receivedCommand(BytesReader * bytesReader) {
		TIM_Mode mode = (TIM_Mode)bytesReader->popUInt8();
		uint8_t timer = bytesReader->popUInt8();

		if (timer >= 0 && timer <= 4 && htim[timer] != NULL) {


			if (mode == PWM) {
				if (!bytesReader->isOverrun()) {
					HAL_TIM_PWM_DeInit(htim[timer]);
					delete htim[timer];
					htim[timer] = NULL;
					sendOk();
				}
			}
		}
	}

	void sendOk()
	{
		uint8_t txBuf[4];
		((uint16_t*) (txBuf))[0] = 2; // size
		((uint16_t*) (txBuf))[1] = TIM_DEINIT_RESPONSE;
		sendResponse(txBuf, 4);
	}
};

#endif /* CORE_SRC_COMMAND_TIM_DEINIT_H_ */