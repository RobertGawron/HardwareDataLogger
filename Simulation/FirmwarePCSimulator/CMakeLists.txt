# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(FirmwarePCSimulator LANGUAGES C CXX)

# Enable position-independent code for compatibility with shared libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Include directories scoped to each target
set(INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Inc/
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Interfaces/
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Middlewares/Third_Party/stm32-st7735
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Middlewares/Third_Party/stm32-st7735
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Middlewares/Third_Party/u8g2/cppsrc
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Middlewares/Third_Party/u8g2/csrc
    ${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Core/Inc
    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Mock/Application/Driver/Inc
    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Mock/System/
)

# Gather source files for the Driver and Platform components
file(GLOB SIMULATOR_DRIVER_SRC
    "${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Mock/Application/Driver/Src/*.cpp"
   # "${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/St7735DisplayDriver.cpp"
    "${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DriverState.cpp"
    "${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application/Driver/Src/DisplayPixelColor.cpp"
)

file(GLOB SIMULATOR_PLATFORM_SRC
    "${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Core/Src/MyApplication.cpp"
    #"${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Mock/System/stm32f1xx_hal.c"
    "${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Mock/System/PlatformFactoryStm32.cpp"
    "${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Mock/System/st7735_reg.c"
    "${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Mock/System/st7735.c"
    
    #"${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Middlewares/Third_Party/stm32-st7735/st7735/fonts.c"
    #"${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Middlewares/Third_Party/stm32-st7735/st7735/st7735.c" 
)

# Define DriverForSimulation as a shared library
add_library(DriverForSimulation SHARED ${SIMULATOR_DRIVER_SRC})
target_include_directories(DriverForSimulation PRIVATE ${INCLUDE_DIRS})

# Define PlatformForSimulation as a shared library
add_library(PlatformForSimulation SHARED ${SIMULATOR_PLATFORM_SRC})
target_include_directories(PlatformForSimulation PRIVATE ${INCLUDE_DIRS})

# Define FirmwarePCSimulator as the main shared library
set(SIMULATOR_SRC ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/LibWrapper.cpp)
add_library(FirmwarePCSimulator SHARED ${SIMULATOR_SRC})
target_include_directories(FirmwarePCSimulator PRIVATE ${INCLUDE_DIRS})

# Link dependencies for FirmwarePCSimulator
target_link_libraries(FirmwarePCSimulator
    PlatformForSimulation
    BusinessLogic
    Device
    DriverForSimulation
    u8g2
)
