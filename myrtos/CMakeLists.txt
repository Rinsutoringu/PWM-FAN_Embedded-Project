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
add_subdirectory(examples)
# Add programs
#add_subdirectory(programs)

