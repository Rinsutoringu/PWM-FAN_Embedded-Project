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
        HAL_GPIO_TogglePin(BLUE_LED_GPIO_Port, BLUE_LED_Pin);
        osDelay(1000);
    }
}

#ifdef __cplusplus
}
#endif