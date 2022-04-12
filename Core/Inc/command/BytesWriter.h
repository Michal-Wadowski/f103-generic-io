/*
 * BytesBuilder.h
 *
 *  Created on: Apr 9, 2022
 *      Author: developer
 */

#ifndef CORE_INC_COMMAND_BYTESWRITER_H_
#define CORE_INC_COMMAND_BYTESWRITER_H_

#include "stm32f1xx_hal.h"

class BytesWriter {
public:
	BytesWriter(uint8_t * buffer) : buffer(buffer) {
		setSize(0);
	}

	uint16_t getTotalSize() {
		return getContentSize() + 2;
	}

	uint16_t getBufferIndex() {
		return getContentSize() + 2;
	}

	uint16_t getContentSize() {
		return *((uint16_t*)(&buffer[0]));
	}

	void setSize(uint32_t value) {
		*((uint16_t*)(&buffer[0])) = value;
	}

	void pushUInt8(uint8_t value) {
		*((uint8_t*)(&buffer[getBufferIndex()])) = value;
		setSize( getContentSize() + 1);
	}

	void pushUInt16(uint16_t value) {
		*((uint16_t*)(&buffer[getBufferIndex()])) = value;
		setSize( getContentSize() + 2);
	}

	void pushUInt32(uint32_t value) {
		*((uint32_t*)(&buffer[getBufferIndex()])) = value;
		setSize( getContentSize() + 4);
	}


private:
	uint8_t * buffer;
};

#endif /* CORE_INC_COMMAND_BYTESWRITER_H_ */
