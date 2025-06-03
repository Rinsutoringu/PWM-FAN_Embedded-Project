//
// Created by RinChord on 25-5-30.
//

#pragma once

#include "stm32f1xx_hal.h"
#include "tim.h"
#include "time.h"

#define GPIO_OUTPUT 0x01
#define GPIO_INPUT 0x02

/**
 * 在使用本驱动前需要做的事情：
 * 0. 确定CPP支持已启用
 * 1. 寻找一个空闲的GPIO引脚
 * 2. 初始化这个引脚的对应时钟，时钟周期应为1MHZ
 * 3. 在main函数前实例化ds18b20对象，使用全局变量而不是new
 * 4. 使用init初始化ds18b20设备
 */
class DS18B20 {

private:
	GPIO_TypeDef* gpioPort;
	uint16_t gpioPin;
	bool isEnable;
	int32_t temperature;
	uint16_t gpioMode;


public:
	DS18B20(GPIO_TypeDef* gpioPort, uint16_t gpioPin);
	// 初始化设备
	bool init();
	// 发送指令
	void sendCommand(uint8_t command);
	// 读取温度
	int32_t readTemperature();

	void enable();
	void disable();

	void setGPIOOutput();
	void output_low();
	void output_high();
	void write_bit(bool bit);
	void write_bit(uint8_t byte);

	void setGPIOInput();
	bool get_status();

	static void delay_us(uint16_t us);


};



