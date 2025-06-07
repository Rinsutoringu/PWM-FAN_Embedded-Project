//
// Created by RinChord on 25-5-30.
//
#include "stm32f1xx_hal.h"
#include <cstdint>

#pragma once

class LED {
private:

    // LED状态
    bool state;
	// 目标灯泡所连接到的GPIO端口（假设为某个具体的端口）
	GPIO_TypeDef* gpioPort;
	// 目标LED灯泡所连接到的GPIO引脚（假设为某个具体的引脚）
	uint16_t gpioPin;

public:
	/**
	 * 实例化LED类
	 */
	LED(GPIO_TypeDef *GPIOPort, uint16_t GPIO_Pin);

	void init();
	/**
     * 点亮LED灯泡
     * @return 成功点亮返回true
     */
    bool turnON();

    /**
     * 关闭LED灯泡
     * @return
     */
    bool turnOFF();

    /**
     * 获取LED开关状态
     * @return 当前LED状态
     */
    bool getState() const;

	void switchStatus();

};
