STM32 OOP 开发指南

> [!TIP]
>
> STM32CubeMX生成的功能天然支持C++，但是main只支持.c，需要手动迁移到c++中
>
> 我的方案是在CMakeFile.txt里排除`main.c`，手动维护`main.cpp`
>
> 目的在于利用CubeMX生成的自动化，降低新增功能时的额外开销
>
> 之后如果有需要会写自动适配脚本

**如何开发**

- 添加新设备驱动

  1. 在`Drivers`文件夹中创建驱动目录，内部至少包含`.cpp`和`.h`

  2. 在文件头包含

     ```c++
     #include "stm32f1xx_hal.h"
     ```

  3. 修改`CMakeFiles.txt`

     1. 在`include_directories`中添加对应文件夹

        目的：添加头文件搜索目录，将帮助编译器在编译时识别和使用函数、类型、宏声明等

     2. 确认现有`file(GLOB_RECURSE SOURCES`中记录的路径通配符是否覆盖到当前目录

        目的：递归查找并收集所有源文件，并把它们存入 `SOURCES` 变量中

     > [!NOTE]
     >
     > 接下来编译器将会通过
     >
     > ```c++
     > add_executable(${PROJECT_NAME}.elf ${SOURCES} ${LINKER_SCRIPT})
     > ```
     >
     > 这个语句，将编译输出的.obj文件链接成一个可烧录进单片机的.elf文件

  4. 只有.h需要写`#include`,.cpp/.c只需要include .h即可。