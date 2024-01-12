/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_TIM_CONFIGCHANNEL_H_
#define CORE_SRC_COMMAND_TIM_CONFIGCHANNEL_H_

#include "GenericTimer.h"

class TIM_ConfigChannel: public GenericTimer
{
public:
	static void receivedCommand(BytesReader * bytesReader) {
		TIM_Mode mode = (TIM_Mode)bytesReader->popUInt8();
		uint8_t timer = bytesReader->popUInt8();
		uint8_t channel = bytesReader->popUInt8();

		uint32_t ocMode = bytesReader->popUInt32();

		uint32_t pulse = bytesReader->popUInt32();

		uint32_t ocPolarity = bytesReader->popUInt32();
		uint32_t ocnPolarity = bytesReader->popUInt32();
		uint32_t ocFastMode = bytesReader->popUInt32();
		uint32_t ocIdleState = bytesReader->popUInt32();
		uint32_t ocnIdleState = bytesReader->popUInt32();

		if (timer >= 0 && timer <= 3 && htimEnabled[timer]) {
			if (mode == PWM) {
				if (!bytesReader->isOverrun()) {

					TIM_OC_InitTypeDef sConfigOC = {0};
					sConfigOC.OCMode = ocMode;
					sConfigOC.Pulse = pulse;
					sConfigOC.OCPolarity = ocPolarity;
					sConfigOC.OCNPolarity = ocnPolarity;
					sConfigOC.OCFastMode = ocFastMode;
					sConfigOC.OCIdleState = ocIdleState;
					sConfigOC.OCNIdleState = ocnIdleState;
					HAL_TIM_PWM_ConfigChannel(&htim[timer], &sConfigOC, channel);


					sendOk(TIM_CONFIG_CHANNEL_RESPONSE);
				}
			}
		}
	}
};

#endif /* CORE_SRC_COMMAND_TIM_CONFIGCHANNEL_H_ */
