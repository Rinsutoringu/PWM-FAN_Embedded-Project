//
// Created by RinChord on 25-5-31.
//
#include "stm32f1xx_hal.h"
#pragma once


class Button {
public:
	typedef void (*Callback)(bool pressed);
	Button(GPIO_TypeDef* gpioPort, uint16_t gpioPin);
	void read(); // 轮询模式，获取消抖后的按钮状态
	void onInterrupt(); // 中断回调函数
	bool getIsEnable(); // 获取按钮可用性
	void enable(); // 启用按钮
	void disable(); // 禁用按钮
	void setDebounceDelay(uint32_t delay); // 设置消抖延迟
	void setCallback(Callback cb); // 设置回调

private:
	// 按钮状态
	bool state;
	// 按钮可用性
	bool isEnable;
	// 目标按钮所连接到的GPIO端口（假设为某个具体的端口）
	GPIO_TypeDef* gpioPort;
	// 目标按钮所连接到的GPIO引脚（假设为某个具体的引脚）
	uint16_t gpioPin;
	// 消抖延迟
	uint32_t debounceDelay;
	// 最近的按钮状态
	bool pendingState;
	// 获取到最近按钮状态时的时间
	uint32_t pendingTime;
	// 经过校验的上一个状态
	bool VerifiedStatus;
	// 该按钮的回调函数
	Callback callback;


};


