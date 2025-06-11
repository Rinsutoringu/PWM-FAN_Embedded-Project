cmake_minimum_required(VERSION 3.22)

include(cmake/gcc-arm-none-eabi.cmake)

add_definitions(-DSTM32F103xB)
add_definitions(-DCMSIS_device_header="stm32f1xx.h")

project(myrtos)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_subdirectory(broad)
add_subdirectory(examples)

