//
// Created by RinChord on 25-5-30.
//

#include "ds18b20.h"

DS18B20::DS18B20(GPIO_TypeDef* gpioPort, uint16_t gpioPin)
	: gpioPort(gpioPort), gpioPin(gpioPin), isEnable(false), temperature(-1) {
}

void DS18B20::setGPIOInput()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = gpioPin;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(gpioPort, &GPIO_InitStructure);
}

void DS18B20::setGPIOOutput()
{
	GPIO_InitTypeDef GPIO_InitStructure;
}


void DS18B20::init()
{

}
