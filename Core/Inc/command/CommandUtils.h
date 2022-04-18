/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_COMMANDUTILS_H_
#define CORE_SRC_COMMAND_COMMANDUTILS_H_

#include "GenericCommand.h"
#include <strings.h>

extern uint8_t * adcDataBuffer;
//extern uint8_t * adcResponseBuffer;
extern uint32_t adcDataBufferSize;

typedef enum {
	READ_BUFFER
} CommandUtils_Command;

class CommandUtils: public GenericCommand
{
public:
	static void receivedCommand(BytesReader * bytesReader) {
		CommandUtils_Command command = (CommandUtils_Command)bytesReader->popUInt8();

		if (command == READ_BUFFER) {
			if (bytesReader->isOverrun()) {
				return;
			}

			if (conversionNumber > conversionNumberSent) {
				sendReadBufferData(getAdcDataPart(), adcDataBufferSize / 2);
				conversionNumberSent = conversionNumber;
			}
		}
	}

	static uint8_t * getAdcDataPart() {
		if (conversionNumber & 1 == 0) {
			return &adcDataBuffer[0];
		} else {
			return &adcDataBuffer[adcDataBufferSize / 2];
		}
	}

	static void sendReadBufferData(uint8_t * data, uint32_t size) {
		uint8_t txBuf[size + 16];

		BytesWriter bw = BytesWriter(txBuf);
		bw.pushUInt16(COMMAND_UTILS_RESPONSE);
		bw.pushUInt8(READ_BUFFER);
		bw.pushUInt32(size);

		memcpy(bw.getCurrPointer(), data, size);
		bw.resize(size);

		GenericCommand::sendResponse(txBuf, bw.getTotalSize());
	}

	static void sendResponse(CommandUtils_Command command) {
		uint8_t txBuf[16];

		BytesWriter bw = BytesWriter(txBuf);
		bw.pushUInt16(COMMAND_UTILS_RESPONSE);
		bw.pushUInt8(command);

		GenericCommand::sendResponse(txBuf, bw.getTotalSize());
	}

	static void adcConversionCompleteHandler(ADC_HandleTypeDef* hadc, uint8_t part) {
		if (part == 0) {
			conversionNumber = (conversionNumber + 2) & ~1;
		} else {
			conversionNumber = conversionNumber | 1;
		}
	}

private:
	static int32_t conversionNumber;
	static int32_t conversionNumberSent;
};

#endif /* CORE_SRC_COMMAND_COMMANDUTILS_H_ */
