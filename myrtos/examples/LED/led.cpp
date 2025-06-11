//
// Created by Chord on 25-6-11.
//

#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "led.h"
#include "cmsis_os.h"
#include "stm32f1xx_it.h"


#ifdef __cplusplus
extern "C" {
#endif

void MydefaultTask(void *argument)
{
    UNUSED(argument);
    while (1)
    {
        osDelay(100);
        // HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, GPIO_PIN_RESET);
        // osDelay(1000);
        // HAL_GPIO_WritePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin, GPIO_PIN_SET);

    }
}

#ifdef __cplusplus
}
#endif