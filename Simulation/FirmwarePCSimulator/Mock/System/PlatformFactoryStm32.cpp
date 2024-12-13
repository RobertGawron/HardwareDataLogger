#include "PlatformFactoryStm32.hpp"

#include "AmbientLightSensorDriverStub.hpp"
#include "BrightnessDriverStub.hpp"
#include "KeyboardDriverStub.hpp"
#include "UartIdentifier.hpp"
#include "UartDriverStub.hpp"
#include "SdCardDriverStub.hpp"
#include "PulseCounterIdentifier.hpp"
#include "PulseCounterDriverStub.hpp"
#include "St7735DisplayDriverStub.hpp"

Driver::St7735DisplayDriverStub st7735DisplayDriverStub;
Driver::KeyboardDriverStub keyboardDriverStub;

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
        return st7735DisplayDriverStub;
    }

    Driver::IKeyboardDriver &PlatformFactoryStm32::createKeyboardDriver()
    {
        return keyboardDriverStub;
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
