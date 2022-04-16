/*
 * Application.cpp
 *
 *  Created on: Apr 2, 2022
 *      Author: developer
 */

#include "../Inc/command/CommandUtils.h"

uint8_t adcDataBuffer[64];
uint8_t adcResponseBuffer[64];

bool CommandUtils::copyDataOnConversionComplete = false;
