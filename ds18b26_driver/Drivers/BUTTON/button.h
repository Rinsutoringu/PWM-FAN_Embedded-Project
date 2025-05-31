//
// Created by RinChord on 25-5-31.
//
#include "stm32f1xx_hal.h"
#pragma once

enum struct button_mode
{
	INTERRUPT_MODE = 0, // 中断模式
	POLLING_MODE = 1, // 轮询模式
};

class button {

	private:
		// 按钮状态
		bool state;
		// 目标按钮所连接到的GPIO端口（假设为某个具体的端口）
		GPIO_TypeDef* gpioPort;
		// 目标按钮所连接到的GPIO引脚（假设为某个具体的引脚）
		uint16_t gpioPin;
		// 按钮模式
		button_mode mode;
		
};


