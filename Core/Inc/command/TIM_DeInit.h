/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_TIM_DEINIT_H_
#define CORE_SRC_COMMAND_TIM_DEINIT_H_

#include "GenericTimer.h"
#include "usbd_cdc_if.h"

class TIM_DeInit: public GenericTimer
{
public:
	static void receivedCommand(BytesReader * bytesReader) {
		TIM_Mode mode = (TIM_Mode)bytesReader->popUInt8();
		uint8_t timer = bytesReader->popUInt8();

		if (timer >= 0 && timer <= 4 && htimEnabled[timer]) {


			if (mode == PWM) {
				if (!bytesReader->isOverrun()) {
					HAL_TIM_PWM_DeInit(&htim[timer]);

					if (htim[timer].Instance == TIM1) {
						__HAL_RCC_TIM1_CLK_DISABLE();
					} else if (htim[timer].Instance == TIM2) {
						__HAL_RCC_TIM2_CLK_DISABLE();
					} else if (htim[timer].Instance == TIM3) {
						__HAL_RCC_TIM3_CLK_DISABLE();
					} else if (htim[timer].Instance == TIM4) {
						__HAL_RCC_TIM4_CLK_DISABLE();
					}


					htimEnabled[timer] = 0;
					sendOk(TIM_DEINIT_RESPONSE);
				}
			} else {
				if (mode == ENCODER) {
					if (!bytesReader->isOverrun()) {
						HAL_TIM_Encoder_DeInit(&htim[timer]);

						if (htim[timer].Instance == TIM1) {
							__HAL_RCC_TIM1_CLK_DISABLE();
						} else if (htim[timer].Instance == TIM2) {
							__HAL_RCC_TIM2_CLK_DISABLE();
						} else if (htim[timer].Instance == TIM3) {
							__HAL_RCC_TIM3_CLK_DISABLE();
						} else if (htim[timer].Instance == TIM4) {
							__HAL_RCC_TIM4_CLK_DISABLE();
						}


						htimEnabled[timer] = 0;
						sendOk(TIM_DEINIT_RESPONSE);
					}
				}
			}
		}
	}
};

#endif /* CORE_SRC_COMMAND_TIM_DEINIT_H_ */
