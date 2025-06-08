//
// Created by RinChord on 25-5-31.
//

#include "buttonbase.h"
#include "buttonnvicmanager.h"
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_it.h"

extern Button button1;
extern buttonnvicmanager buttonNvicManager;

// 这是一个通用中断回调函数，处理GPIO中断
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	buttonNvicManager.handleInterrupt(GPIO_Pin);
}