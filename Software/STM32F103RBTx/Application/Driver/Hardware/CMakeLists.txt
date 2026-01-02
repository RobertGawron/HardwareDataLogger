cmake_minimum_required(VERSION 3.22)
project(Driver LANGUAGES C CXX)

# Driver library
add_library(Driver STATIC)

target_sources(Driver PRIVATE
    Src/LightSensorDriver.cpp
    Src/DisplayPixelColor.cpp
    Src/KeyboardDriver.cpp
    Src/PulseCounterDriver.cpp
    Src/SdCardDriver.cpp
    Src/BrightnessDriver.cpp
    Src/DisplayDriver.cpp
    Src/UartDriver.cpp
    # From outside of Cube MX
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../FATFS/Target/user_diskio_spi.c
)

target_include_directories(Driver PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)


target_include_directories(Driver PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Drivers/STM32F1xx_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Drivers/CMSIS/Device/ST/STM32F1xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Library/stm32-st7735/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../Middlewares/Third_Party/FatFs/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../FATFS/Target
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
)

# Debug options
target_compile_options(Driver PRIVATE 
    $<$<CONFIG:Debug>:-g3>
)

# Enable PIC for linking into shared libraries
set_target_properties(Driver PROPERTIES POSITION_INDEPENDENT_CODE ON)