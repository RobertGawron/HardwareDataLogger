cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

add_library(Driver STATIC)

# Link dependencies
target_link_libraries(Driver 
    PUBLIC DriverInterface
    PRIVATE u8g2
)

target_sources(Driver
    PUBLIC FILE_SET CXX_MODULES FILES
        Modules/BrightnessDriver.cppm
        Modules/DisplayDriver.cppm
        Modules/Driver.cppm
        Modules/KeyboardDriver.cppm
        Modules/LightSensorDriver.cppm
        Modules/PlatformFactory.cppm
        Modules/PulseCounterDriver.cppm
        Modules/SdCardDriver.cppm
        Modules/UartDriver.cppm
)

target_sources(Driver PRIVATE
    Src/BrightnessDriver.cpp
    Src/DisplayDriver.cpp
    Src/KeyboardDriver.cpp
    Src/LightSensorDriver.cpp
    Src/PulseCounterDriver.cpp
    Src/SdCardDriver.cpp
    Src/UartDriver.cpp
    ../../../FATFS/Target/user_diskio_spi.c
)

target_include_directories(Driver PRIVATE
    ../../../Drivers/STM32F1xx_HAL_Driver/Inc
    ../../../Drivers/CMSIS/Driver/ST/STM32F1xx/Include
    ../../../Drivers/CMSIS/Include
    ../../../Core/Inc
    ../../Library/stm32-st7735
    ../../../Middlewares/Third_Party/FatFs/src
    ../../../FATFS/Target
    ../../../Drivers/CMSIS/Device/ST/STM32F1xx/Include
)