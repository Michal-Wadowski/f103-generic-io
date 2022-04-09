/*
 * PingCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_PINGCOMMAND_H_
#define CORE_SRC_COMMAND_PINGCOMMAND_H_

#include "GenericCommand.h"
#include "usbd_cdc_if.h"

class PingCommand: public GenericCommand
{
public:
	virtual ~PingCommand() {};
	virtual void receivedCommand(BytesReader * bytesReader) {
		sendPong();
	};

private:
	void sendPong()
	{
		uint8_t txBuf[4];
		((uint16_t*) (txBuf))[0] = 2; // size
		((uint16_t*) (txBuf))[1] = PONG_COMMAND; // pong
		sendResponse(txBuf, 4);
	}
};

#endif /* CORE_SRC_COMMAND_PINGCOMMAND_H_ */
