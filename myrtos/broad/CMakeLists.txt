cmake_minimum_required(VERSION 3.22)

project(stm32f103)

# 递归查找 broad 目录下所有 C 源文件和汇编文件
file(GLOB_RECURSE BROAD_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.s"
)


# 创建静态库
add_library(stm32f103 STATIC ${BROAD_SOURCES})

# 递归查找 broad 目录下所有头文件目录
file(GLOB_RECURSE BROAD_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
set(BROAD_INCLUDE_DIRS "")
foreach(header ${BROAD_HEADERS})
    get_filename_component(dir ${header} DIRECTORY)
    list(APPEND BROAD_INCLUDE_DIRS ${dir})
endforeach()
list(REMOVE_DUPLICATES BROAD_INCLUDE_DIRS)

target_include_directories(stm32f103 PUBLIC
    ${BROAD_INCLUDE_DIRS}
)

add_subdirectory(cmake/stm32cubemx)