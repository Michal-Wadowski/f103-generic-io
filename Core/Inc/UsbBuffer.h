#ifndef __USB_BUFFER_H__
#define __USB_BUFFER_H__


#include "main.h"
#include <stdlib.h>
#include <string.h>

#include <list>
#include <vector>


class UsbBuffer {
public:
	void append(uint8_t* buf, uint32_t len);
	std::vector<uint8_t>* ingest();

	int size();
protected:
	std::list<std::vector<uint8_t>*> samples;
};

#endif
