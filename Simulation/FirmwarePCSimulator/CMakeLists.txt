# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(FirmwarePCSimulator LANGUAGES C CXX)


include_directories(
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Inc
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Device/Inc
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Inc

    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/BusinessLogic/Interfaces
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Device/Interfaces
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Interfaces

    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Middlewares/Third_Party/stm32-st7735/st7735
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Core/Inc
    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Stub/Application/Driver/
    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Stub/Application/Driver/Inc
    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Stub/System/
)


file(GLOB SIMULATOR_DRIVER_SRC
    "${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Stub/Driver/Src/*.cpp"
)

# Manually specify the additional .cpp files to include
set(SIMULATOR_SRC
    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Simulation.cpp
    #  ../../Software/NUCLEO-F103RB/Application/Driver/St7735DisplayDriver.cpp
    #${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Core/Src/MyApplication.cpp
    # ../stubs/System/stm32f1xx_hal.c
    #${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Stub/Driver/Src/*cpp
    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Stub/System/stm32f1xx_hal.c
    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Stub/System/PlatformFactoryStm32.cpp
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Middlewares/Third_Party/stm32-st7735/st7735/fonts.c
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Middlewares/Third_Party/stm32-st7735/st7735/st7735.c
)


# Create the executable for the firmware simulator
add_library(FirmwarePCSimulator SHARED ${SIMULATOR_SRC} ${SIMULATOR_DRIVER_SRC})


# Link the libraries from the Application project
target_link_libraries(FirmwarePCSimulator
    BusinessLogic
    Device
)


