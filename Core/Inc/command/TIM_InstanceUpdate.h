/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_TIM_INSTANCEUPDATE_H_
#define CORE_SRC_COMMAND_TIM_INSTANCEUPDATE_H_

#include "GenericTimer.h"

typedef enum {
	SET_COMPARE,
	SET_AUTORELOAD,
	SET_COUNTER
} InstanceUpdateCommand;

class TIM_InstanceUpdate: public GenericTimer
{
public:
	static void receivedCommand(BytesReader * bytesReader) {

		uint8_t timer = bytesReader->popUInt8();

		if (timer >= 0 && timer <= 3 && htimEnabled[timer]) {

			InstanceUpdateCommand command = (InstanceUpdateCommand)bytesReader->popUInt8();

			uint8_t channel;
			uint32_t value;

			switch (command) {
			case SET_COMPARE:
				channel = bytesReader->popUInt8();
				value = bytesReader->popUInt32();
				if (!bytesReader->isOverrun()) {
					__HAL_TIM_SET_COMPARE(&htim[timer], channel, value);
					sendOk(TIM_INSTANCE_UPDATE_RESPONSE);
				}
				break;
			case SET_AUTORELOAD:
				value = bytesReader->popUInt32();
				if (!bytesReader->isOverrun()) {
					__HAL_TIM_SET_AUTORELOAD(&htim[timer], value);
					sendOk(TIM_INSTANCE_UPDATE_RESPONSE);
				}
				break;
			case SET_COUNTER:
				value = bytesReader->popUInt32();
				if (!bytesReader->isOverrun()) {
					__HAL_TIM_SET_COUNTER(&htim[timer], value);
					sendOk(TIM_INSTANCE_UPDATE_RESPONSE);
				}
				break;
			default:
				return;
			}
		}
	}
};

#endif /* CORE_SRC_COMMAND_TIM_INSTANCEUPDATE_H_ */
