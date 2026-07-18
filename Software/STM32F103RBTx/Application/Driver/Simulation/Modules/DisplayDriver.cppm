module;

#include <cstdint>
#include <array>

export module Driver.DisplayDriver;

import Driver.DriverComponent;
import Driver.Concepts.DisplayDriver;

export namespace Driver
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

        // Display control
        [[nodiscard]] auto displayOn() noexcept -> bool;
        [[nodiscard]] auto displayOff() noexcept -> bool;

        // Configuration
        [[nodiscard]] auto setOrientation(Orientation orientation) noexcept -> bool;
        [[nodiscard]] auto getOrientation(Orientation &orientation) const noexcept -> bool;
        [[nodiscard]] auto setCursor(std::uint8_t xPosition, std::uint8_t yPosition) noexcept -> bool;

        // Drawing operations
        [[nodiscard]] auto drawBitmap(std::uint8_t xPosition, std::uint8_t yPosition,
                                      std::uint8_t &bitmap) noexcept -> bool;
        [[nodiscard]] auto fillRGBRectangle(std::uint8_t xPosition,
                                            std::uint8_t yPosition,
                                            std::uint8_t &data,
                                            std::uint8_t width,
                                            std::uint8_t height) noexcept -> bool;
        // Size operations
        [[nodiscard]] auto getXSize(std::uint8_t &size) const noexcept -> bool;
        [[nodiscard]] auto getYSize(std::uint8_t &size) const noexcept -> bool;

        // Lifecycle methods
        [[nodiscard]] auto onInit() noexcept -> bool;
        [[nodiscard]] auto onStart() noexcept -> bool { return true; }
        [[nodiscard]] auto onStop() noexcept -> bool { return true; }

    private:
        // Display dimensions
        // Defined by HW of the ST7735 display
        static constexpr std::uint8_t MAX_WIDTH = 128U;
        static constexpr std::uint8_t MAX_HEIGHT = 160U;

        Orientation orientation{Orientation::Vertical};
        //   std::array<std::array<DisplayPixelColor::PixelColor, MAX_HEIGHT>, MAX_WIDTH> content{};
    };

    static_assert(Driver::Concepts::DisplayDriverConcept<DisplayDriver>,
                  "DisplayDriver must satisfy concept requirements");
}