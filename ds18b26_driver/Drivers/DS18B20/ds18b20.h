//
// Created by RinChord on 25-5-30.
//

#pragma once

#include "stm32f1xx_hal.h"
#include "tim.h"
#include "uart.h"

#define GPIO_OUTPUT 0x01
#define GPIO_INPUT 0x02
#define DEVICE_JUMP_ROM 0xCC
#define DEVICE_READ_ROM 0x33
#define DEVICE_TEMP_CONVERSION 0x44
#define DEVICE_READ_RAM 0xBE

extern UART uart1;

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
	void init();
	// 重置设备
	bool reset();
	// 读取温度
	int16_t readTemperature();

	bool is_Enable();

	void setGPIOOutput();
	void output_low();
	void output_high();
	void write_bit(bool bit);
	void write_byte(uint8_t byte);

	void setGPIOInput();
	bool read_bit();
	uint8_t read_byte();

	static void delay_us(uint16_t us);



};



