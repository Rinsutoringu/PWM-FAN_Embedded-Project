//
// Created by Chord on 25-6-7.
//

#pragma once

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_adc.h"

#include "uart.h"

extern UART uart1;


class adcsensor {
private:
	GPIO_TypeDef* gpioPort;
	uint8_t gpioPin;
	// ADC硬件句柄
	ADC_HandleTypeDef * adc;
	DMA_HandleTypeDef * dma;
	uint32_t adcChannel;

	// ADC缓冲区
	uint32_t adcBuffer[10];

public:
	adcsensor(GPIO_TypeDef* gpioPort, uint8_t gpioPin, ADC_HandleTypeDef * adc, DMA_HandleTypeDef * dma, uint32_t adcChannel);
	void init();
	void startDMA();
	uint32_t* getBuffer();


};



