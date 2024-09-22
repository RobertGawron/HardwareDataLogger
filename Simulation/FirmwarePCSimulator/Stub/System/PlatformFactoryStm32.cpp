#include "PlatformFactoryStm32.hpp"

#include "AmbientLightSensorDriverStub.hpp"
#include "BrightnessDriverStub.hpp"
#include "DisplayDriverStub.hpp"
#include "KeyboardDriverStub.hpp"
#include "UartIdentifier.hpp"
#include "UartDriverStub.hpp"
#include "SdCardDriverStub.hpp"
#include "PulseCounterIdentifier.hpp"
#include "PulseCounterDriverStub.hpp"

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"

// I'm not sure if it should be here.
// extern UART_HandleTypeDef huart3;

// I's not really nice to do it this way (global objects accessible via "extern" but this is just for simulation).
Driver::St7735DisplayDriver displayDriver{};

namespace BusinessLogic
{

    Driver::IAmbientLightSensorDriver &PlatformFactoryStm32::createAmbientLightSensorDriver()
    {
        static Driver::AmbientLightSensorDriverStub driver;
        return driver;
    }

    Driver::IDisplayBrightnessDriver &PlatformFactoryStm32::createDisplayBrightnessDriver()
    {
        static Driver::BrightnessDriverStub driver;
        return driver;
    }

    Driver::IDisplayDriver &PlatformFactoryStm32::createDisplayDriver()
    {
        return displayDriver;
    }

    Driver::IKeyboardDriver &PlatformFactoryStm32::createKeyboardDriver()
    {
        static Driver::KeyboardDriverStub driver;
        return driver;
    }

    Driver::IUartDriver &PlatformFactoryStm32::createUartDriver(const Driver::UartIdentifier id)
    {
        static Driver::UartDriverStub driver;
        return driver;
    }

    Driver::ISdCardDriver &PlatformFactoryStm32::createSdCardDriver()
    {
        static Driver::SdCardDriverStub driver;
        return driver;
    }

    Driver::IPulseCounterDriver &PlatformFactoryStm32::createPulseCounterDriver(const Driver::PulseCounterIdentifier id)
    {
        static Driver::PulseCounterDriverStub driver;
        return driver;
    }

}
