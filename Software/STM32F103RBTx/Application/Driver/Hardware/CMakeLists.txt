
add_library(Driver OBJECT)

target_link_libraries(Driver 
    PUBLIC DriverInterface
)

target_sources(Driver
    PUBLIC FILE_SET CXX_MODULES FILES 
        Modules/CycleClock.cppm
        
        Modules/BrightnessDriver.cppm
        Modules/DisplayDriver.cppm
        Modules/Driver.cppm
        Modules/KeyboardDriver.cppm
        Modules/LightSensorDriver.cppm
        Modules/PlatformFactory.cppm
        Modules/PulseCounterDriver.cppm
        Modules/SdCardDriver.cppm
        Modules/UartDriver.cppm
)

target_sources(Driver PRIVATE
    Src/BrightnessDriver.cpp
    Src/DisplayDriver.cpp
    Src/KeyboardDriver.cpp
    Src/LightSensorDriver.cpp
    Src/PulseCounterDriver.cpp
    Src/SdCardDriver.cpp
    Src/UartDriver.cpp
    ../../../FATFS/Target/user_diskio_spi.c
)

target_include_directories(Driver PRIVATE
    ../../../Drivers/STM32F1xx_HAL_Driver/Inc
    ../../../Drivers/CMSIS/Driver/ST/STM32F1xx/Include
    ../../../Drivers/CMSIS/Include
    ../../../Core/Inc
    ../../Library/stm32-st7735
    ../../../Middlewares/Third_Party/FatFs/src
    ../../../FATFS/Target
    ../../../Drivers/CMSIS/Device/ST/STM32F1xx/Include
)