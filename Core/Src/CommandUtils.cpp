/*
 * Application.cpp
 *
 *  Created on: Apr 2, 2022
 *      Author: developer
 */

#include "../Inc/command/CommandUtils.h"

uint8_t * adcDataBuffer = NULL;
uint8_t * adcResponseBuffer = NULL;
uint32_t adcDataBufferSize = 0;

bool CommandUtils::copyDataOnConversionComplete = false;
volatile bool CommandUtils::isDataSending = false;
