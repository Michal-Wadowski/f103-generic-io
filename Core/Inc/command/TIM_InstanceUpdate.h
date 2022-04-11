/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_TIM_INSTANCEUPDATE_H_
#define CORE_SRC_COMMAND_TIM_INSTANCEUPDATE_H_

#include "GenericCommand.h"
#include "usbd_cdc_if.h"
#include "TIM_Common.h"

extern TIM_HandleTypeDef * htim[4];

typedef enum {
	SET_COMPARE,
	SET_AUTORELOAD,
	SET_COUNTER
} InstanceUpdateCommand;

class TIM_InstanceUpdate: public GenericCommand
{
public:
	virtual ~TIM_InstanceUpdate() {};
	virtual void receivedCommand(BytesReader * bytesReader) {

		uint8_t timer = bytesReader->popUInt8();

		if (timer >= 0 && timer <= 4 && htim[timer] != NULL) {

			InstanceUpdateCommand command = (InstanceUpdateCommand)bytesReader->popUInt8();

			uint8_t channel;
			uint32_t value;

			switch (command) {
			case SET_COMPARE:
				channel = bytesReader->popUInt8();
				value = bytesReader->popUInt32();
				if (!bytesReader->isOverrun()) {
					__HAL_TIM_SET_COMPARE(htim[timer], channel, value);
					sendOk();
				}
				break;
			case SET_AUTORELOAD:
				value = bytesReader->popUInt32();
				if (!bytesReader->isOverrun()) {
					__HAL_TIM_SET_AUTORELOAD(htim[timer], value);
					sendOk();
				}
				break;
			case SET_COUNTER:
				value = bytesReader->popUInt32();
				if (!bytesReader->isOverrun()) {
					__HAL_TIM_SET_COUNTER(htim[timer], value);
					sendOk();
				}
				break;
			default:
				return;
			}
		}
	}

	void sendOk()
	{
		uint8_t txBuf[4];
		((uint16_t*) (txBuf))[0] = 2; // size
		((uint16_t*) (txBuf))[1] = TIM_INSTANCE_UPDATE_RESPONSE;
		sendResponse(txBuf, 4);
	}
};

#endif /* CORE_SRC_COMMAND_TIM_INSTANCEUPDATE_H_ */
