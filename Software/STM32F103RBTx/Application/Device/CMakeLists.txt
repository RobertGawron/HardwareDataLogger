cmake_minimum_required(VERSION 3.31)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

add_library(Device STATIC)

target_link_libraries(Device PRIVATE
    Driver
    u8g2
)

# Module interface files
target_sources(Device PUBLIC FILE_SET CXX_MODULES FILES
    Modules/CobsEncoder.cppm
    Modules/Crc32.cppm
    Modules/Device.cppm
    Modules/DeviceComponent.cppm
    Modules/Display.cppm
    Modules/DisplayBrightness.cppm
    Modules/DisplayPixelColor.cppm
    Modules/Keyboard.cppm
    Modules/KeyAction.cppm
    Modules/MeasurementDeviceId.cppm
    Modules/MeasurementRecorder.cppm
    Modules/MeasurementSource.cppm
    Modules/MeasurementType.cppm
    Modules/PulseCounterSource.cppm
    Modules/RecorderVariant.cppm
    Modules/SdCardRecorder.cppm
    Modules/SourceVariant.cppm
    Modules/UartRecorder.cppm
    Modules/UartSource.cppm
    Modules/WiFiRecorder.cppm
    Modules/WiFiSerializer.cppm
)

target_sources(Device PRIVATE
    Src/Display.cpp
    Src/DisplayBrightness.cpp
    Src/Keyboard.cpp
    Src/PulseCounterSource.cpp
    Src/SdCardRecorder.cpp
    Src/UartRecorder.cpp
    Src/UartSource.cpp
    Src/WiFiRecorder.cpp
)

target_include_directories(Device PRIVATE
    ../Library/u8g2/cppsrc
)