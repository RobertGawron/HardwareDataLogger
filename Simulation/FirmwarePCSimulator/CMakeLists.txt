# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(FirmwarePCSimulator LANGUAGES C CXX)


include_directories(
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Inc/

    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Middlewares/Third_Party/stm32-st7735/st7735
    ${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Core/Inc
    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Mock/Application/Driver/
    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Mock/Application/Driver/Inc
    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Mock/System/
)


file(GLOB SIMULATOR_DRIVER_SRC
    "${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Mock/Application/Driver/Src/*.cpp"

    "${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Application/Driver/Src/DriverState.cpp"
)

# Manually specify the additional .cpp files to include
set(SIMULATOR_SRC
    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Simulation.cpp
    #  ../../Software/NUCLEO-F103RB/Application/Driver/St7735DisplayDriver.cpp
    #${CMAKE_SOURCE_DIR}/Software/NUCLEO-F103RB/Core/Src/MyApplication.cpp
    # ../Mocks/System/stm32f1xx_hal.c
    #${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Mock/Driver/Src/*cpp
    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Mock/System/stm32f1xx_hal.c
    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/Mock/System/PlatformFactoryStm32.cpp
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


