//
// Created by Chord on 25-6-7.
//
#pragma once
#include "buttonbase.h"

class buttonnvicmanager {
public:
	buttonnvicmanager(Button& button, IRQn_Type irqn);
	void init();
	void handleInterrupt(uint8_t GPIO_Pin);
private:
	Button& button;
	// 中断号
	IRQn_Type irqn;
};



