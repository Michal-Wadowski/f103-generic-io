/*
 * Application.cpp
 *
 *  Created on: Apr 2, 2022
 *      Author: developer
 */

#include "../Inc/command/CommandUtils.h"

uint8_t * adcDataBuffer = NULL;
uint32_t adcDataBufferSize = 0;

int32_t CommandUtils::conversionNumber = -1;
int32_t CommandUtils::conversionNumberSent = -1;
