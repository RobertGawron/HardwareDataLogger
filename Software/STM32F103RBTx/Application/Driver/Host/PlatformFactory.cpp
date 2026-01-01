#include "PlatformFactory.hpp"

#include "Driver/Interface/UartId.hpp"
#include "Driver/Interface/PulseCounterId.hpp"

#include "Driver/Interface/IUartDriver.hpp"
#include "Driver/Interface/ISdCardDriver.hpp"
#include "Driver/Interface/IPulseCounterDriver.hpp"

#include "Driver/Interface/IKeyboardDriver.hpp"
#include "Driver/Interface/IDisplayDriver.hpp"
#include "Driver/Interface/IDisplayBrightnessDriver.hpp"
#include "Driver/Interface/IAmbientLightSensorDriver.hpp"

#include "UartDriverStub.hpp"
#include "PulseCounterDriverStub.hpp"

#include <cstddef>

namespace BusinessLogic
{
    PlatformFactory::PlatformFactory()
        : uartDrivers{Driver::UartDriverStub(Driver::UartId::MEASUREMENT_RECEIVER),
                      Driver::UartDriverStub(Driver::UartId::TRANSMIT_VIA_WIFI),
                      Driver::UartDriverStub(Driver::UartId::TRANSMIT_VIA_USB)},
          pulseCounterDrivers{Driver::PulseCounterDriverStub(Driver::PulseCounterId::bncA),
                              Driver::PulseCounterDriverStub(Driver::PulseCounterId::bncB),
                              Driver::PulseCounterDriverStub(Driver::PulseCounterId::bncC),
                              Driver::PulseCounterDriverStub(Driver::PulseCounterId::bncD)}
    {
    }

    Driver::IAmbientLightSensorDriver &PlatformFactory::getAmbientLightSensorDriver()
    {
        return ambientLightSensor;
    }

    Driver::IDisplayBrightnessDriver &PlatformFactory::getDisplayBrightnessDriver()
    {
        return brightness;
    }

    Driver::IDisplayDriver &PlatformFactory::getDisplayDriver()
    {
        return display;
    }

    Driver::IKeyboardDriver &PlatformFactory::getKeyboardDriver()
    {
        return keyboard;
    }

    Driver::IUartDriver &PlatformFactory::getUartDriver(const Driver::UartId deviceId)
    {
        const std::size_t index = static_cast<std::size_t>(deviceId);
        return uartDrivers.at(index);
    }

    Driver::ISdCardDriver &PlatformFactory::getSdCardDriver()
    {
        return sdCard;
    }

    Driver::IPulseCounterDriver &PlatformFactory::getPulseCounterDriver(const Driver::PulseCounterId deviceId)
    {
        const std::size_t index = static_cast<std::size_t>(deviceId);
        return pulseCounterDrivers.at(index);
    }
}
