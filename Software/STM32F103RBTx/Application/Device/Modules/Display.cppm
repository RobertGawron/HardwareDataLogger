module;

#include <cstdint>

#include "U8g2lib.h"
#include "u8g2.h"

export module Device.Display;

import Device.DeviceComponent;
import Device.DisplayPixelColor;

import Driver.DisplayDriver;

export namespace Device
{
    /**
     * @class Display
     * @brief Adapter class that implements the `IDisplay` interface using a provided display driver.
     *
     * The `Display` class bridges the `IDisplay` interface and a specific `DisplayDriver` implementation.
     * It manages the initialization and configuration of the display and provides utility functions
     * for working with the underlying display driver.
     */
    class Display final : public U8G2, public DeviceComponent
    {
    public:
        /**
         * @brief Constructs a `Display` instance with a reference to a display driver.
         *
         * @param displayDriver Reference to a `Driver::DisplayDriver` implementation.
         */

        explicit constexpr Display(Driver::DisplayDriver &displayDriver) noexcept
            : displayDriver{displayDriver}
        {
        }

        ~Display() = default;

        // Non-copyable and non-movable
        Display() = delete;
        Display(const Display &) = delete;
        Display(Display &&) = delete;
        Display &operator=(const Display &) = delete;
        Display &operator=(Display &&) = delete;

        [[nodiscard]] auto onInit() noexcept -> bool;

        [[nodiscard]] auto onStart() noexcept -> bool;
        [[nodiscard]] auto onStop() noexcept -> bool;

    private:
        Driver::DisplayDriver &displayDriver;
    };

} // namespace Device