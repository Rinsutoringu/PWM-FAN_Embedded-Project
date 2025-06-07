//
// Created by Chord on 25-6-7.
//

#pragma once

#include "stm32f1xx_hal.h"
#include "uart.h"

extern UART uart1;


class light_sensor {
private:
	GPIO_TypeDef* gpioPort;
	uint8_t gpioPin;


public:
	light_sensor();

};



