//
// Created by RinChord on 25-5-31.
//

#include "uart.h"

UART::UART(UART_HandleTypeDef *huart, uint32_t Timeout)
{
	this->huart = huart;
	this->Timeout = Timeout;
}

UART::UART(UART_HandleTypeDef *huart)
{
	this->huart = huart;
	this->Timeout = HAL_MAX_DELAY; // 默认超时时间为HAL_MAX_DELAY
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
