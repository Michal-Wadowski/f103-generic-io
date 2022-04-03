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
	static const int COMMAND_ID = 1;

	virtual ~PingCommand() {};
	virtual void receivedCommand(uint8_t * data, uint16_t size) {
		sendPong();
	};

private:
	void sendPong()
	{
		uint8_t txBuf[4];
		((uint16_t*) (txBuf))[0] = 2; // size
		((uint16_t*) (txBuf))[1] = 2; // pong
		while (CDC_Transmit_FS((uint8_t*) (txBuf), 4) != USBD_OK);
	}
};

#endif /* CORE_SRC_COMMAND_PINGCOMMAND_H_ */
