/**
 * @file IPlatformFactory.hpp
 * @brief Declaration of the IPlatformFactory interface for creating platform-specific drivers.
 */

#ifndef IPlatformFactory_h
#define IPlatformFactory_h

#include "Driver/Interface/IAmbientLightSensorDriver.hpp"
#include "Driver/Interface/IDisplayBrightnessDriver.hpp"
#include "Driver/Interface/IDisplayDriver.hpp"
#include "Driver/Interface/IKeyboardDriver.hpp"
#include "Driver/Interface/ISdCardDriver.hpp"
#include "Driver/Interface/UartId.hpp"
#include "Driver/Interface/IUartDriver.hpp"
#include "Driver/Interface/PulseCounterId.hpp"
#include "Driver/Interface/IPulseCounterDriver.hpp"

namespace BusinessLogic
{
    /**
     * @class IPlatformFactory
     * @brief Interface for creating platform-specific driver instances.
     */
    class IPlatformFactory
    {
    public:
        IPlatformFactory() = default;

        IPlatformFactory(const IPlatformFactory &) = delete;
        IPlatformFactory &operator=(const IPlatformFactory &) = delete;
        IPlatformFactory(IPlatformFactory &&) = delete;
        IPlatformFactory &operator=(IPlatformFactory &&) = delete;

        virtual ~IPlatformFactory() = default;

        [[nodiscard]] virtual Driver::IAmbientLightSensorDriver &getAmbientLightSensorDriver() = 0;
        [[nodiscard]] virtual Driver::IDisplayBrightnessDriver &getDisplayBrightnessDriver() = 0;
        [[nodiscard]] virtual Driver::IDisplayDriver &getDisplayDriver() = 0;
        [[nodiscard]] virtual Driver::IKeyboardDriver &getKeyboardDriver() = 0;
        [[nodiscard]] virtual Driver::IUartDriver &getUartDriver(Driver::UartId deviceId) = 0;
        [[nodiscard]] virtual Driver::ISdCardDriver &getSdCardDriver() = 0;
        [[nodiscard]] virtual Driver::IPulseCounterDriver &getPulseCounterDriver(Driver::PulseCounterId deviceId) = 0;
    };
}

#endif // IPlatformFactory_h
