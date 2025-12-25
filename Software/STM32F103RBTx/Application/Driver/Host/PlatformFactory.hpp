#ifndef PlatformFactoryStm32Stub_hpp
#define PlatformFactoryStm32Stub_hpp

#include "BusinessLogic/Interface/IPlatformFactory.hpp"

#include "Driver/Host/Inc/AmbientLightSensorDriverStub.hpp"
#include "Driver/Host/Inc/BrightnessDriverStub.hpp"
#include "Driver/Host/Inc/St7735DisplayDriverStub.hpp"
#include "Driver/Host/Inc/KeyboardDriverStub.hpp"
#include "Driver/Host/Inc/UartDriverStub.hpp"
#include "Driver/Host/Inc/SdCardDriverStub.hpp"
#include "Driver/Host/Inc/PulseCounterDriverStub.hpp"

namespace BusinessLogic
{
    class PlatformFactory : public IPlatformFactory
    {
    public:
        PlatformFactory();
        ~PlatformFactory() override = default;

        Driver::IAmbientLightSensorDriver &getAmbientLightSensorDriver() override;
        Driver::IDisplayBrightnessDriver &getDisplayBrightnessDriver() override;
        Driver::IDisplayDriver &getDisplayDriver() override;
        Driver::IKeyboardDriver &getKeyboardDriver() override;
        Driver::IUartDriver &getUartDriver(Driver::UartId id) override;
        Driver::ISdCardDriver &getSdCardDriver() override;
        Driver::IPulseCounterDriver &getPulseCounterDriver(Driver::PulseCounterId id) override;

    private:
        static constexpr std::size_t UART_COUNT = 3U;
        static constexpr std::size_t PULSE_COUNTER_COUNT = 4U;

        Driver::AmbientLightSensorDriverStub ambientLightSensor;
        Driver::BrightnessDriverStub brightness;
        Driver::St7735DisplayDriverStub display;
        Driver::KeyboardDriverStub keyboard;
        std::array<Driver::UartDriverStub, UART_COUNT> uartDrivers;
        Driver::SdCardDriverStub sdCard;
        std::array<Driver::PulseCounterDriverStub, PULSE_COUNTER_COUNT> pulseCounterDrivers;
    };
}

#endif
