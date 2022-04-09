/*
 * BytesBuilder.h
 *
 *  Created on: Apr 9, 2022
 *      Author: developer
 */

#ifndef CORE_INC_COMMAND_BYTESREADER_H_
#define CORE_INC_COMMAND_BYTESREADER_H_

#include "stm32f1xx_hal.h"

class BytesReader {
public:
	BytesReader(uint8_t * data, uint32_t length) : index(0), data(data), length(length), overrun(false) {}

	uint32_t size() {
		return length;
	}

	uint32_t dataLeft() {
		return length - index;
	}

	uint8_t popUInt8() {
		if (dataLeft() >= 1) {
			uint8_t val = *getCurrPointer();
			index++;
			return val;
		} else {
			overrun = true;
			return 0;
		}
	}

	uint16_t popUInt16() {
		if (dataLeft() >= 2) {
			uint16_t val = *((uint16_t*)getCurrPointer());
			index += 2;
			return val;
		} else {
			overrun = true;
			return 0;
		}
	}

	uint32_t popUInt32() {
		if (dataLeft() >= 4) {
			uint32_t val = *((uint32_t*)getCurrPointer());
			index += 4;
			return val;
		} else {
			overrun = true;
			return 0;
		}
	}

	uint8_t * getCurrPointer() {
		return data + index;
	}

	bool isOverrun() {
		return overrun;
	}

private:
	uint32_t index;
	uint8_t * data;
	uint32_t length;
	bool overrun;
};

#endif /* CORE_INC_COMMAND_BYTESREADER_H_ */
