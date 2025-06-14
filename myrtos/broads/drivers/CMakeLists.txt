file(GLOB_RECURSE DRIVER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE DRIVER_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(drivers STATIC ${DRIVER_SOURCES} ${DRIVER_HEADERS})

target_include_directories(drivers PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/../stm32c8t6/Core/Inc
	${CMAKE_CURRENT_SOURCE_DIR}/../stm32c8t6/Drivers/STM32F1xx_HAL_Driver/Inc/Legacy
	${CMAKE_CURRENT_SOURCE_DIR}/../stm32c8t6/Drivers/STM32F1xx_HAL_Driver/Inc
	${CMAKE_CURRENT_SOURCE_DIR}/../stm32c8t6/Middlewares/Third_Party/FreeRTOS/Source/include
	${CMAKE_CURRENT_SOURCE_DIR}/../stm32c8t6/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2
	${CMAKE_CURRENT_SOURCE_DIR}/../stm32c8t6/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3
	${CMAKE_CURRENT_SOURCE_DIR}/../stm32c8t6/Drivers/CMSIS/Device/ST/STM32F1xx/Include
	${CMAKE_CURRENT_SOURCE_DIR}/../stm32c8t6/Drivers/CMSIS/Include
xx)