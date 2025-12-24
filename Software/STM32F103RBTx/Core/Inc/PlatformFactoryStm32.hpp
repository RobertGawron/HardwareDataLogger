#ifndef PlatformFactoryStm32_h
#define PlatformFactoryStm32_h

#include "BusinessLogic/Interface/IPlatformFactory.hpp"
namespace BusinessLogic
{
    class PlatformFactoryStm32 : public IPlatformFactory
    {
    public:
        explicit PlatformFactoryStm32() = default;
        ~PlatformFactoryStm32() override = default;

        PlatformFactoryStm32(const PlatformFactoryStm32 &) = delete;
        PlatformFactoryStm32 &operator=(const PlatformFactoryStm32 &) = delete;

        Driver::IAmbientLightSensorDriver &createAmbientLightSensorDriver() override;
        Driver::IDisplayBrightnessDriver &createDisplayBrightnessDriver() override;
        Driver::IDisplayDriver &createDisplayDriver() override;
        Driver::IKeyboardDriver &createKeyboardDriver() override;
        Driver::IUartDriver &createUartDriver(const Driver::UartIdentifier id) override;
        Driver::ISdCardDriver &createSdCardDriver() override;
        Driver::IPulseCounterDriver &createPulseCounterDriver(const Driver::PulseCounterIdentifier id) override;
    };
}

#endif
