//
// Created by Chord on 25-6-7.
//

#pragma once

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_.h"

#include "uart.h"

extern UART uart1;


class light_sensor {
private:
	GPIO_TypeDef* gpioPort;
	uint8_t gpioPin;

	ADC_HandleTypeDef* adcHandle;


public:
	light_sensor(GPIO_InitTypeDef* gpioPort, uint8_t gpioPin,);
	void init();
	void read();

};



