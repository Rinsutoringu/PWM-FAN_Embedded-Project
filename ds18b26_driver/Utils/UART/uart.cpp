//
// Created by RinChord on 25-5-31.
//

#include "uart.h"

UART::UART(UART_HandleTypeDef *huart,uint32_t Baudrate, uint32_t Timeout)
{
	this->huart = huart;
	this->Timeout = Timeout;
	this->Baudrate = Baudrate;
}

void UART::init()
{
	setBaudrate(this->Baudrate);
}

void UART::setBaudrate(uint32_t baudrate)
{
	huart->Init.BaudRate = baudrate;
	HAL_UART_DeInit(huart);
	HAL_UART_Init(huart);
}

bool UART::print(const uint8_t *pdata) const
{
	if (HAL_UART_Transmit(huart, pdata, strlen((const char *)pdata), Timeout) == HAL_OK)
		return true;
	return false;
}

bool UART::print(const char *pdata) const
{
	if (HAL_UART_Transmit(huart, (const uint8_t *)pdata, strlen(pdata), Timeout) == HAL_OK)
		return true;
	return false;
}
