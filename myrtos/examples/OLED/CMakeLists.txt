set(CMAKE_PROJECT_NAME example_oled_${PROJECT_NAME})

project(${CMAKE_PROJECT_NAME} ASM C CXX)

add_executable(${CMAKE_PROJECT_NAME}
		oled.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME}
		stm32cubemx
)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE -Wl,--gc-sections)