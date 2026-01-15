module;

#include "stm32f1xx_hal.h"

#include <cstdint>

export module Driver.BrightnessDriver;

import Driver.DriverComponent;
import Driver.BrightnessDriverConcept;

export namespace Driver
{
    /**
     * @class BrightnessDriver
     * @brief Controls LCD backlight brightness via PWM at 5kHz
     */
    class BrightnessDriver final : public DriverComponent
    {
    public:
        explicit BrightnessDriver(TIM_HandleTypeDef &htim) noexcept;

        ~BrightnessDriver() = default;

        BrightnessDriver() = delete;
        BrightnessDriver(const BrightnessDriver &) = delete;
        BrightnessDriver &operator=(const BrightnessDriver &) = delete;
        BrightnessDriver(BrightnessDriver &&) = delete;
        BrightnessDriver &operator=(BrightnessDriver &&) = delete;

        [[nodiscard]] bool setBrightness(std::uint8_t brightness) noexcept;

        [[nodiscard]] bool onInit();
        [[nodiscard]] bool onStart();
        [[nodiscard]] bool onStop();

    private:
        // Hardware configuration constants
        static constexpr std::uint32_t TIMER_CLOCK_FREQ = 24'000'000U; // 24 MHz
        static constexpr std::uint32_t PWM_FREQ = 5'000U;              // 5 kHz
        static constexpr std::uint32_t TIMER_PERIOD = (TIMER_CLOCK_FREQ / PWM_FREQ) - 1U;
        static constexpr std::uint8_t MAX_BRIGHTNESS = 100U;
        static constexpr std::uint8_t INITIAL_BRIGHTNESS = 0U;

        [[nodiscard]] bool initializeTimer() noexcept;
        [[nodiscard]] bool configurePwmChannel() noexcept;
        [[nodiscard]] bool startPwmWithInitialBrightness() noexcept;
        [[nodiscard]] bool stopPwm() noexcept;

        [[nodiscard]] static constexpr std::uint32_t calculatePulseFromBrightness(
            std::uint8_t brightness) noexcept
        {
            return (static_cast<std::uint32_t>(brightness) * TIMER_PERIOD) / MAX_BRIGHTNESS;
        }

        TIM_HandleTypeDef &htim;
    };

    static_assert(Driver::Concepts::BrightnessDriverConcept<BrightnessDriver>,
                  "BrightnessDriver must satisfy concept requirements");

} // namespace Driver