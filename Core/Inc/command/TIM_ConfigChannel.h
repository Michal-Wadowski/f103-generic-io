/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_TIM_CONFIGCHANNEL_H_
#define CORE_SRC_COMMAND_TIM_CONFIGCHANNEL_H_

#include "GenericCommand.h"
#include "usbd_cdc_if.h"

extern TIM_HandleTypeDef * htim[4];

class TIM_ConfigChannel: public GenericCommand
{
public:
	virtual ~TIM_ConfigChannel() {};
	virtual void receivedCommand(BytesReader * bytesReader) {
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

		if (timer >= 0 && timer <= 4 && htim[timer] != NULL) {
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
					HAL_TIM_PWM_ConfigChannel(htim[timer], &sConfigOC, channel);


					sendOk();
				}
			}
		}
	}

	void sendOk()
	{
		uint8_t txBuf[4];
		((uint16_t*) (txBuf))[0] = 2; // size
		((uint16_t*) (txBuf))[1] = TIM_CONFIG_CHANNEL_RESPONSE;
		sendResponse(txBuf, 4);
	}
};

#endif /* CORE_SRC_COMMAND_TIM_CONFIGCHANNEL_H_ */
