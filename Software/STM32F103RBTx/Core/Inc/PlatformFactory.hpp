#ifndef PlatformFactory_h
#define PlatformFactory_h

#include "BusinessLogic/Interface/IPlatformFactory.hpp"

namespace BusinessLogic
{
    class PlatformFactory final : public IPlatformFactory
    {
    public:
        PlatformFactory() = default;
        ~PlatformFactory() override = default;

        PlatformFactory(const PlatformFactory &) = delete;
        PlatformFactory &operator=(const PlatformFactory &) = delete;
        PlatformFactory(PlatformFactory &&) = delete;
        PlatformFactory &operator=(PlatformFactory &&) = delete;

        [[nodiscard]] Driver::IAmbientLightSensorDriver &getAmbientLightSensorDriver() override;
        [[nodiscard]] Driver::IDisplayBrightnessDriver &getDisplayBrightnessDriver() override;
        [[nodiscard]] Driver::IDisplayDriver &getDisplayDriver() override;
        [[nodiscard]] Driver::IKeyboardDriver &getKeyboardDriver() override;
        [[nodiscard]] Driver::IUartDriver &getUartDriver(Driver::UartId deviceId) override;
        [[nodiscard]] Driver::ISdCardDriver &getSdCardDriver() override;
        [[nodiscard]] Driver::IPulseCounterDriver &getPulseCounterDriver(Driver::PulseCounterId deviceId) override;
    };
}

#endif // PlatformFactory_h