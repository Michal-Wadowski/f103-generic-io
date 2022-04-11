/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_TIM_INSTANCEREAD_H_
#define CORE_SRC_COMMAND_TIM_INSTANCEREAD_H_

#include "GenericCommand.h"
#include "usbd_cdc_if.h"
#include "TIM_Common.h"

extern TIM_HandleTypeDef * htim[4];

typedef enum {
	GET_COMPARE,
	GET_AUTORELOAD,
	GET_COUNTER
} InstanceReadCommand;

class TIM_InstanceRead: public GenericCommand
{
public:
	virtual ~TIM_InstanceRead() {};
	virtual void receivedCommand(BytesReader * bytesReader) {

		uint8_t timer = bytesReader->popUInt8();

		if (timer >= 0 && timer <= 4 && htim[timer] != NULL) {

			InstanceReadCommand command = (InstanceReadCommand)bytesReader->popUInt8();

			uint8_t channel;
			uint32_t value;

			switch (command) {
			case GET_COMPARE:
				channel = bytesReader->popUInt8();
				if (!bytesReader->isOverrun()) {
					value = __HAL_TIM_GET_COMPARE(htim[timer], channel);
					sendOk(value);
				}
				break;
			case GET_AUTORELOAD:
				if (!bytesReader->isOverrun()) {
					value = __HAL_TIM_GET_AUTORELOAD(htim[timer]);
					sendOk(value);
				}
				break;
			case GET_COUNTER:
				if (!bytesReader->isOverrun()) {
					value = __HAL_TIM_GET_COUNTER(htim[timer]);
					sendOk(value);
				}
				break;
			default:
				return;
			}
		}
	}

	void sendOk(uint32_t value)
	{
		uint8_t txBuf[8];
		*((uint16_t*)&txBuf[0]) = 6;
		*((uint16_t*)&txBuf[2]) = TIM_INSTANCE_READ_RESPONSE;
		*((uint32_t*)&txBuf[4]) = value;
		sendResponse(txBuf, sizeof(txBuf));
	}
};

#endif /* CORE_SRC_COMMAND_TIM_INSTANCEREAD_H_ */
