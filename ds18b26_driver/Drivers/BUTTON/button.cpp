//
// Created by RinChord on 25-5-31.
//

#include "button.h"

extern UART uart1;

Button::Button(GPIO_TypeDef* gpioPort, uint16_t gpioPin):
	state(false), gpioPort(gpioPort), gpioPin(gpioPin), debounceDelay(10), pendingState(false), pendingTime(0), buttonFlag(false) {}

/**
 * 消抖函数，轮询时用
 * 先抓取按钮当前状态，延迟一下，再读一个，如果俩结果一样，那就确定按钮被按了
 * 如果结果不一样，说明是按钮抖动了，不管它
 */
void Button::read()
{
	bool reading = (HAL_GPIO_ReadPin(gpioPort, gpioPin) == GPIO_PIN_SET);
	uint32_t now = HAL_GetTick();

	// 打印当前采样值和时间
	uart1.printf("read=%d, pendingState=%d, state=%d, now=%lu, pendingTime=%lu\r\n",
				 reading, pendingState, state, now, pendingTime);

	if (reading != pendingState) {
		pendingState = reading;
		pendingTime = now;
		uart1.printf("State changed! pendingState=%d, pendingTime=%lu\r\n", pendingState, pendingTime);
	}

	if ((now - pendingTime) >= debounceDelay) {
		if (state != pendingState) {
			state = pendingState;
			uart1.printf("Debounced! state=%d, time=%lu\r\n", state, now);
			if (callback) callback(state);
		}
	}
}

void Button::setCallback(Callback cb)
{
	callback = cb;
}


void Button::onInterrupt()
{
	setButtonFlag(true); // 设置按钮中断标志
}

bool Button::getIsEnable()
{
	return isEnable; // 获取按钮可用性
}

void Button::enable()
{
	isEnable = true; // 启用按钮
}

void Button::disable()
{
	isEnable = false; // 禁用按钮
}

void Button::setDebounceDelay(uint32_t delay)
{
	debounceDelay = delay; // 设置消抖延迟
}

bool Button::getButtonFlag()
{
	return this->buttonFlag; // 获取按钮中断标志
}

void Button::setButtonFlag(bool flag)
{
	this->buttonFlag = flag;
}
