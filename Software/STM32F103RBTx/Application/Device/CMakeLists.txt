cmake_minimum_required(VERSION 3.28)
project(Device LANGUAGES CXX)

# Enable C++23 and module support
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable experimental C++ module support
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

# Device library
add_library(Device STATIC)

target_link_libraries(Device PRIVATE
    Driver
   # PRIVATE DriverInterface
)

# Add module interface files
target_sources(Device
    PUBLIC
        FILE_SET device_public 
        TYPE CXX_MODULES 
        FILES
            Modules/Device.cppm
            Modules/Display.cppm
            Modules/DisplayPixelColor.cppm
            Modules/Keyboard.cppm
            Modules/MeasurementDeviceId.cppm
            Modules/DisplayBrightness.cppm
            Modules/PulseCounterSource.cppm
            Modules/SourceVariant.cppm
            Modules/UartSource.cppm
            Modules/WiFiRecorder.cppm
            Modules/UartRecorder.cppm
            Modules/SdCardRecorder.cppm
            Modules/RecorderVariant.cppm
            Modules/MeasurementSource.cppm
            Modules/MeasurementType.cppm
            Modules/MeasurementRecorder.cppm
            Modules/DeviceComponent.cppm
            Modules/KeyActionState.cppm
            Modules/CobsEncoder.cppm
            Modules/Crc32.cppm
            Modules/WiFiSerializer.cppm
    #PRIVATE
    #    FILE_SET device_private 
    #    TYPE CXX_MODULES 
    #    FILES  

)

# Add regular source files
target_sources(Device PRIVATE
    Src/DisplayBrightness.cpp
    Src/Display.cpp
    Src/Keyboard.cpp
    Src/PulseCounterSource.cpp
    Src/SdCardRecorder.cpp
    Src/UartRecorder.cpp
    Src/UartSource.cpp
    Src/WiFiRecorder.cpp
)

target_include_directories(Device PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/cppsrc
    ${CMAKE_CURRENT_SOURCE_DIR}/../Library/u8g2/csrc
)



