/**
 * @file DisplayDriver.hpp
 * @brief Defines the DisplayDriver class for interacting with ST7735 LCD displays.
 */

#ifndef ST7735DisplayDISPLAY_H_
#define ST7735DisplayDISPLAY_H_

#include "Driver/Interface/DisplayDriverConcept.hpp"
#include "Driver/Interface/DriverComponent.hpp"
#include "Driver/Interface/DisplayPixelColor.hpp"

#include <array>
#include <cstdint>

namespace Driver
{
    /**
     * @class DisplayDriver
     * @brief Driver class for the ST7735 LCD display.
     *
     * This class provides implementation for controlling the ST7735 LCD display. It includes functions
     * to initialize the display, draw pixels, write text, fill rectangles, draw images, and invert colors.
     * ST7735 is a low cost popular 128x160 RGB LCD display.
     */
    class DisplayDriver final : public DriverComponent
    {
    public:
        /**
         * @enum StatusEnum
         * @brief Operation status codes for display operations.
         */
        enum class StatusEnum : std::uint8_t
        {
            Ok = 0U,
            Fail = 1U
        };
        using Status = StatusEnum;

        /**
         * @enum OrientationEnum
         * @brief Display orientation options.
         */
        enum class OrientationEnum : std::uint8_t
        {
            Horizontal = 0U,
            Vertical = 1U
        };
        using Orientation = OrientationEnum;

        DisplayDriver() = default;
        ~DisplayDriver() = default;

        // Non-copyable and non-movable
        DisplayDriver(const DisplayDriver &) = delete;
        DisplayDriver(DisplayDriver &&) = delete;
        DisplayDriver &operator=(const DisplayDriver &) = delete;
        DisplayDriver &operator=(DisplayDriver &&) = delete;

        // Display control (must be noexcept for concept)
        [[nodiscard]] Status displayOn() noexcept;
        [[nodiscard]] Status displayOff() noexcept;

        // Configuration
        [[nodiscard]] Status setOrientation(Orientation orientation) noexcept;
        [[nodiscard]] Status getOrientation(Orientation &orientation) const noexcept;
        [[nodiscard]] Status setCursor(std::uint8_t xPosition, std::uint8_t yPosition) noexcept;

        // Drawing operations (must be noexcept for concept)
        [[nodiscard]] Status drawBitmap(std::uint8_t xPosition, std::uint8_t yPosition,
                                        std::uint8_t &bitmap) noexcept;
        [[nodiscard]] Status fillRGBRectangle(std::uint8_t xPosition,
                                              std::uint8_t yPosition,
                                              std::uint8_t &data,
                                              std::uint8_t width,
                                              std::uint8_t height) noexcept;
        [[nodiscard]] Status fillRectangle(std::uint8_t xPosition,
                                           std::uint8_t yPosition,
                                           std::uint8_t width,
                                           std::uint8_t height,
                                           DisplayPixelColor::PixelColor color) noexcept;
        [[nodiscard]] Status setPixel(std::uint8_t xPosition,
                                      std::uint8_t yPosition,
                                      DisplayPixelColor::PixelColor color) noexcept;
        [[nodiscard]] Status getPixel(std::uint8_t xPosition,
                                      std::uint8_t yPosition,
                                      DisplayPixelColor::PixelColor &color) const noexcept;

        // Size queries (must be noexcept for concept)
        [[nodiscard]] Status getXSize(std::uint8_t &size) const noexcept;
        [[nodiscard]] Status getYSize(std::uint8_t &size) const noexcept;

        // Helper for Python wrapper
        [[nodiscard]] DisplayPixelColor::PixelColor getPixelValue(std::uint8_t xPosition,
                                                                  std::uint8_t yPosition) const noexcept;

        // Lifecycle methods (required by DriverComponent)
        [[nodiscard]] bool onInit() noexcept;
        [[nodiscard]] bool onStart() noexcept { return true; }
        [[nodiscard]] bool onStop() noexcept { return true; }

    private:
        // Display dimensions - ST7735_HEIGHT assumed to be defined elsewhere
        static constexpr std::uint8_t MAX_WIDTH = 160;  // ST7735_HEIGHT
        static constexpr std::uint8_t MAX_HEIGHT = 160; // ST7735_HEIGHT

        Orientation orientation{Orientation::Vertical};
        std::array<std::array<DisplayPixelColor::PixelColor, MAX_HEIGHT>, MAX_WIDTH> content{};
    };

    static_assert(Driver::Concepts::DisplayDriverConcept<DisplayDriver>,
                  "DisplayDriver must satisfy concept requirements");
}

#endif // ST7735DisplayDISPLAY_H_