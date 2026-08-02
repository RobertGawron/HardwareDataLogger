add_library(Device OBJECT)

target_link_libraries(Device PUBLIC # TODO PUBLIC for unit tests, but should be PRIVATE
    Driver
)

target_sources(Device
  PUBLIC
    FILE_SET CXX_MODULES
    BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/Modules"
    FILES
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
