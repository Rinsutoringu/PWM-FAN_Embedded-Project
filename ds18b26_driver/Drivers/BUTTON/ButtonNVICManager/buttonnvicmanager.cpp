//
// Created by Chord on 25-6-7.
//

#include "buttonnvicmanager.h"

buttonnvicmanager::buttonnvicmanager(Button& button, IRQn_Type irqn) :
	button(button), irqn(irqn) {}

void buttonnvicmanager::init()
{
	GPIO_InitTypeDef nvicButton;
	nvicButton.Pin = button.getGpioPin();
	nvicButton.Pull = GPIO_PULLUP;
	nvicButton.Mode = GPIO_MODE_IT_RISING_FALLING;
	nvicButton.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(button.getGpioPort(), &nvicButton);
	// 设置中断优先级
	HAL_NVIC_SetPriority(irqn, 0, 0);
	// 使能中断
	HAL_NVIC_EnableIRQ(irqn);
}

void buttonnvicmanager::handleInterrupt(uint8_t GPIO_Pin)
{
	if (GPIO_Pin == button.getGpioPin()) {
		button.onInterrupt();
	}
}
