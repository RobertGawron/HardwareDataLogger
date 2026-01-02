cmake_minimum_required(VERSION 3.28)
project(Device LANGUAGES CXX)

# Device library
add_library(Device STATIC)

target_sources(Device PRIVATE
    Src/DisplayBrightness.cpp
    Src/Display.cpp
    Src/Keyboard.cpp
    Src/PulseCounterSource.cpp
    Src/SdCardRecorder.cpp
    Src/UartRecorder.cpp
    Src/UartSource.cpp
    Src/WiFiRecorder.cpp
)

target_include_directories(Device PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/cppsrc
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/csrc
)


if(CMAKE_PROJECT_NAME STREQUAL "HardwareDataLogger_STM32F103RBTx")

    message(STATUS "Building for STM32 hardware")

    target_include_directories(Device PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../Driver/Hardware/Inc

        ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32F1xx_HAL_Driver/Inc
        ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Device/ST/STM32F1xx/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/../../Core/Inc
        ${CMAKE_CURRENT_SOURCE_DIR}/../Library/stm32-st7735/
        ${CMAKE_CURRENT_SOURCE_DIR}/../../Middlewares/Third_Party/FatFs/src
        ${CMAKE_CURRENT_SOURCE_DIR}/../../FATFS/Target
        ${CMAKE_CURRENT_SOURCE_DIR}/../
    )
    target_link_libraries(Device PUBLIC
        Driver
    )
else()
    message(STATUS "Building for host/testing")

    target_include_directories(Device PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../Driver/Host/Inc
    )
    
    if(TARGET Driver)
        target_link_libraries(Device PUBLIC Driver)
    endif()

endif()