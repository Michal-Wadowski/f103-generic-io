#ifndef __USB_BUFFER_H__
#define __USB_BUFFER_H__


#include "main.h"
#include <stdlib.h>
#include <string.h>

#include <list>

#include "command/BytesReader.h"

class UsbBuffer {
private:
	static const int QUEUE_SIZE = 32U;
public:
	UsbBuffer(): begin(0), end(0) {}

	void append(uint8_t* buf, uint32_t len) {
		if (size() < QUEUE_SIZE) {
			samples2[end % QUEUE_SIZE] = BytesReader(buf, len);
			end++;
		}
	}

	BytesReader * ingest() {
		if (size() > 0) {
			BytesReader * piece = &samples2[begin % QUEUE_SIZE];
			begin++;
			return piece;
		}
		return NULL;
	}

	uint32_t size() {
		return end - begin;
	}


protected:
	uint8_t begin;
	uint8_t end;

	BytesReader samples2[QUEUE_SIZE];
};

#endif
