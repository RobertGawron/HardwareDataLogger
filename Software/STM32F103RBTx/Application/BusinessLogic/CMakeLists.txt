cmake_minimum_required(VERSION 3.28)
project(BusinessLogic LANGUAGES CXX)

# BusinessLogic library
add_library(BusinessLogic STATIC)

target_sources(BusinessLogic PRIVATE
    Src/ApplicationFacade.cpp
    Src/HmiFacade.cpp
)

target_include_directories(BusinessLogic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/cppsrc
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/csrc
)


if(CMAKE_PROJECT_NAME STREQUAL "HardwareDataLogger_STM32F103RBTx")

    message(STATUS "Building for STM32 hardware")

    target_include_directories(BusinessLogic PUBLIC
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

else()
    message(STATUS "Building for host/testing")

    target_include_directories(BusinessLogic PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../Driver/Host/Inc
    )

endif()