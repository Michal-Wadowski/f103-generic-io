#include "UsbBuffer.h"


void UsbBuffer::append(uint8_t* buf, uint32_t len) {
	std::vector<uint8_t> * piece = new std::vector<uint8_t>(buf, &buf[len]);
	samples.push_back(piece);
}

std::vector<uint8_t>* UsbBuffer::ingest() {
	if (samples.size() > 0) {
		std::vector<uint8_t> * piece = *samples.begin();
		samples.pop_front();
		return piece;
	}
	return NULL;
}

int UsbBuffer::size() {
	return samples.size();
}
