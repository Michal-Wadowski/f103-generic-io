#ifndef __USB_BUFFER_H__
#define __USB_BUFFER_H__


#include "main.h"
#include <stdlib.h>
#include <string.h>

#include <list>

#include "command/BytesReader.h"

class UsbBuffer {
public:
	void append(uint8_t* buf, uint32_t len) {
		samples.push_back(new BytesReader(buf, len));
	}

	BytesReader * ingest() {
		if (samples.size() > 0) {
			BytesReader * piece = *samples.begin();
			samples.pop_front();
			return piece;
		}
		return NULL;
	}

	int size() {
		return samples.size();
	}


protected:
	std::list<BytesReader*> samples;
};

#endif
