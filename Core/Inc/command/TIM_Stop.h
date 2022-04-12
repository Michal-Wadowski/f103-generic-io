/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_TIM_STOP_H_
#define CORE_SRC_COMMAND_TIM_STOP_H_

#include "GenericTimer.h"

class TIM_Stop: public GenericTimer
{
public:
	static void receivedCommand(BytesReader * bytesReader) {
		TIM_Mode mode = (TIM_Mode)bytesReader->popUInt8();

		uint8_t timer = bytesReader->popUInt8();
		uint8_t channel = bytesReader->popUInt8();

		if (timer >= 0 && timer <= 4 && htimEnabled[timer]) {

			if (mode == PWM) {
				if (!bytesReader->isOverrun()) {
					HAL_TIM_PWM_Stop(&htim[timer], channel);
					sendOk(TIM_STOP_RESPONSE);
				}
			} else {
				if (mode == ENCODER) {
					if (!bytesReader->isOverrun()) {
						HAL_TIM_Encoder_Stop(&htim[timer], channel);
						sendOk(TIM_STOP_RESPONSE);
					}
				}
			}
		}
	}
};

#endif /* CORE_SRC_COMMAND_TIM_STOP_H_ */
