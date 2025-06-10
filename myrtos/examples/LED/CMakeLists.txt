set(CMAKE_PROJECT_NAME example_led_${PROJECT_NAME})

project(${CMAKE_PROJECT_NAME} ASM C CXX)

add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32f103
)