add_library(Driver STATIC)

target_link_libraries(Driver 
    PUBLIC DriverInterface
)

target_sources(Driver
    PUBLIC FILE_SET CXX_MODULES FILES
        Modules/EventHandlers.cppm

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
        Modules/CycleClock.cppm
)

target_sources(Driver PRIVATE
    Src/EventHandlers.cpp

    Src/BrightnessDriver.cpp
    Src/DisplayDriver.cpp
    Src/KeyboardDriver.cpp
    Src/LightSensorDriver.cpp
    Src/PulseCounterDriver.cpp
    Src/SdCardDriver.cpp
    Src/UartDriver.cpp
)
