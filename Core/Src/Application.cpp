/*
 * Application.cpp
 *
 *  Created on: Apr 2, 2022
 *      Author: developer
 */

#include "Application.h"

Application application = Application();

extern "C" void usbDataReceived(uint8_t * buf, uint32_t len)
{
	application.usbDataReceived(buf, len);
}

extern "C" void loopIteration()
{
	application.loopIteration();
}
