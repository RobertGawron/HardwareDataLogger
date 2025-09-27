# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(SimulatorESP8266 LANGUAGES C CXX)

# Enable position-independent code for compatibility with shared libraries
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Include directories scoped to each target
set(INCLUDE_DIRS
BEFORE # The BEFORE keyword ensures that these directories are prioritized over the system's include paths.
    ${CMAKE_SOURCE_DIR}/Software/ESP8266/include
    ${CMAKE_SOURCE_DIR}/Software/Common
    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/ESP8266
    ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/ESP8266/Mocks/Inc
)

file(GLOB SIMULATOR_MAIN_SRC
    "${CMAKE_SOURCE_DIR}/Software/ESP8266/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/Software/ESP8266/lib/Device/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/Software/Common/*.cpp"
    "${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/ESP8266/*.cpp"
    "${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/ESP8266/Mocks/Src/*.cpp"
)

# Define DriverForSimulation as a shared library
add_library(MainSource SHARED ${SIMULATOR_MAIN_SRC})
target_include_directories(MainSource PRIVATE ${INCLUDE_DIRS})


# C:\Users\rober\Documents\HardwareDataLogger\Software\ESP8266\.vscode\c_cpp_properties.json
target_compile_definitions(MainSource PRIVATE 
    PLATFORMIO=60116
    ESP8266
    ARDUINO_ARCH_ESP8266
    ARDUINO_ESP8266_ADAFRUIT_HUZZAH
    F_CPU=80000000L
    __ets__
    ICACHE_FLASH
    _GNU_SOURCE
    ARDUINO=10805
    ARDUINO_BOARD="PLATFORMIO_HUZZAH"
    ARDUINO_BOARD_ID="huzzah"
    FLASHMODE_QIO
    LWIP_OPEN_SRC
    NONOSDK22x_190703=1
    TCP_MSS=536
    LWIP_FEATURES=1
    LWIP_IPV6=0
    VTABLES_IN_FLASH
    MMU_IRAM_SIZE=0x8000
    MMU_ICACHE_SIZE=0x8000
)

# Define FirmwarePCSimulator as the main shared library
set(SIMULATOR_SRC ${CMAKE_SOURCE_DIR}/Simulation/FirmwarePCSimulator/ESP8266/LibWrapper.cpp)
add_library(SimulatorESP8266 SHARED ${SIMULATOR_SRC})
target_include_directories(SimulatorESP8266 PRIVATE ${INCLUDE_DIRS})

target_link_libraries(SimulatorESP8266
MainSource 
)
