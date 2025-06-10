cmake_minimum_required(VERSION 3.22)

# 如果没有指定工具链，则自动设置
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/broad/cmake/gcc-arm-none-eabi.cmake" CACHE FILEPATH "Toolchain file")
endif()

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Add CubeMX generated files
add_subdirectory(broad)
# Add example project
#add_subdirectory(example)
# Add programs
#add_subdirectory(programs)



## Define the build type
#if(NOT CMAKE_BUILD_TYPE)
#    set(CMAKE_BUILD_TYPE "Debug")
#endif()
#

#

#
## Enable compile command to ease indexing with e.g. clangd
#set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
#

#
## Core project settings
#project(${CMAKE_PROJECT_NAME})
#message("Build type: " ${CMAKE_BUILD_TYPE})
#
## Create an executable object type
#add_executable(${CMAKE_PROJECT_NAME})
#
## Add STM32CubeMX generated sources
#add_subdirectory(cmake/stm32cubemx)
#
## Link directories setup
#target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
#    # Add user defined library search paths
#)
#
## Add sources to executable
#target_sources(${CMAKE_PROJECT_NAME} PRIVATE
#    # Add user sources here
#)
#
## Add include paths
#target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
#    # Add user defined include paths
#)
#
## Add project symbols (macros)
#target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
#    # Add user defined symbols
#)
#
## Add linked libraries
#target_link_libraries(${CMAKE_PROJECT_NAME}
#    stm32cubemx
#
#    # Add user defined libraries
#)
