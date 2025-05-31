//
// Created by RinChord on 25-5-30.
//

#pragma once

#include "stm32f1xx_hal.h"


class DS18B20 {

private:
	GPIO_TypeDef* gpioPort;
	uint16_t gpioPin;
	bool isEnable;
	int32_t temperature;

public:
	DS18B20(GPIO_TypeDef* gpioPort, uint16_t gpioPin);
	// 初始化设备
	void init();
	// 发送指令
	void sendCommand(uint8_t command);
	// 读取温度
	int32_t readTemperature();

	void enable();
	void disable();

	void setGPIOInput();
	void setGPIOOutput();



};



