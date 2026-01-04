cmake_minimum_required(VERSION 3.28)
project(Driver LANGUAGES CXX)

# Enable C++23 and module support
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable experimental C++ module support
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

# DriverInterface library
add_library(DriverInterface STATIC)

# for now
add_subdirectory(Hardware)

# Add module interface files
target_sources(DriverInterface
    PUBLIC
        FILE_SET driver_interface_public
        TYPE CXX_MODULES 
        FILES
           # Interface/PlatformFactory.cppm
            Interface/BrightnessDriverConcept.cppm
            Interface/DisplayDriverConcept.cppm
            #Interface/DisplayPixelColor.cppm
            Interface/DriverComponent.cppm
            Interface/FileOpenMode.cppm
            Interface/KeyboardDriverConcept.cppm
            Interface/KeyIdentifier.cppm
            Interface/KeyState.cppm
            Interface/LightSensorDriverConcept.cppm
            Interface/PulseCounterDriverConcept.cppm
            Interface/PulseCounterId.cppm
            Interface/PulseCounterMeasurementSize.cppm
            Interface/SdCardDriverConcept.cppm
            Interface/SdCardStatus.cppm
            Interface/UartDriverConcept.cppm
            Interface/UartId.cppm
            Interface/UartStatus.cppm
    #PRIVATE
    #    FILE_SET driver_private 
    #    TYPE CXX_MODULES 
    #    FILES  
)
