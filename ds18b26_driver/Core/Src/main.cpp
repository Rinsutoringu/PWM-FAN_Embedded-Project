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
#include "tim.h"
#include "gpio.h"
#include "led.h"
#include "usart.h"
#include "uart.h"
#include "button.h"
#include "ds18b20.h"
#include "pwmfandriver.h"



void SystemClock_Config(void);
static void MX_NVIC_Init(void);

LED blueLED(GPIOA, BLUE_LED_Pin);
UART uart1(&huart1, 921600, 1000);
Button button1(GPIOA, BUTTON_Pin);
DS18B20 ds18b20(GPIOA, DS18B20_Pin, &htim1);
PWM_FAN_DRIVER pwmfan(GPIOB, GPIO_PIN_0);

uint8_t runtimes = 0;
enum TempReadState { TEMP_IDLE, TEMP_CONVERTIONG};
TempReadState tempState = TEMP_IDLE; // 温度读取状态
uint32_t ReadTempTime = 0;

bool tempFlag = false;

void callback(bool pressed)
{
	if (pressed) tempFlag = true;
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
	// 初始化所有外设
	MX_GPIO_Init();
	// 初始化USART1
	MX_USART1_UART_Init();
	MX_TIM1_Init();
	MX_NVIC_Init();

	uart1.init();
	button1.setCallback(callback);
	ds18b20.init();
	pwmfan.init();

	uart1.print("init success!\r\n");
	blueLED.turnON();

    while (1)
    {
		runtimes++;
		if (runtimes >= 5)
		{
			if (tempState == TEMP_IDLE)
			{
				ds18b20.startConvert();
				ReadTempTime = HAL_GetTick();
				tempState = TEMP_CONVERTIONG;
			} else if (tempState == TEMP_CONVERTIONG)
			{
				if (HAL_GetTick() - ReadTempTime >= 750)
				{
					pwmfan.updateSpeed();
					tempState = TEMP_IDLE;
					ReadTempTime = 0;
				}
			}
			runtimes = 0;
		}

    	if (button1.getButtonFlag()) {
			button1.read(); // 轮询按钮状态
		}
		if (tempFlag)
		{
			uart1.printf("Get Temperature: %d\r\n", ds18b20.readTemperature());
			pwmfan.switchStatus();
			tempFlag = false;
		}


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

/**
 * 初始化NVIC中断
 */
static void MX_NVIC_Init(void)
{
	/* EXTI9_5_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
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