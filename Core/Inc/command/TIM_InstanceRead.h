/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_TIM_INSTANCEREAD_H_
#define CORE_SRC_COMMAND_TIM_INSTANCEREAD_H_

#include "GenericTimer.h"

typedef enum {
	GET_COMPARE,
	GET_AUTORELOAD,
	GET_COUNTER
} InstanceReadCommand;

class TIM_InstanceRead: public GenericTimer
{
public:
	static void receivedCommand(BytesReader * bytesReader) {

		uint8_t timer = bytesReader->popUInt8();

		if (timer >= 0 && timer <= 4 && htimEnabled[timer]) {

			InstanceReadCommand command = (InstanceReadCommand)bytesReader->popUInt8();

			uint8_t channel;
			uint32_t value;

			switch (command) {
			case GET_COMPARE:
				channel = bytesReader->popUInt8();
				if (!bytesReader->isOverrun()) {
					value = __HAL_TIM_GET_COMPARE(&htim[timer], channel);
					sendResult(value);
				}
				break;
			case GET_AUTORELOAD:
				if (!bytesReader->isOverrun()) {
					value = __HAL_TIM_GET_AUTORELOAD(&htim[timer]);
					sendResult(value);
				}
				break;
			case GET_COUNTER:
				if (!bytesReader->isOverrun()) {
					value = __HAL_TIM_GET_COUNTER(&htim[timer]);
					sendResult(value);
				}
				break;
			default:
				return;
			}
		}
	}

	static void sendResult(uint32_t value)
	{
		uint8_t txBuf[16];

		BytesWriter bw = BytesWriter(txBuf);
		bw.pushUInt16(TIM_INSTANCE_READ_RESPONSE);
		bw.pushUInt32(value);

		sendResponse(txBuf, bw.getTotalSize());
	}
};

#endif /* CORE_SRC_COMMAND_TIM_INSTANCEREAD_H_ */
