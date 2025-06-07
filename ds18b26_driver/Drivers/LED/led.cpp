//
// Created by RinChord on 25-5-30.
//
#include "led.h"


LED::LED(GPIO_TypeDef* GPIOPort, uint16_t GPIO_Pin) : state(false), gpioPort(GPIOPort), gpioPin(GPIO_Pin) {
    // 初始化LED状态为关闭
}

void LED::init()
{
	GPIO_InitTypeDef ledgpioInit;
	ledgpioInit.Pin = gpioPin;
	ledgpioInit.Mode = GPIO_MODE_OUTPUT_PP;
	ledgpioInit.Speed = GPIO_SPEED_FREQ_LOW;
	ledgpioInit.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(gpioPort, &ledgpioInit);
}

// 点亮LED灯泡
bool LED::turnON() {
    this->state = true;
	HAL_GPIO_WritePin(gpioPort, gpioPin, GPIO_PIN_SET);
    return true;
}

// 关闭LED灯泡
bool LED::turnOFF() {
	this->state = false;
	HAL_GPIO_WritePin(gpioPort, gpioPin, GPIO_PIN_RESET);
    return true;
}

// 获取LED开关状态
bool LED::getState() const {
    return this->state;  // 返回当前LED状态
}

void LED::switchStatus()
{
	if (this->getState())
	{
		turnOFF();
		return;
	}
	turnON();
	return;

}

