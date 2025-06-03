//
// Created by RinChord on 25-5-30.
//

#include "ds18b20.h"

DS18B20::DS18B20(GPIO_TypeDef* gpioPort, uint16_t gpioPin)
	: gpioPort(gpioPort), gpioPin(gpioPin), isEnable(false), temperature(-1), gpioMode(0x00) {
}

/**
 * 配置GPIO为输入模式
 * 不驱动时处于悬空状态
 */
void DS18B20::setGPIOInput()
{
	if (gpioMode == GPIO_INPUT) return;

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = gpioPin;
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT; // 初始化为输入模式
	GPIO_InitStructure.Pull = GPIO_NOPULL; // 不使用上拉或下拉电阻
	HAL_GPIO_Init(gpioPort, &GPIO_InitStructure);
	gpioMode = GPIO_INPUT;
}

/**
 * 配置GPIO为推挽输出模式
 * 不驱动时处于悬空状态
 */
void DS18B20::setGPIOOutput()
{
	if (gpioMode == GPIO_OUTPUT) return;

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = gpioPin; // 设置GPIO引脚
	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; // 初始化为推挽输出模式
	GPIO_InitStructure.Pull = GPIO_PULLDOWN; // 默认下拉
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH; // 高速模式
	HAL_GPIO_Init(gpioPort, &GPIO_InitStructure);
	gpioMode = GPIO_OUTPUT;

}

// 引脚高电平
void DS18B20::gpio_output_high()
{
	setGPIOOutput();
	HAL_GPIO_WritePin(gpioPort, gpioPin, GPIO_PIN_SET);
}

// 引脚低电平
void DS18B20::gpio_output_low()
{
	setGPIOOutput();
	HAL_GPIO_WritePin(gpioPort, gpioPin, GPIO_PIN_RESET);

}

// ds18b20设备初始化
void DS18B20::init()
{
	gpio_output_high();
	HAL_Delay()

}
