//
// Created by Chord on 25-6-7.
//

#include "adcsensor.h"

adcsensor::adcsensor(GPIO_TypeDef* gpioPort, uint8_t gpioPin, ADC_HandleTypeDef * adc, DMA_HandleTypeDef * dma, uint32_t adcChannel) :
	gpioPort(gpioPort),
	gpioPin(gpioPin),
	adc(adc),
	dma(dma),
	adcChannel(adcChannel)
{
	// 初始化ADC缓冲区
	for (int i = 0; i < 10; i++) {
		adcBuffer[i] = 0;
	}
}

void adcsensor::init()
{
	// 初始化GPIO
	GPIO_InitTypeDef adcGPIO;
	adcGPIO.Pin = gpioPin;
	adcGPIO.Pull = GPIO_NOPULL;
	adcGPIO.Mode = GPIO_MODE_ANALOG; // 模拟输入模式
	adcGPIO.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(gpioPort, &adcGPIO);

	// 初始化ADC
	adc->Instance = ADC1;
	// 启动扫描模式
	adc->Init.ScanConvMode = ADC_SCAN_DISABLE;
	// 设置ADC通道
	adc->Init.NbrOfConversion = 1;

	// 启动连续转换模式
	adc->Init.ContinuousConvMode = ENABLE;
	// 硬件触发关闭
	adc->Init.ExternalTrigConv = ADC_EXTERNALTRIGCONVEDGE_NONE;
	// 数据右对齐
	adc->Init.DataAlign = ADC_DATAALIGN_RIGHT;
	HAL_ADC_Init(adc);

	// 初始化DMA
	__HAL_RCC_DMA1_CLK_ENABLE();
	dma->Instance = DMA1_Channel1;
	dma->Init.Direction = DMA_PERIPH_TO_MEMORY;
	dma->Init.PeriphInc = DMA_PINC_DISABLE; // 外设地址不递增
	dma->Init.MemInc = DMA_MINC_ENABLE;
	dma->Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD; // 外设对齐方式
	dma->Init.MemDataAlignment = DMA_PDATAALIGN_WORD; // 内存对齐方式
	dma->Init.Mode = DMA_CIRCULAR; // 循环模式
	dma->Init.Priority = DMA_PRIORITY_HIGH; // 高优先级
	HAL_DMA_Init(dma);

	// 关联DMA和ADC
	__HAL_LINKDMA(adc, DMA_Handle, *dma);

	// set adc device 1
	ADC_ChannelConfTypeDef adcChannelConfig;
	// ADC通道
	adcChannelConfig.Channel = adcChannel;
	// 优先级
	adcChannelConfig.Rank = ADC_REGULAR_RANK_1;
	// 采样时间
	adcChannelConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
	HAL_ADC_ConfigChannel(adc, &adcChannelConfig);
	dma->Parent = adc;

}

void adcsensor::startDMA() {
	HAL_ADC_Start_DMA(adc, adcBuffer, 10); // 启动 ADC 和 DMA，采集 10 个数据
}

uint32_t* adcsensor::getBuffer()
{
	return adcBuffer;
}
