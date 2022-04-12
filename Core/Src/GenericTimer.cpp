/*
 * Application.cpp
 *
 *  Created on: Apr 2, 2022
 *      Author: developer
 */

#include "command/GenericTimer.h"

TIM_HandleTypeDef GenericTimer::htim[4] = {};
uint8_t GenericTimer::htimEnabled[4] = {};
