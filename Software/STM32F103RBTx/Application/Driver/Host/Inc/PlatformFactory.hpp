// Driver/Interface/IPlatformDrivers.hpp
#pragma once

#include "LightSensorDriver.hpp"
#include "BrightnessDriver.hpp"
#include "DisplayDriver.hpp"
#include "KeyboardDriver.hpp"
#include "UartDriver.hpp"
#include "SdCardDriver.hpp"
#include "PulseCounterDriver.hpp"

// #include "Driver/Interface/Board.hpp"

namespace Driver
{
    /**
     * @brief Bundle of all platform driver interface references
     *
     * This struct only contains references to driver interfaces,
     * hiding all concrete implementation details from business logic.
     */
    struct PlatformFactory
    {
        LightSensorDriver &LightSensor;
        BrightnessDriver &displayBrightness;
        DisplayDriver &display;
        KeyboardDriver &keyboard;
        UartDriver &wifiUart;
        UartDriver &usbUart;
        UartDriver &measurementUart;
        SdCardDriver &sdCard;
        PulseCounterDriver &counter1;
        PulseCounterDriver &counter2;
        PulseCounterDriver &counter3;
        PulseCounterDriver &counter4;
    };

} // namespace Driver
