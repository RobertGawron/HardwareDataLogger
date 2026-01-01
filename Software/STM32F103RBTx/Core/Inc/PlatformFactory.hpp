#ifndef PlatformFactory_h
#define PlatformFactory_h

#include "BusinessLogic/Interface/IPlatformFactory.hpp"

namespace BusinessLogic
{
    class PlatformFactory : public IPlatformFactory
    {
    public:
        explicit PlatformFactory() = default;
        ~PlatformFactory() override = default;

        PlatformFactory(const PlatformFactory &) = delete;
        PlatformFactory &operator=(const PlatformFactory &) = delete;

        Driver::IAmbientLightSensorDriver &getAmbientLightSensorDriver() override;
        Driver::IDisplayBrightnessDriver &getDisplayBrightnessDriver() override;
        Driver::IDisplayDriver &getDisplayDriver() override;
        Driver::IKeyboardDriver &getKeyboardDriver() override;
        Driver::IUartDriver &getUartDriver(const Driver::UartId deviceId) override;
        Driver::ISdCardDriver &getSdCardDriver() override;
        Driver::IPulseCounterDriver &getPulseCounterDriver(Driver::PulseCounterId deviceId) override;
    };
}

#endif
