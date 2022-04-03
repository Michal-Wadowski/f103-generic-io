/*
 * Application.h
 *
 *  Created on: Apr 2, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_APPLICATION_H_
#define CORE_SRC_APPLICATION_H_

#include "UsbBuffer.h"
#include "usbd_cdc_if.h"
#include <string.h>
#include "command/GenericCommand.h"
#include "command/PingCommand.h"

class Application
{
public:
	Application();

	void usbDataReceived(uint8_t * buf, uint32_t len);
	void loopIteration();
protected:
	UsbBuffer usbBuffer;

	GenericCommand * commands[16];
};

#endif /* CORE_SRC_APPLICATION_H_ */
