module;

#include <array>
#include <cstdint>
#include <cstddef>
#include <functional>
#include <utility>

#include "stm32f1xx_hal_gpio.h"

module Driver.PulseCounterDriver;

import Driver.PulseCounterId;

namespace
{
    static constexpr std::uint8_t PULSE_COUNTER_AMOUNT = 4U;

    // modified in interruption, shared by all instances of PulseCounterDriver
    std::array<Driver::PulseCounterMeasurementSize, PULSE_COUNTER_AMOUNT>
        rawPulseCounters = {0};
}

// Global HAL EXTI callback for the entire MCU.
// CubeMX provides a weak default; this definition overrides it and therefore becomes the
// central dispatch point for all GPIO EXTI lines in the system.
// It is implemented here because EXTI events are owned by this driver in this project;
// if more EXTI users are added later, consider moving this to a dedicated IRQ dispatcher.
extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    switch (GPIO_Pin)
    {
    case GPIO_PIN_6:
        ++rawPulseCounters[0];
        break;
    case GPIO_PIN_7:
        ++rawPulseCounters[1];
        break;
    case GPIO_PIN_8:
        ++rawPulseCounters[2];
        break;
    case GPIO_PIN_9:
        ++rawPulseCounters[3];
        break;
    default:
        break;
    }
}

/*
namespace
{
    using CounterArray = std::array<
        Driver::PulseCounterMeasurementSize,
        Driver::PulseCounterDriver::PULSE_COUNTER_AMOUNT>;

    constinit CounterArray pulseCounters{};
}

extern "C"
{
    void incrementPulseCounter(std::uint8_t counterId) noexcept
    {
        if (counterId < pulseCounters.size()) [[likely]]
        {
            ++pulseCounters[counterId];
        }
    }
}
*/
namespace Driver
{

    PulseCounterDriver::PulseCounterDriver(PulseCounterId deviceIdentifier) noexcept
        : value(rawPulseCounters[std::to_underlying(deviceIdentifier)])
    {
    }
    /*
        auto PulseCounterDriver::onInit() noexcept -> bool
        {
            // pulseCounters.fill(0U);
            return true;
        }*/

    auto PulseCounterDriver::onStart() noexcept -> bool
    {
        // rawPulseCounters.fill(0U);
        clearMeasurement();
        return true;
    }

    auto PulseCounterDriver::onStop() noexcept -> bool
    {
        clearMeasurement();
        return true;
    }

    auto PulseCounterDriver::getMeasurement() noexcept -> PulseCounterMeasurementSize
    {
        return value;
    }

    auto PulseCounterDriver::clearMeasurement() noexcept -> void
    {
        value = 0U;
    }

} // namespace Driver