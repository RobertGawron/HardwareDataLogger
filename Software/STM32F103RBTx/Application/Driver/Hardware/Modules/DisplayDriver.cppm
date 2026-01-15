module;

#include <cstdint>

export module Driver.DisplayDriver;

import Driver.DriverComponent;
import Driver.Concepts.DisplayDriver;
// import Driver.DisplayPixelColor;

export namespace Driver
{

    /**
     * @class DisplayDriver
     * @brief Hardware driver for ST7735 LCD display via SPI
     */
    class DisplayDriver final : public DriverComponent
    {
    public:
        /**
         * @enum OrientationEnum
         * @brief Display orientation options.
         */
        enum class OrientationEnum : std::uint8_t
        {
            Horizontal = 0U, ///< Display is in horizontal orientation.
            Vertical = 1U    ///< Display is in vertical orientation.
        };

        using Orientation = OrientationEnum; ///< Alias for OrientationEnum.

        DisplayDriver() = default;
        ~DisplayDriver() = default;

        DisplayDriver(const DisplayDriver &) = delete;
        DisplayDriver &operator=(const DisplayDriver &) = delete;
        DisplayDriver(DisplayDriver &&) = delete;
        DisplayDriver &operator=(DisplayDriver &&) = delete;

        [[nodiscard]] bool displayOn() noexcept;
        [[nodiscard]] bool displayOff() noexcept;
        [[nodiscard]] bool setOrientation(Orientation orientation) noexcept;
        [[nodiscard]] bool getOrientation(Orientation &orientation) const noexcept;
        [[nodiscard]] bool setCursor(std::uint8_t xPosition, std::uint8_t yPosition) noexcept;
        [[nodiscard]] bool drawBitmap(std::uint8_t xPosition, std::uint8_t yPosition, std::uint8_t &bitmap) noexcept;
        [[nodiscard]] bool fillRGBRectangle(std::uint8_t xPosition,
                                            std::uint8_t yPosition,
                                            std::uint8_t &data,
                                            std::uint8_t width,
                                            std::uint8_t height) noexcept;
        /* [[nodiscard]] Status fillRectangle(std::uint8_t xPosition,
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
         */
        [[nodiscard]] bool getXSize(std::uint8_t &size) const noexcept;
        [[nodiscard]] bool getYSize(std::uint8_t &size) const noexcept;

    protected:
        [[nodiscard]] bool onInit();
    };

    static_assert(Driver::Concepts::DisplayDriverConcept<DisplayDriver>,
                  "DisplayDriver must satisfy concept requirements");

} // namespace Driver