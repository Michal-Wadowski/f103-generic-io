/*
 * Application.cpp
 *
 *  Created on: Apr 2, 2022
 *      Author: developer
 */

#include "Application.h"

Application application = Application();

void Application::usbDataReceived(uint8_t* buf, uint32_t len) {
	usbBuffer.append(buf, len);
}

void Application::loopIteration() {
	do {
		std::vector<uint8_t>* dataItem = usbBuffer.ingest();
		if (dataItem == NULL) {
			break;
		}

		uint16_t size = *(uint16_t *)&(*dataItem)[0];
		if (size >= 2) {
			uint16_t command = *(uint16_t *)&(*dataItem)[2];

			if (command == 1) { // ping
				uint8_t txBuf[4];
				((uint16_t*)txBuf)[0] = 2; // size
				((uint16_t*)txBuf)[1] = 2; // pong
				while(CDC_Transmit_FS((uint8_t*)txBuf, 4)!=USBD_OK);
			}
		}

		delete dataItem;

	} while(true);
}

extern "C" void usbDataReceived(uint8_t* buf, uint32_t len) {
	application.usbDataReceived(buf, len);
}

extern "C" void loopIteration() {
	application.loopIteration();
}

