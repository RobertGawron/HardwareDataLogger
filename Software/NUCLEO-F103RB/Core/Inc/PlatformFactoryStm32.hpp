#ifndef PlatformFactoryStm32_h
#define PlatformFactoryStm32_h

#include "IPlatformFactory.hpp"

namespace BusinessLogic
{
    class PlatformFactoryStm32 : public IPlatformFactory
    {
    public:
        explicit PlatformFactoryStm32() = default;
        virtual ~PlatformFactoryStm32() = default;

        PlatformFactoryStm32(const PlatformFactoryStm32 &) = delete;
        PlatformFactoryStm32 &operator=(const PlatformFactoryStm32 &) = delete;

        virtual Driver::IAmbientLightSensorDriver &createAmbientLightSensorDriver() override;
        virtual Driver::IDisplayBrightnessDriver &createDisplayBrightnessDriver() override;
        virtual Driver::IDisplayDriver &createDisplayDriver() override;
        virtual Driver::IKeyboardDriver &createKeyboardDriver() override;
        virtual Driver::IUartDriver &createUartDriver(const Driver::UartIdentifier id) override;
        virtual Driver::ISdCardDriver &createSdCardDriver() override;
        virtual Driver::IPulseCounterDriver &createPulseCounterDriver(const Driver::PulseCounterIdentifier id) override;
    };
}

#endif
