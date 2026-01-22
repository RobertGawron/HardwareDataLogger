module;

#include <cstdint>

export module Driver.DisplayDriver;

import Driver.DriverComponent;
import Driver.Concepts.DisplayDriver;

export namespace Driver
{

    /**
     * @class DisplayDriver
     * @brief Hardware driver for ST7735 LCD display via SPI
     */
    class DisplayDriver final : public DriverComponent
    {
    public:
        DisplayDriver() = default;
        ~DisplayDriver() = default;

        DisplayDriver(const DisplayDriver &) = delete;
        DisplayDriver &operator=(const DisplayDriver &) = delete;
        DisplayDriver(DisplayDriver &&) = delete;
        DisplayDriver &operator=(DisplayDriver &&) = delete;

        [[nodiscard]] bool onInit();
        [[nodiscard]] bool onStart();

        [[nodiscard]] bool setCursor(std::uint8_t xPosition,
                                     std::uint8_t yPosition) noexcept;

        [[nodiscard]] bool drawBitmap(std::uint8_t xPosition,
                                      std::uint8_t yPosition,
                                      std::uint8_t &bitmap) noexcept;

        [[nodiscard]] bool fillRGBRectangle(std::uint8_t xPosition,
                                            std::uint8_t yPosition,
                                            std::uint8_t &data,
                                            std::uint8_t width,
                                            std::uint8_t height) noexcept;
    };

    static_assert(Driver::Concepts::DisplayDriverConcept<DisplayDriver>,
                  "DisplayDriver must satisfy concept requirements");

} // namespace Driver