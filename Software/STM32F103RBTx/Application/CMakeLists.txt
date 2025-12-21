cmake_minimum_required(VERSION 3.22)
project(ApplicationLib)

# Set C++ standard to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Interface library for common includes
add_library(ApplicationInterfaces INTERFACE)
target_include_directories(ApplicationInterfaces INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Common
    ${CMAKE_CURRENT_SOURCE_DIR}/Library/u8g2/cppsrc
    ${CMAKE_CURRENT_SOURCE_DIR}/Library/u8g2/csrc
)

# Add u8g2 subdirectory
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/Library/u8g2
    ${CMAKE_BINARY_DIR}/u8g2_build
)

# BusinessLogic library sources
set(BUSINESS_LOGIC_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/BusinessLogic/Src/ApplicationBuilder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BusinessLogic/Src/HmiFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BusinessLogic/Src/HmiMeasurementModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BusinessLogic/Src/HmiMui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BusinessLogic/Src/HmiMuiHandlers.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BusinessLogic/Src/MeasurementCoordinator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BusinessLogic/Src/MeasurementDataStore.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BusinessLogic/Src/MeasurementSourcesFactory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BusinessLogic/Src/MeasurementStoresFactory.cpp
)

# Device library sources
set(DEVICE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/Src/CacheMeasurementRecorder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/Src/DisplayBrightnessRegulator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/Src/Display.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/Src/Keyboard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/Src/PulseCounterMeasurementSource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/Src/SdCardMeasurementRecorder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/Src/UartMeasurementRecorder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/Src/UartMeasurementSource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/Src/WiFiMeasurementRecorder.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/Src/WiFiMeasurementSerializer.cpp
)

# Driver library sources
set(DRIVER_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/Src/AmbientLightSensorDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/Src/DisplayPixelColor.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/Src/DriverState.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/Src/KeyboardFourPushButtonsDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/Src/PulseCounterDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/Src/SdCardDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/Src/St7735DisplayBrightnessDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/Src/St7735DisplayDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Driver/Src/UartDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/Src/CobsEncoder.cpp  
    ${CMAKE_CURRENT_SOURCE_DIR}/Device/Src/Crc32.cpp
    # From outside of Cube MX, its CMake doesnt know it
    ${CMAKE_CURRENT_SOURCE_DIR}/../FATFS/Target/user_diskio_spi.c
)

# BusinessLogic library
add_library(BusinessLogic STATIC)
target_sources(BusinessLogic PRIVATE ${BUSINESS_LOGIC_SOURCES})
target_link_libraries(BusinessLogic PRIVATE 
    u8g2 
    ApplicationInterfaces
)

# Device library
add_library(Device STATIC)
target_sources(Device PRIVATE ${DEVICE_SOURCES})
target_link_libraries(Device PRIVATE 
    u8g2 
    ApplicationInterfaces
)

# Driver library
add_library(Driver STATIC)
target_sources(Driver PRIVATE ${DRIVER_SOURCES})

if(USE_X86_HEADERS)
    target_include_directories(Driver PUBLIC
        ${CMAKE_SOURCE_DIR}/Test/Unit/System
    )
else()
    target_include_directories(Driver PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../Drivers/STM32F1xx_HAL_Driver/Inc
        ${CMAKE_CURRENT_SOURCE_DIR}/../Drivers/CMSIS/Device/ST/STM32F1xx/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/../Drivers/CMSIS/Include
        ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Inc
        ${CMAKE_CURRENT_SOURCE_DIR}/Library/stm32-st7735/
        # Not eassy this SD Card lib
        ${CMAKE_CURRENT_SOURCE_DIR}/../Middlewares/Third_Party/FatFs/src
        ${CMAKE_CURRENT_SOURCE_DIR}/../FATFS/Target
    )
endif()

# Link common interfaces to Driver
target_link_libraries(Driver PUBLIC ApplicationInterfaces)

# Debug options using generator expressions
foreach(lib IN ITEMS BusinessLogic Device Driver u8g2)
    if(TARGET ${lib})
        target_compile_options(${lib} PRIVATE 
            $<$<CONFIG:Debug>:-g3>
        )
    endif()
endforeach()