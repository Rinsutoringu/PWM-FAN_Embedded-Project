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
void DS18B20::output_high()
{
	setGPIOOutput();
	HAL_GPIO_WritePin(gpioPort, gpioPin, GPIO_PIN_SET);
}

// 引脚低电平
void DS18B20::output_low()
{
	setGPIOOutput();
	HAL_GPIO_WritePin(gpioPort, gpioPin, GPIO_PIN_RESET);
}

void DS18B20::write_bit(bool bit)
{
	if (bit) // 写1
	{
		delay_us(1);
		output_low();
		delay_us(5);
		setGPIOInput();
		delay_us(75);
	}
	else // 写0
	{
		delay_us(1);
		output_low();
		delay_us(75);
		setGPIOInput();
		delay_us(5);
	}
}

// 延迟函数
void DS18B20::delay_us(uint16_t us)
{
	uint16_t start = __HAL_TIM_GET_COUNTER(&htim1);
	while (__HAL_TIM_GET_COUNTER(&htim1) - start < us);
}

bool DS18B20::get_status()
{
	setGPIOInput();
	GPIO_PinState state = HAL_GPIO_ReadPin(gpioPort, gpioPin);
	return (state == GPIO_PIN_SET);
}



// ds18b20设备初始化
bool DS18B20::init()
{
	output_low();
	delay_us(600); // 等待500us
	output_high(); // 释放总线
	setGPIOInput();

	if (get_status() == false) return true; // 总线被拉低，设备初始化成功
	return false; // 初始化失败
}

void DS18B20::write_bit(uint8_t byte)
{
	for (int i,)
}
