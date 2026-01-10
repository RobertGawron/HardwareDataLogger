module;

#include <cstdint>
#include <array>

export module Driver.DisplayDriver;

import Driver.DriverComponent;
import Driver.Concepts.DisplayDriver;
// import Driver.DisplayPixelColor;

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

        // Display control (must be noexcept for concept)
        [[nodiscard]] bool displayOn() noexcept;
        [[nodiscard]] bool displayOff() noexcept;

        // Configuration
        [[nodiscard]] bool setOrientation(Orientation orientation) noexcept;
        [[nodiscard]] bool getOrientation(Orientation &orientation) const noexcept;
        [[nodiscard]] bool setCursor(std::uint8_t xPosition, std::uint8_t yPosition) noexcept;

        // Drawing operations (must be noexcept for concept)
        [[nodiscard]] bool drawBitmap(std::uint8_t xPosition, std::uint8_t yPosition,
                                      std::uint8_t &bitmap) noexcept;
        [[nodiscard]] bool fillRGBRectangle(std::uint8_t xPosition,
                                            std::uint8_t yPosition,
                                            std::uint8_t &data,
                                            std::uint8_t width,
                                            std::uint8_t height) noexcept;
        /* [[nodiscard]] bool fillRectangle(std::uint8_t xPosition,
                                            std::uint8_t yPosition,
                                            std::uint8_t width,
                                            std::uint8_t height,
                                            DisplayPixelColor::PixelColor color) noexcept;
         [[nodiscard]] bool setPixel(std::uint8_t xPosition,
                                       std::uint8_t yPosition,
                                       DisplayPixelColor::PixelColor color) noexcept;
         [[nodiscard]] bool getPixel(std::uint8_t xPosition,
                                       std::uint8_t yPosition,
                                       DisplayPixelColor::PixelColor &color) const noexcept;
 */

        // Size queries (must be noexcept for concept)
        [[nodiscard]] bool getXSize(std::uint8_t &size) const noexcept;
        [[nodiscard]] bool getYSize(std::uint8_t &size) const noexcept;

        /*
        // Helper for Python wrapper
        [[nodiscard]] DisplayPixelColor::PixelColor getPixelValue(std::uint8_t xPosition,
                                                                  std::uint8_t yPosition) const noexcept;
*/
        // Lifecycle methods (required by DriverComponent)
        [[nodiscard]] bool onInit() noexcept;
        [[nodiscard]] bool onStart() noexcept { return true; }
        [[nodiscard]] bool onStop() noexcept { return true; }

    private:
        // Display dimensions - ST7735_HEIGHT assumed to be defined elsewhere
        static constexpr std::uint8_t MAX_WIDTH = 160;  // ST7735_HEIGHT
        static constexpr std::uint8_t MAX_HEIGHT = 160; // ST7735_HEIGHT

        Orientation orientation{Orientation::Vertical};
        //   std::array<std::array<DisplayPixelColor::PixelColor, MAX_HEIGHT>, MAX_WIDTH> content{};
    };

    static_assert(Driver::Concepts::DisplayDriverConcept<DisplayDriver>,
                  "DisplayDriver must satisfy concept requirements");
}