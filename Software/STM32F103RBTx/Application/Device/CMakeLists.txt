cmake_minimum_required(VERSION 3.28)
project(Device LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Device library
add_library(Device STATIC)

target_sources(Device PRIVATE
    Src/CacheMeasurementRecorder.cpp
    Src/CobsEncoder.cpp
    Src/Crc32.cpp
    Src/DisplayBrightnessRegulator.cpp
    Src/Display.cpp
    Src/Keyboard.cpp
    Src/PulseCounterMeasurementSource.cpp
    Src/SdCardMeasurementRecorder.cpp
    Src/UartMeasurementRecorder.cpp
    Src/UartMeasurementSource.cpp
    Src/WiFiMeasurementRecorder.cpp
    Src/WiFiMeasurementSerializer.cpp
)

target_include_directories(Device PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/cppsrc
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/csrc
)
