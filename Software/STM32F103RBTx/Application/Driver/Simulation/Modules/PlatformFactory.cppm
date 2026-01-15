export module Driver.PlatformFactory;

import Driver.LightSensorDriver;
import Driver.BrightnessDriver;
import Driver.DisplayDriver;
import Driver.KeyboardDriver;
import Driver.UartDriver;
import Driver.SdCardDriver;
import Driver.PulseCounterDriver;

export namespace Driver
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