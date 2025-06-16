project(example_led_${BOARD_NAME} ASM C CXX)

add_arm_executable(${PROJECT_NAME}
		TARGET ${BOARD_NAME}
		SOURCES
		Src/blueled.cpp
		Src/redled.cpp
		Src/main.cpp
)