//
// Created by RinChord on 25-6-3.
//

#include "pwmfandriver.h"

PWM_FAN_DRIVER(GPIO_TypeDef* gpioPort, uint16_t gpioPin)
	: gpioPort(gpioPort), gpioPin(gpioPin), temp(0) {
}


void PWM_FAN_DRIVER::init()
{
	// 将GPIO初始化为复用推挽输出模式
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.Pin = gpioPin;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(gpioPort, &GPIO_InitStructure);

	// 配置pwm发生源
	TIM_HandleTypeDef htim3;
	TIM_OC_InitTypeDef sConfigOC;

	// 启用TIM3时钟
	__HAL_RCC_TIM3_CLK_ENABLE();
	// 配置PWM的相关信息
	htim3.Init.Prescaler = (uint16_t)(SystemCoreClock / 1000000) - 1; // 计数频率1Mhz
	htim3.Init.Period = 39; // 计数周期为40us，对应25KHz的PWM频率
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP; // 向上计数
	htim3.Init.AutoReloadPreload = TIM_AUTOMATICOUTPUT_DISABLE;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // 时钟分频系数为1
	// 指派单片机的实际外设
	htim3.Instance = TIM3;
	HAL_TIM_PWM_Init(&htim3);

	sConfigOC.OCMode = TIM_OCMODE_PWM1; // PWM模式1
	sConfigOC.Pulse = 0; // 初始占空比为0
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH; // 输出极性为高
	HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3); // 配置通道3 PWM输出

	// 启动PWM输出
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

}
