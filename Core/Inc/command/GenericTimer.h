/*
 * GenericTimer.h
 *
 *  Created on: Apr 12, 2022
 *      Author: developer
 */

#ifndef CORE_INC_COMMAND_GENERICTIMER_H_
#define CORE_INC_COMMAND_GENERICTIMER_H_

#include "usbd_cdc_if.h"
#include "GenericCommand.h"

extern TIM_HandleTypeDef htim[4];
extern uint8_t htimEnabled[4];

enum TIM_Mode {
	PWM,
	ENCODER
};

class GenericTimer: public GenericCommand {
protected:
	static TIM_HandleTypeDef htim[4];
	static uint8_t htimEnabled[4];
};

#endif /* CORE_INC_COMMAND_GENERICTIMER_H_ */
