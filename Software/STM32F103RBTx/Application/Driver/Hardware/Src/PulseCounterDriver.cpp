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
    static constexpr std::uint8_t PULSE_COUNTER_COUNT =
        std::to_underlying(Driver::PulseCounterId::LastNotUsed);

    // modified in interruption, shared by all instances of PulseCounterDriver
    // Each counter uses one and only one element in array.
    alignas(std::uint32_t) std::array<Driver::PulseCount,
                                      PULSE_COUNTER_COUNT> rawPulseCounters = {0};
}

// We are the client of PulseCounterId; verify enum values because
// the program will fail at runtime if the values are incorrect.
static_assert(std::to_underlying(Driver::PulseCounterId::bncA) == 0U,
              "PulseCounterId::bncA must be 0");

static_assert(std::to_underlying(Driver::PulseCounterId::bncB) == 1U,
              "PulseCounterId::bncB must be 1");

static_assert(std::to_underlying(Driver::PulseCounterId::bncC) == 2U,
              "PulseCounterId::bncC must be 2");

static_assert(std::to_underlying(Driver::PulseCounterId::bncD) == 3U,
              "PulseCounterId::bncD must be 3");

static_assert(std::to_underlying(Driver::PulseCounterId::LastNotUsed) == 4U,
              "PulseCounterId::LastNotUsed must be 4 (count of valid BNC connectors)");

// Global HAL EXTI callback for the entire MCU.
// CubeMX provides a weak default; this definition overrides it and therefore becomes the
// central dispatch point for all GPIO EXTI lines in the system.
// It is implemented here because EXTI events are owned by this driver in this project;
// if more EXTI users are added later, consider moving this to a dedicated IRQ dispatcher.
extern "C" void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    static constexpr std::uint8_t COUNTER_1 = std::to_underlying(Driver::PulseCounterId::bncA);
    static constexpr std::uint8_t COUNTER_2 = std::to_underlying(Driver::PulseCounterId::bncB);
    static constexpr std::uint8_t COUNTER_3 = std::to_underlying(Driver::PulseCounterId::bncC);
    static constexpr std::uint8_t COUNTER_4 = std::to_underlying(Driver::PulseCounterId::bncD);

    switch (GPIO_Pin)
    {
    case GPIO_PIN_6:
        ++rawPulseCounters[COUNTER_1];
        break;
    case GPIO_PIN_7:
        ++rawPulseCounters[COUNTER_2];
        break;
    case GPIO_PIN_8:
        ++rawPulseCounters[COUNTER_3];
        break;
    case GPIO_PIN_9:
        ++rawPulseCounters[COUNTER_4];
        break;
    default:
        break;
    }
}

namespace Driver
{

    PulseCounterDriver::PulseCounterDriver(PulseCounterId deviceId) noexcept
        : counter(rawPulseCounters[std::to_underlying(deviceId)])
    {
    }

    auto PulseCounterDriver::onStart() noexcept -> bool
    {
        clear();
        return true;
    }

    auto PulseCounterDriver::read() const noexcept -> PulseCount
    {
        return counter;
    }

    auto PulseCounterDriver::clear() noexcept -> void
    {
        counter = 0U;
    }

} // namespace Driver