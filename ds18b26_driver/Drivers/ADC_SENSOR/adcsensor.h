
#pragma once
#include "stm32f1xx_hal.h"

/**
 * 此类负责初始化ADC外设，DMA由其他类管理
 */
class adcsensor
{
private:
	// 设备所在GPIO端口
	GPIO_TypeDef* gpioPort;
	// 设备所在GPIO引脚
	uint16_t gpioPin;
	// ADC句柄
	ADC_HandleTypeDef* hadc;
	DMA_HandleTypeDef* hdma;
	// ADC通道
	uint32_t channel_1;
	uint32_t channel_2;

	// DMA缓冲区
	uint16_t buffer[2]; // 假设只需要一个采样值
public:
	adcsensor(GPIO_TypeDef* gpioPort, uint16_t gpioPin, ADC_HandleTypeDef* hadc,uint32_t channel_1, uint32_t channel_2, DMA_HandleTypeDef* hdma);
	void init();
	void startDMA();
	uint32_t getBuffer(uint8_t idx);
};