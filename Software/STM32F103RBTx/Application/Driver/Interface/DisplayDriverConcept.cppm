module;

#include <concepts>
#include <cstdint>

export module Driver.Concepts.DisplayDriver;

import Driver.DriverComponent;
// import Driver.DisplayPixelColor;

export namespace Driver::Concepts
{
    /**
     * @concept DisplayDriver
     * @brief Defines requirements for display drivers
     */
    template <typename T>
    concept DisplayDriverConcept =
        std::derived_from<T, DriverComponent> &&
        requires(T driver,
                 const T constDriver,
                 std::uint8_t x,
                 std::uint8_t y /*,
                  DisplayPixelColor::PixelColor color*/
        ) {
            // Display control
            { driver.displayOn() } noexcept;
            { driver.displayOff() } noexcept;

            /* // Pixel operations
             { driver.setPixel(x, y, color) } noexcept;
             { constDriver.getPixel(x, y, color) } noexcept;

             // Rectangle operations
             { driver.fillRectangle(x, y, x, y, color) } noexcept;
 */
            // Size queries
            { constDriver.getXSize(x) } noexcept;
            { constDriver.getYSize(y) } noexcept;
        };
}