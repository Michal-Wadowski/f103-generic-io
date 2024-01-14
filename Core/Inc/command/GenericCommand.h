/*
 * GenericCommand.h
 *
 *  Created on: Apr 3, 2022
 *      Author: developer
 */

#ifndef CORE_SRC_COMMAND_GENERICCOMMAND_H_
#define CORE_SRC_COMMAND_GENERICCOMMAND_H_

#include "stm32f1xx_hal.h"
#include "usbd_cdc_if.h"

#include "BytesReader.h"
#include "BytesWriter.h"

typedef enum
{
	PING_COMMAND,

	WRITE_PIN,

	READ_PIN,

	GPIO_INIT,

	TIM_START,

	TIM_STOP,

	TIM_INIT,

	TIM_DEINIT,

	TIM_CONFIG_CHANNEL,

	TIM_INSTANCE_UPDATE,

	TIM_INSTANCE_READ,

	DMA_INIT,

	ADC_INIT,

	ADC_CONFIG_CHANNEL,

	ADC_START,

	NVIC_SET_PRIORITY,

	NVIC_ENABLE_IRQ,

	COMMAND_UTILS,

	BUFFER
} CommandIds;

typedef enum
{
	PONG_COMMAND,

	WRITE_PIN_RESPONSE,

	READ_PIN_RESPONSE,

	GPIO_INIT_RESPONSE,

	TIM_START_RESPONSE,

	TIM_STOP_RESPONSE,

	TIM_INIT_RESPONSE,

	TIM_DEINIT_RESPONSE,

	TIM_CONFIG_CHANNEL_RESPONSE,

	TIM_INSTANCE_UPDATE_RESPONSE,

	TIM_INSTANCE_READ_RESPONSE,

	DMA_INIT_RESPONSE,

	ADC_INIT_RESPONSE,

	ADC_CONFIG_CHANNEL_RESPONSE,

	ADC_START_RESPONSE,

	NVIC_SET_PRIORITY_RESPONSE,

	NVIC_ENABLE_IRQ_RESPONSE,

	COMMAND_UTILS_RESPONSE,

	BUFFER_RESPONSE
} CommandResponseIds;

typedef void (*receivedCommand)(BytesReader *bytesReader);

extern USBD_HandleTypeDef hUsbDeviceFS;

class GenericCommand
{
protected:
	static void sendResponse(uint8_t *data, uint16_t size)
	{
		while (CDC_Transmit_FS((uint8_t *)(data), size) != USBD_OK)
			;

		// Helps if data buffer is located at stack and not heap
		waitForTransmisionFinish();
	}

	static void sendOk(uint16_t responseCode)
	{
		uint8_t txBuf[16];

		BytesWriter bw = BytesWriter(txBuf);
		bw.pushUInt16(responseCode);

		sendResponse(txBuf, bw.getTotalSize());
	}

private:
	static void waitForTransmisionFinish()
	{
		USBD_CDC_HandleTypeDef *hcdc =
			(USBD_CDC_HandleTypeDef *)(hUsbDeviceFS.pClassData);
		while (hcdc->TxState != 0)
			;
	}
};

#endif /* CORE_SRC_COMMAND_GENERICCOMMAND_H_ */
