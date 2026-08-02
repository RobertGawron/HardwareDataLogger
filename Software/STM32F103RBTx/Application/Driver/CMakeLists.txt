add_library(DriverInterface OBJECT)

target_sources(DriverInterface
    PUBLIC FILE_SET CXX_MODULES FILES
        Interface/CycleBudget.cppm
        Interface/CycleCpu.cppm
        Interface/CoreClockConfig.cppm

        Interface/BrightnessDriverConcept.cppm
        Interface/DisplayDriverConcept.cppm
        Interface/DriverComponent.cppm
        Interface/FileOpenMode.cppm
        Interface/KeyboardDriverConcept.cppm
        Interface/KeyId.cppm
        Interface/KeyState.cppm
        Interface/LightSensorDriverConcept.cppm
        Interface/PulseCounterDriverConcept.cppm
        Interface/PulseCounterId.cppm
        Interface/PulseCount.cppm
        Interface/SdCardDriverConcept.cppm
        Interface/SdCardStatus.cppm
        Interface/UartDriverConcept.cppm
        Interface/UartStatus.cppm
)

if(BUILD_IS_FOR_HARDWARE)
    add_subdirectory(Hardware)
else()
    add_subdirectory(Simulation)
endif()
