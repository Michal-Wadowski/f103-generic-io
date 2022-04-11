/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_TIM_INIT_H_
#define CORE_SRC_COMMAND_TIM_INIT_H_

#include "GenericCommand.h"
#include "usbd_cdc_if.h"

extern TIM_HandleTypeDef * htim[4];

class TIM_Init: public GenericCommand
{
public:
	virtual ~TIM_Init() {};
	virtual void receivedCommand(BytesReader * bytesReader) {
		TIM_Mode mode = (TIM_Mode)bytesReader->popUInt8();
		uint8_t timer = bytesReader->popUInt8();

		if (timer >= 0 && timer <= 4 && htim[timer] == NULL) {

			if (mode == PWM) {
				uint32_t prescaler = bytesReader->popUInt32();
				uint32_t counterMode = bytesReader->popUInt32();
				uint32_t period = bytesReader->popUInt32();
				uint32_t clockDivision = bytesReader->popUInt32();
				uint32_t repetitionCounter = bytesReader->popUInt32();
				uint32_t autoReloadPreload = bytesReader->popUInt32();

				if (!bytesReader->isOverrun()) {
					htim[timer] = new TIM_HandleTypeDef();
					memset(htim[timer], 0, sizeof(TIM_HandleTypeDef));

					switch (timer) {
					case 0:
						htim[timer]->Instance = TIM1;
						break;
					case 1:
						htim[timer]->Instance = TIM2;
						break;
					case 2:
						htim[timer]->Instance = TIM3;
						break;
					case 3:
						htim[timer]->Instance = TIM4;
						break;
					default:
						return;
					}

					htim[timer]->Init.Prescaler = prescaler;
					htim[timer]->Init.CounterMode = counterMode;
					htim[timer]->Init.Period = period;
					htim[timer]->Init.ClockDivision = clockDivision;
					htim[timer]->Init.RepetitionCounter = repetitionCounter;
					htim[timer]->Init.AutoReloadPreload = autoReloadPreload;
					HAL_TIM_PWM_Init(htim[timer]);

					sendOk();
				}
			}
		}
	}

	void sendOk()
	{
		uint8_t txBuf[4];
		((uint16_t*) (txBuf))[0] = 2; // size
		((uint16_t*) (txBuf))[1] = TIM_INIT_RESPONSE;
		sendResponse(txBuf, 4);
	}
};

#endif /* CORE_SRC_COMMAND_TIM_INIT_H_ */