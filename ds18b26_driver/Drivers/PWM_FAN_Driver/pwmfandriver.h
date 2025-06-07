//
// Created by RinChord on 25-6-3.
//

#pragma once

#include "stm32f1xx_hal.h"
#include "uart.h"
#include "ds18b20.h"

extern UART uart1;
extern DS18B20 ds18b20;

class PWM_FAN_DRIVER {
private:
	GPIO_TypeDef						* gpioPort;
	uint16_t gpioPin;
	int16_t temp;
	TIM_HandleTypeDef htim3;
	TIM_OC_InitTypeDef sConfigOC;
	bool status;

public:
	PWM_FAN_DRIVER(GPIO_TypeDef* gpioPort, uint16_t gpioPin);

	void init();

	void setTemp(int16_t temp);

	void start();

	void stop();

	void switchStatus();

	void updateSpeed();


};



