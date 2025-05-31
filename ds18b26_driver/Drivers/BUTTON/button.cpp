//
// Created by RinChord on 25-5-31.
//

#include "button.h"

Button::Button(GPIO_TypeDef* gpioPort, uint16_t gpioPin):
	state(false), gpioPort(gpioPort), gpioPin(gpioPin), debounceDelay(10), pendingState(false), pendingTime(0) {}

/**
 * 消抖函数，轮询时用
 * 先抓取按钮当前状态，延迟一下，再读一个，如果俩结果一样，那就确定按钮被按了
 * 如果结果不一样，说明是按钮抖动了，不管它
 */
void Button::read()
{
	// 判断按钮现在状态
	bool reading = (HAL_GPIO_ReadPin(gpioPort, gpioPin) == GPIO_PIN_SET);
	uint32_t now = HAL_GetTick();

	// 如果按钮当前状态没变化，那就不管它
	if (reading == pendingState) return;
	// 如果发现按钮状态变了，就记录本次采样时间和状态
	pendingTime = now;
	pendingState = reading;

	// 如果当前时间和上次采样时间的差值小于消抖延迟，就不管它
	if (!(now-pendingTime > debounceDelay)) return;
	// 如果状态没有变化，就不管它
	if (pendingState == VerifiedStatus) return;
	// 如果状态变化了，就更新状态
	VerifiedStatus = pendingState;
	state = VerifiedStatus;
	// 如果有回调函数，就调用它
	if (callback) callback(state);
}

void Button::setCallback(Callback cb)
{
	callback = cb;
}


void Button::onInterrupt()
{
	read();
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
