cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP ON)

add_library(DriverInterface STATIC)

# Module interface files
target_sources(DriverInterface
    PUBLIC FILE_SET CXX_MODULES FILES
        Interface/BrightnessDriverConcept.cppm
        Interface/DisplayDriverConcept.cppm
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
)


add_subdirectory(Hardware)