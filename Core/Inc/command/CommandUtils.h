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

extern uint8_t adcDataBuffer[64];
extern uint8_t adcResponseBuffer[64];

typedef enum {
	COPY_DATA_ON_CONVERSION_COMPLETE,
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

			sendReadBufferData(adcResponseBuffer, sizeof(adcResponseBuffer));
		} else if (command == COPY_DATA_ON_CONVERSION_COMPLETE) {
			bool enable = (bool)bytesReader->popUInt8();

			if (bytesReader->isOverrun()) {
				return;
			}

			copyDataOnConversionComplete = enable;

			sendResponse(COPY_DATA_ON_CONVERSION_COMPLETE);
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
		if (copyDataOnConversionComplete) {
			if (part == 0) {
				memcpy(&adcResponseBuffer[0], &adcDataBuffer[0], sizeof(adcDataBuffer) / 2);
			} else {
				memcpy(&adcResponseBuffer[32], &adcDataBuffer[32], sizeof(adcDataBuffer) / 2);
			}
		}
	}

private:
	static bool copyDataOnConversionComplete;
};

#endif /* CORE_SRC_COMMAND_COMMANDUTILS_H_ */
