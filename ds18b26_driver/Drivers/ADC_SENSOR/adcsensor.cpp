#include "adcsensor.h"

adcsensor::adcsensor(GPIO_TypeDef* gpioPort, uint16_t gpioPin, ADC_HandleTypeDef* hadc,uint32_t channel, DMA_HandleTypeDef* hdma) :
	gpioPort(gpioPort), gpioPin(gpioPin), hadc(hadc), hdma(hdma)
{}

void adcsensor::init()
{
	// 配置GPIO引脚为模拟输入模式
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = gpioPin;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(gpioPort, &GPIO_InitStruct);

	// 初始化DMA
	__HAL_RCC_DMA1_CLK_ENABLE();
	hdma->Instance = DMA1_Channel1; // 视你的ADC通道而定
	hdma->Init.Direction = DMA_PERIPH_TO_MEMORY;
	hdma->Init.PeriphInc = DMA_PINC_DISABLE;
	hdma->Init.MemInc = DMA_MINC_ENABLE;
	hdma->Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	hdma->Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	hdma->Init.Mode = DMA_CIRCULAR;
	hdma->Init.Priority = DMA_PRIORITY_LOW;
	HAL_DMA_Init(hdma);

	// 关联DMA到ADC
	__HAL_LINKDMA(hadc, DMA_Handle, *hdma);

	// 初始化ADC设备
	hadc->Instance = ADC1; // 根据实际ADC外设修改
	hadc->Init.ContinuousConvMode = ENABLE;           // 使能连续转换
	hadc->Init.DataAlign = ADC_DATAALIGN_RIGHT;       // 数据右对齐
	hadc->Init.ScanConvMode = ADC_SCAN_DISABLE;       // 单通道
	hadc->Init.ExternalTrigConv = ADC_SOFTWARE_START; // 软件触发
	hadc->Init.DiscontinuousConvMode = DISABLE;
	hadc->Init.NbrOfConversion = 1;
	if (HAL_ADC_Init(hadc) != HAL_OK)
	{
		// 错误处理
	}

	// 配置ADC通道
	ADC_ChannelConfTypeDef sConfig = {0};
	sConfig.Channel = channel;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES_5; // 推荐采样时间
	if (HAL_ADC_ConfigChannel(hadc, &sConfig) != HAL_OK)
	{
		// 错误处理
	}
}
void adcsensor::startDMA()
{
	HAL_ADC_Start_DMA(hadc, (uint32_t*)buffer, 1); // buffer为你的数据缓存
}
uint32_t adcsensor::getBuffer()
{
	// 读取DMA缓冲区数据
	// 这里可以根据需要处理buffer中的数据
	return buffer[0]; // 返回第一个采样值
}