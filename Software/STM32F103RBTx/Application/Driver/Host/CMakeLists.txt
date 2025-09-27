cmake_minimum_required(VERSION 3.28)
project(SimulatorSTM32F103RBTx LANGUAGES C CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Base paths
set(APP_ROOT "${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Application")
set(CORE_ROOT "${CMAKE_SOURCE_DIR}/Software/STM32F103RBTx/Core")
set(MOCK_ROOT "${APP_ROOT}/Driver/Host")

# Common includes
add_library(SimulatorIncludes INTERFACE)
target_include_directories(SimulatorIncludes INTERFACE
    ${APP_ROOT}
    ${APP_ROOT}/Driver/Interface
    ${APP_ROOT}/Library/stm32-st7735
    ${APP_ROOT}/Library/u8g2/cppsrc
    ${APP_ROOT}/Library/u8g2/csrc
    ${CORE_ROOT}/Inc
    ${MOCK_ROOT}/Inc
    ${MOCK_ROOT}
)

# Collect driver simulation sources that exist
set(DRIVER_SOURCES)

file(GLOB MOCK_ROOT_SOURCES "${MOCK_ROOT}/*.cpp")
list(APPEND DRIVER_SOURCES ${MOCK_ROOT_SOURCES})

file(GLOB MOCK_DRIVER_SOURCES "${MOCK_ROOT}/Src/*.cpp")
list(APPEND DRIVER_SOURCES ${MOCK_DRIVER_SOURCES})

# Add specific driver sources if they exist
foreach(src IN ITEMS
    "${APP_ROOT}/Driver/Hardware/Src/DriverState.cpp"
    "${APP_ROOT}/Driver/Hardware/Src/DisplayPixelColor.cpp"
)
    if(EXISTS ${src})
        list(APPEND DRIVER_SOURCES ${src})
    endif()
endforeach()

# Only create library if we have sources
if(DRIVER_SOURCES)
    add_library(DriverSimulation SHARED ${DRIVER_SOURCES})
    target_link_libraries(DriverSimulation PRIVATE SimulatorIncludes)
else()
    message(WARNING "No driver simulation sources found")
endif()

# Main simulator library
add_library(SimulatorSTM32F103RBTx SHARED
    "${APP_ROOT}/../Core/Src/MyApplication.cpp"
    "${MOCK_ROOT}/LibWrapper.cpp"
    "${MOCK_ROOT}/EventHandlers.cpp"
)

target_link_libraries(SimulatorSTM32F103RBTx
    PRIVATE SimulatorIncludes
    PUBLIC
        $<TARGET_NAME_IF_EXISTS:PlatformSimulation>
        BusinessLogic
        Device
        $<TARGET_NAME_IF_EXISTS:DriverSimulation>
        u8g2
)

set_target_properties(SimulatorSTM32F103RBTx PROPERTIES
    OUTPUT_NAME "simulator_stm32f103"
    VERSION 1.0.0
    SOVERSION 1
)

# Enable compile_commands.json export for SimulatorSTM32F103RBTx
if(DEFINED EXPORT_SINGLE_JSON AND EXPORT_SINGLE_JSON STREQUAL "SIMULATION_LIB")
    message(STATUS "Enabling compile_commands.json export for: SimulatorSTM32F103RBTx")
    set_target_properties(SimulatorSTM32F103RBTx PROPERTIES EXPORT_COMPILE_COMMANDS ON)
endif()