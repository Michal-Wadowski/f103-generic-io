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
	static void receivedCommand(BytesReader * bytesReader) {
		sendPong();
	};

private:
	static void sendPong()
	{
		sendOk(PONG_COMMAND);
	}
};

#endif /* CORE_SRC_COMMAND_PINGCOMMAND_H_ */
