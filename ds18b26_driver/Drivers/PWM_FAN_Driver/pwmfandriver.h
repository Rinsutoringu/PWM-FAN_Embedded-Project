//
// Created by RinChord on 25-6-3.
//

#pragma once

#include "stm32f1xx_hal.h"
#include "uart.h"

extern UART uart1;

class PWM_FAN_DRIVER {
private:
	GPIO_TypeDef* gpioPort;
	uint16_t gpioPin;
	int16_t temp;
	TIM_HandleTypeDef htim3; // 定时器句柄

public:
	PWM_FAN_DRIVER(GPIO_TypeDef* gpioPort, uint16_t gpioPin);

	void init();

	void start();


};



