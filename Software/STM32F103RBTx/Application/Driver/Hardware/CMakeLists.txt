cmake_minimum_required(VERSION 3.28)
project(Driver LANGUAGES CXX)

# Enable C++23 and module support
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable experimental C++ module support
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

# Driver library
add_library(Driver STATIC)

target_link_libraries(Driver PUBLIC DriverInterface)

# Add module interface files
target_sources(Driver
    PUBLIC
        FILE_SET driver_interface_public
        TYPE CXX_MODULES 
        FILES
            Modules/BrightnessDriver.cppm
            Modules/DisplayDriver.cppm
             Modules/Driver.cppm
            Modules/KeyboardDriver.cppm
            Modules/LightSensorDriver.cppm
            Modules/PulseCounterDriver.cppm
            Modules/PlatformFactory.cppm
            
            Modules/SdCardDriver.cppm
            Modules/UartDriver.cppm
    #PRIVATE
    #    FILE_SET driver_private 
    #    TYPE CXX_MODULES 
    #    FILES  
)



target_sources(Driver PRIVATE
    Src/LightSensorDriver.cpp
    Src/KeyboardDriver.cpp
    Src/PulseCounterDriver.cpp
    Src/SdCardDriver.cpp
    Src/BrightnessDriver.cpp
    Src/DisplayDriver.cpp
    Src/UartDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../FATFS/Target/user_diskio_spi.c
)

target_include_directories(Driver PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/cppsrc
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/csrc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Drivers/STM32F1xx_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Drivers/CMSIS/Driver/ST/STM32F1xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Library/stm32-st7735/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Middlewares/Third_Party/FatFs/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../FATFS/Target
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Drivers/CMSIS/Device/ST/STM32F1xx/Include/
)

