#ifndef ST7735DisplayDISPLAY_H_
#define ST7735DisplayDISPLAY_H_

#include "Driver/Interface/DisplayDriverConcept.hpp"
#include "Driver/Interface/DriverComponent.hpp"
#include "Driver/Interface/DisplayPixelColor.hpp"

#include <cstdint>

namespace Driver
{

    /**
     * @class DisplayDriver
     * @brief Hardware driver for ST7735 LCD display via SPI
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
            Ok = 0U,  ///< Operation completed successfully.
            Fail = 1U ///< Operation failed.
        };

        using Status = StatusEnum; ///< Alias for StatusEnum.

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

        [[nodiscard]] Status displayOn() noexcept;
        [[nodiscard]] Status displayOff() noexcept;
        [[nodiscard]] Status setOrientation(Orientation orientation) noexcept;
        [[nodiscard]] Status getOrientation(Orientation &orientation) const noexcept;
        [[nodiscard]] Status setCursor(std::uint8_t xPosition, std::uint8_t yPosition) noexcept;
        [[nodiscard]] Status drawBitmap(std::uint8_t xPosition, std::uint8_t yPosition, std::uint8_t &bitmap) noexcept;
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
        [[nodiscard]] Status getXSize(std::uint8_t &size) const noexcept;
        [[nodiscard]] Status getYSize(std::uint8_t &size) const noexcept;

    protected:
        [[nodiscard]] bool onInit();
    };

    static_assert(Driver::Concepts::DisplayDriverConcept<DisplayDriver>,
                  "DisplayDriver must satisfy concept requirements");

} // namespace Driver

#endif // ST7735DisplayDISPLAY_H_