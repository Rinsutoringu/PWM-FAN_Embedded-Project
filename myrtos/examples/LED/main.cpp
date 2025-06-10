//
// Created by Chord on 25-6-11.
//

#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "main.h"
#include "cmsis_os.h"
#include "stm32f1xx_it.h"


void MydefaultTask(const void* args)
{
    UNUSED(args);
    while (1)
    {
        // HAL_GPIO_TogglePin(BLUE_LED_Pin, BLUE_LED_GPIO_Port); // Toggle the blue LED
        osDelay(1000); // Delay for 1000 ms
    }
}