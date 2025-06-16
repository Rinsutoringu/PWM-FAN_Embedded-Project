function(add_board_specific_library name)
	cmake_parse_arguments(ARG "" "TARGET" "SOURCES;INCLUDES;DEPENDS" ${ARGN})
	add_library(${name} OBJECT ${ARG_SOURCES})
	target_link_libraries(${name}
			PUBLIC ${ARG_TARGET}_interface
			PRIVATE ${ARG_DEPENDS})
	target_include_directories(${name} PUBLIC ${ARG_INCLUDES})
endfunction(add_board_specific_library)


function(add_arm_executable name)
	cmake_parse_arguments(ARG "" "TARGET" "SOURCES;INCLUDES;DEPENDS;DEFINES" ${ARGN})
	set(HEX_FILE ${CMAKE_CURRENT_BINARY_DIR}/${name}.hex)
	set(BIN_FILE ${CMAKE_CURRENT_BINARY_DIR}/${name}.bin)
	set(MAP_FILE ${CMAKE_CURRENT_BINARY_DIR}/${name}.map)

	add_executable(${name}.elf ${ARG_SOURCES})

	target_link_libraries(${name}.elf
			PRIVATE ${ARG_DEPENDS} ${ARG_TARGET} ${ARG_TARGET}_platform ${ARG_TARGET}_drivers)

	target_include_directories(${name}.elf PRIVATE ${ARG_INCLUDES})
	target_compile_definitions(${name}.elf PRIVATE ${ARG_DEFINES})
	target_link_options(${name}.elf PRIVATE -Wl,--print-memory-usage,-Map=${MAP_FILE})

	find_program(ARM_SIZE arm-none-eabi-size REQUIRED)
	find_program(ARM_OBJCOPY arm-none-eabi-objcopy REQUIRED)
	add_custom_command(TARGET ${name}.elf POST_BUILD
			COMMAND ${ARM_SIZE} ${name}.elf
			COMMAND ${ARM_OBJCOPY} -Oihex $<TARGET_FILE:${name}.elf> ${HEX_FILE}
			COMMAND ${ARM_OBJCOPY} -Obinary $<TARGET_FILE:${name}.elf> ${BIN_FILE}
			COMMENT "Building ${HEX_FILE}\nBuilding ${BIN_FILE}")

	# DEBUG
	message(STATUS "ARG_SOURCES = ${ARG_SOURCES}")
	message(STATUS "ARG_TARGET = ${ARG_TARGET}")
	message(STATUS "ARG_TARGET = ${ARG_TARGET}_drivers")
endfunction(add_arm_executable)