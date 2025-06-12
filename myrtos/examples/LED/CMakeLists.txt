set(CMAKE_PROJECT_NAME example_led_${PROJECT_NAME})

project(${CMAKE_PROJECT_NAME} ASM C CXX)

add_executable(${CMAKE_PROJECT_NAME}
		Src/blueled.cpp
		Src/redled.cpp
		Src/main.cpp
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE Inc)

target_link_libraries(${CMAKE_PROJECT_NAME}
		stm32cubemx
)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE -Wl,--gc-sections)