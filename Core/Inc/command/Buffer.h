#ifndef CORE_SRC_COMMAND_BUFFER_H_
#define CORE_SRC_COMMAND_BUFFER_H_

#include "GenericCommand.h"
#include <strings.h>

typedef enum
{
	ALLOC_BUFFER,
	FREE_BUFFER,
	READ_BUFFER,
	WRITE_BUFFER
} Buffer_Command;

class Buffer : public GenericCommand
{
public:
	static void receivedCommand(BytesReader *bytesReader)
	{
		Buffer_Command command = (Buffer_Command)bytesReader->popUInt8();

		switch (command)
		{

		case ALLOC_BUFFER:
		{
			uint16_t size = bytesReader->popUInt16();

			void *ptr = malloc(size);
			sendAllocBufferResponse(command, ptr);
			break;
		}

		case FREE_BUFFER:
		{
			void *ptr = (void *)bytesReader->popUInt32();
			free(ptr);
			sendResponse(command);
			break;
		}

		case READ_BUFFER:
		{
			uint8_t *ptr = (uint8_t *)bytesReader->popUInt32();
			uint16_t size = bytesReader->popUInt16();
			sendBufferContentResponse(command, ptr, size);
			break;
		}

		case WRITE_BUFFER:
			uint8_t *ptr = (uint8_t *)bytesReader->popUInt32();
			uint16_t size = bytesReader->popUInt16();
			for (uint16_t i = 0; i < size; i++) {
				ptr[i] = bytesReader->popUInt8();
			}
			sendResponse(command);
			break;
		}
	}

	static void sendAllocBufferResponse(Buffer_Command command, void *ptr)
	{
		uint8_t txBuf[16];

		BytesWriter bw = BytesWriter(txBuf);
		bw.pushUInt16(BUFFER_RESPONSE);
		bw.pushUInt8(command);
		bw.pushUInt32((uint32_t)ptr);

		GenericCommand::sendResponse(txBuf, bw.getTotalSize());
	}

	static void sendBufferContentResponse(Buffer_Command command, uint8_t *ptr, uint16_t size)
	{
		uint8_t txBuf[16];

		BytesWriter bw = BytesWriter(txBuf);
		bw.pushUInt16(BUFFER_RESPONSE);
		bw.pushUInt8(command);

		GenericCommand::sendResponse(txBuf, bw.getTotalSize());
		GenericCommand::sendResponse(ptr, size);
	}

	static void sendResponse(Buffer_Command command)
	{
		uint8_t txBuf[16];

		BytesWriter bw = BytesWriter(txBuf);
		bw.pushUInt16(BUFFER_RESPONSE);
		bw.pushUInt8(command);

		GenericCommand::sendResponse(txBuf, bw.getTotalSize());
	}
};

#endif /* CORE_SRC_COMMAND_BUFFER_H_ */
