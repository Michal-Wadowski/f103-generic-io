/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_TIM_INIT_H_
#define CORE_SRC_COMMAND_TIM_INIT_H_

#include "GenericTimer.h"

class TIM_Init: public GenericTimer
{
public:
	static void receivedCommand(BytesReader * bytesReader) {
		TIM_Mode mode = (TIM_Mode)bytesReader->popUInt8();
		uint8_t timer = bytesReader->popUInt8();

		if (timer >= 0 && timer <= 3 && !htimEnabled[timer]) {

			if (mode == PWM) {
				uint32_t prescaler = bytesReader->popUInt32();
				uint32_t counterMode = bytesReader->popUInt32();
				uint32_t period = bytesReader->popUInt32();
				uint32_t clockDivision = bytesReader->popUInt32();
				uint32_t repetitionCounter = bytesReader->popUInt32();
				uint32_t autoReloadPreload = bytesReader->popUInt32();

				if (!bytesReader->isOverrun()) {
					memset(&htim[timer], 0, sizeof(TIM_HandleTypeDef));
					htimEnabled[timer] = 1;

					switch (timer) {
					case 0:
						htim[timer].Instance = TIM1;
						__HAL_RCC_TIM1_CLK_ENABLE();
						break;
					case 1:
						htim[timer].Instance = TIM2;
						__HAL_RCC_TIM2_CLK_ENABLE();
						__HAL_AFIO_REMAP_TIM2_ENABLE();
						break;
					case 2:
						htim[timer].Instance = TIM3;
						__HAL_RCC_TIM3_CLK_ENABLE();
						break;
					case 3:
						htim[timer].Instance = TIM4;
						__HAL_RCC_TIM4_CLK_ENABLE();
						break;
					default:
						return;
					}

					htim[timer].Init.Prescaler = prescaler;
					htim[timer].Init.CounterMode = counterMode;
					htim[timer].Init.Period = period;
					htim[timer].Init.ClockDivision = clockDivision;
					htim[timer].Init.RepetitionCounter = repetitionCounter;
					htim[timer].Init.AutoReloadPreload = autoReloadPreload;
					HAL_TIM_PWM_Init(&htim[timer]);

					sendOk(TIM_INIT_RESPONSE);
				}
			} else if (mode == ENCODER) {
				TIM_Encoder_InitTypeDef encoderConfig = {0};

				uint32_t prescaler = bytesReader->popUInt32();
				uint32_t counterMode = bytesReader->popUInt32();
				uint32_t period = bytesReader->popUInt32();
				uint32_t clockDivision = bytesReader->popUInt32();
				uint32_t autoReloadPreload = bytesReader->popUInt32();


				encoderConfig.EncoderMode = bytesReader->popUInt32();
				encoderConfig.IC1Polarity = bytesReader->popUInt32();
				encoderConfig.IC1Selection = bytesReader->popUInt32();
				encoderConfig.IC1Prescaler = bytesReader->popUInt32();
				encoderConfig.IC1Filter = bytesReader->popUInt32();
				encoderConfig.IC2Polarity = bytesReader->popUInt32();
				encoderConfig.IC2Selection = bytesReader->popUInt32();
				encoderConfig.IC2Prescaler = bytesReader->popUInt32();
				encoderConfig.IC2Filter = bytesReader->popUInt32();

				if (!bytesReader->isOverrun()) {
					memset(&htim[timer], 0, sizeof(TIM_HandleTypeDef));
					htimEnabled[timer] = 1;

					switch (timer) {
					case 0:
						htim[timer].Instance = TIM1;
						__HAL_RCC_TIM1_CLK_ENABLE();
						break;
					case 1:
						htim[timer].Instance = TIM2;
						__HAL_RCC_TIM2_CLK_ENABLE();
						break;
					case 2:
						htim[timer].Instance = TIM3;
						__HAL_RCC_TIM3_CLK_ENABLE();
						break;
					case 3:
						htim[timer].Instance = TIM4;
						__HAL_RCC_TIM4_CLK_ENABLE();
						break;
					default:
						return;
					}

					htim[timer].Init.Prescaler = prescaler;
					htim[timer].Init.CounterMode = counterMode;
					htim[timer].Init.Period = period;
					htim[timer].Init.ClockDivision = clockDivision;
					htim[timer].Init.AutoReloadPreload = autoReloadPreload;
					HAL_TIM_Encoder_Init(&htim[timer], &encoderConfig);

					sendOk(TIM_INIT_RESPONSE);
				}
			}
		}
	}
};

#endif /* CORE_SRC_COMMAND_TIM_INIT_H_ */
