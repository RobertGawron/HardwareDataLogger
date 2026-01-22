module;

#include <concepts>
#include <cstdint>

export module Driver.Concepts.DisplayDriver;

import Driver.DriverComponent;

export namespace Driver::Concepts
{
    /**
     * @concept DisplayDriverConcept
     * @brief Requirements for a display driver component.
     *
     * @details Matches the current Driver::DisplayDriver interface:
     * - lifecycle hooks: onInit(), onStart()
     * - basic drawing API: setCursor(), drawBitmap(), fillRGBRectangle()
     *
     * All functions must return bool and be noexcept where declared noexcept
     * in the concrete driver API.
     */
    template <typename T>
    concept DisplayDriverConcept =
        std::derived_from<T, DriverComponent> &&
        requires(T driver,
                 std::uint8_t x,
                 std::uint8_t y,
                 std::uint8_t width,
                 std::uint8_t height,
                 std::uint8_t &bitmap,
                 std::uint8_t &data) {
            // Lifecycle
            { driver.onInit() } -> std::same_as<bool>;
            { driver.onStart() } -> std::same_as<bool>;

            // Drawing primitives (noexcept in the interface)
            { driver.setCursor(x, y) } noexcept -> std::same_as<bool>;
            { driver.drawBitmap(x, y, bitmap) } noexcept -> std::same_as<bool>;
            { driver.fillRGBRectangle(x, y, data, width, height) } noexcept -> std::same_as<bool>;
        };
} // namespace Driver::Concepts