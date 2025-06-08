/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
// #include "stm32f1xx_hal.h"
#include "main.h"

#include "adc.h"
#include "adcsensor.h"
#include "buttonbase.h"
#include "buttonnvicmanager.h"
#include "ds18b20.h"
#include "gpio.h"
#include "led.h"
#include "pwmfandriver.h"
#include "tim.h"
#include "uart.h"
#include "usart.h"

void SystemClock_Config(void);

LED blueLED(GPIOA, GPIO_PIN_4);
UART uart1(&huart1, 921600, 1000);
Button button1(GPIOA, GPIO_PIN_6);
DS18B20 ds18b20(GPIOA, DS18B20_Pin, &htim1);
PWM_FAN_DRIVER pwmfan(GPIOB, GPIO_PIN_0);
buttonnvicmanager buttonNvicManager(button1, EXTI9_5_IRQn);
DMA_HandleTypeDef dma;
adcsensor adcSensor(GPIOA, GPIO_PIN_0, &hadc1, ADC_CHANNEL_0, &dma);

uint8_t runtimes = 0;
enum TempReadState { TEMP_IDLE, TEMP_CONVERTIONG};
TempReadState tempState = TEMP_IDLE; // 温度读取状态
uint32_t ReadTempTime = 0;

bool tempFlag = false;
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    uart1.printf("DMA callback! buffer[0]=%u\r\n", adcSensor.getBuffer());
}

void callback(bool pressed)
{
	if (pressed)
	{
		uart1.print("Presses!");
	}
}

/**
 * @brief  主程序
 * @retval int
 */
int main(void)
{
	// 初始化HAL库
    HAL_Init();
	// 配置系统时钟
    SystemClock_Config();
    // 初始化串口
	MX_USART1_UART_Init();

	uart1.init();


	blueLED.init();

	adcSensor.init();
	adcSensor.startDMA();

    while (1) {
    	uart1.printf("get buffer: %u\r\n", adcSensor.getBuffer());
    }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** 根据 RCC_OscInitTypeDef 结构体中指定的参数初始化 RCC 振荡器。 */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** 初始化CPU总线时钟、APB1和APB2总线时钟 */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

/** 这个函数在发生错误时执行
 *  @retval None
 */
void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  报告发生 assert_param 错误的源文件名称和源代码行号。
  * @param  file: 指向源文件名称的指针
  * @param  line: assert_param 错误发生的源代码行号
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* 在这里实现错误报告 */
}
#endif