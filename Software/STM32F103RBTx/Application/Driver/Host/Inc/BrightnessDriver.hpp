#ifndef BrightnessDriver_H_
#define BrightnessDriver_H_

#include "Driver/Interface/BrightnessDriverConcept.hpp"
#include "Driver/Interface/DriverComponent.hpp"

#include <stdint.h>

namespace Driver
{

    class BrightnessDriver : public DriverComponent
    {
    public:
        /**
         * @brief Default constructor for BrightnessDriver.
         *
         */
        BrightnessDriver() = default;

        /**
         * @brief Default destructor for BrightnessDriver.
         */
        ~BrightnessDriver() = default;

        // Delete copy constructor and assignment operator

        // Non-copyable and non-movable
        BrightnessDriver(const BrightnessDriver &) = delete;
        BrightnessDriver(BrightnessDriver &&) = delete;
        BrightnessDriver &operator=(const BrightnessDriver &) = delete;
        BrightnessDriver &operator=(BrightnessDriver &&) = delete;

        /**
         * @brief Sets the brightness of the display.
         *
         * Adjusts the PWM duty cycle to set the desired brightness level.
         *
         * @param brightness Brightness level as a percentage (0-100).
         * @return True if the brightness is set successfully, false otherwise.
         */
        bool setBrightness(std::uint8_t brightness) noexcept;

        [[nodiscard]] bool onInit() { return true; }
        [[nodiscard]] bool onStart() { return true; }
        [[nodiscard]] bool onStop() { return true; }
    };

    static_assert(Driver::Concepts::BrightnessDriverConcept<BrightnessDriver>,
                  "BrightnessDriver must satisfy concept requirements");
}

#endif // BrightnessDriver_H_
