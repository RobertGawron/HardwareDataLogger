cmake_minimum_required(VERSION 3.28)
project(BusinessLogic LANGUAGES CXX)

# Enable C++23 and module support
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable experimental C++ module support
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

add_library(BusinessLogic STATIC)

target_sources(BusinessLogic
    PUBLIC
        FILE_SET logic_public 
        TYPE CXX_MODULES 
        FILES
            Modules/ApplicationFacade.cppm
            Modules/HmiFacade.cppm
            Modules/MeasurementCoordinator.cppm
            Modules/ApplicationComponent.cppm
    #PRIVATE
    #    FILE_SET logic_private 
    #    TYPE CXX_MODULES 
    #    FILES
    # No private modules yet

)

target_sources(BusinessLogic PRIVATE
    Src/ApplicationFacade.cpp
    Src/HmiFacade.cpp
)

target_include_directories(BusinessLogic PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/cppsrc
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/csrc
)

target_link_libraries(BusinessLogic 
    PUBLIC DriverInterface
    PUBLIC Device # TODO is it really need to be public?
    PUBLIC Driver
    PRIVATE u8g2
)


target_include_directories(BusinessLogic PUBLIC
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
