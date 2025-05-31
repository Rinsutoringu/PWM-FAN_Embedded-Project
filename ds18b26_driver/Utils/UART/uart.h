//
// Created by RinChord on 25-5-31.
//

#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <string.h>

#pragma once

class UART {

private:
	// UART所用端口
	UART_HandleTypeDef *huart;
	uint32_t Timeout;

public:
	/**
	 * 实例化UART类
	 * @param huart 输出端口
	 * @param printdata 输出数据
	 */
	UART(UART_HandleTypeDef *huart, uint32_t Timeout);

	/**
	 * 实例化UART类 Timeout默认值为HAL_MAX_DELAY
	 * @param huart 输出端口
	 */
	UART(UART_HandleTypeDef *huart);

	/**
	 * 发送数据
	 * @param data 要发送的数据
	 * @return 成功发送返回true
	 */
	bool print(const uint8_t *pdata) const;

	/**
	 * 发送字符串
	 * @param str 要发送的字符串
	 * @return 成功发送返回true
	 */
	bool print(const char *pdata) const;

};
