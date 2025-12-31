cmake_minimum_required(VERSION 3.28)
project(Device LANGUAGES CXX)

# Device library
add_library(Device STATIC)

target_sources(Device PRIVATE
    Src/CacheMeasurementRecorder.cpp
    Src/DisplayBrightnessRegulator.cpp
    Src/Display.cpp
    Src/Keyboard.cpp
    Src/PulseCounterMeasurementSource.cpp
    Src/SdCardMeasurementRecorder.cpp
    Src/UartMeasurementRecorder.cpp
    Src/UartMeasurementSource.cpp
    Src/WiFiMeasurementRecorder.cpp
)

target_include_directories(Device PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces
    ${CMAKE_CURRENT_SOURCE_DIR}/..
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/cppsrc
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/csrc
)
