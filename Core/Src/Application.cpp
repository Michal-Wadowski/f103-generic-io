/*
 * Application.cpp
 *
 *  Created on: Apr 2, 2022
 *      Author: developer
 */

#include "Application.h"

Application application = Application();

Application::Application() : commands() {
	commands[PING_COMMAND] = new PingCommand();
	commands[WRITE_PIN] = new WritePin();
	commands[READ_PIN] = new ReadPin();
	commands[GPIO_INIT] = new GPIOInit();
}

void Application::usbDataReceived(uint8_t * buf, uint32_t len) {
	usbBuffer.append(buf, len);
}

void Application::loopIteration() {
	do {
		std::vector<uint8_t> * dataItem = usbBuffer.ingest();
		if (dataItem == NULL) {
			break;
		}

		uint16_t size = *(uint16_t *)&(*dataItem)[0];
		if (size >= 2) {
			uint16_t command = *(uint16_t *)&(*dataItem)[2];
			uint8_t * data = (uint8_t *)&(*dataItem)[4];

			if (commands[command] != NULL) {
				commands[command]->receivedCommand(data, size);
			}
		}

		delete dataItem;

	} while(true);
}

extern "C" void usbDataReceived(uint8_t * buf, uint32_t len) {
	application.usbDataReceived(buf, len);
}

extern "C" void loopIteration() {
	application.loopIteration();
}

