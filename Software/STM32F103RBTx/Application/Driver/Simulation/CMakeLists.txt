cmake_minimum_required(VERSION 3.31)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

add_library(Driver STATIC)

# Link dependencies
target_link_libraries(Driver 
    PUBLIC DriverInterface
)

target_include_directories(Driver PRIVATE
    Inc
)

target_sources(Driver
    PUBLIC FILE_SET CXX_MODULES FILES
        Modules/BrightnessDriver.cppm
        Modules/DisplayDriver.cppm
        Modules/Driver.cppm
        Modules/KeyboardDriver.cppm
        Modules/LightSensorDriver.cppm
        Modules/PlatformFactory.cppm
        Modules/PulseCounterDriver.cppm
        Modules/SdCardDriver.cppm
        Modules/UartDriver.cppm
        Modules/UartId.cppm
)

target_sources(Driver PRIVATE
    Src/EventHandlers.cpp
   # LibWrapper.cppm

    Src/BrightnessDriver.cpp
    Src/DisplayDriver.cpp
    Src/KeyboardDriver.cpp
    Src/LightSensorDriver.cpp
    Src/PulseCounterDriver.cpp
    Src/SdCardDriver.cpp
    Src/UartDriver.cpp
)

