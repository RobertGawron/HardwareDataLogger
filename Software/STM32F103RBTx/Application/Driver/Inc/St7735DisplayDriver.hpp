/**
 * @file St7735DisplayDriver.hpp
 * @brief Defines the St7735DisplayDriver class for interacting with ST7735 LCD displays.

 */

#ifndef ST7735DisplayDISPLAY_H_
#define ST7735DisplayDISPLAY_H_

#include "Driver/Interfaces/IDisplayDriver.hpp"

namespace Driver
{

    /**
     * @class St7735DisplayDriver
     * @brief Driver class for the ST7735 LCD display
     *
     */
    class St7735DisplayDriver : public Driver::IDisplayDriver
    {
    public:
        /**
         * @brief Default constructor for St7735DisplayDriver.
         */
        explicit St7735DisplayDriver() = default;

        /**
         * @brief Virtual destructor for St7735DisplayDriver.
         *
         * Ensures proper cleanup of derived classes.
         */
        ~St7735DisplayDriver() override = default;

        // Delete copy constructor and assignment operator
        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        St7735DisplayDriver(const St7735DisplayDriver &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         */
        St7735DisplayDriver &operator=(const St7735DisplayDriver &) = delete;

        Status displayOn() override;
        Status displayOff() override;
        Status setOrientation(Orientation orientation) override;
        Status getOrientation(Orientation &orientation) const override;
        Status setCursor(std::uint8_t x, std::uint8_t y) override;
        Status drawBitmap(std::uint8_t x, std::uint8_t y, std::uint8_t &bitmap) override;
        Status fillRGBRectangle(std::uint8_t x,
                                std::uint8_t y,
                                std::uint8_t &data,
                                std::uint8_t width,
                                std::uint8_t height) override;
        Status drawHorizontalLine(std::uint8_t x,
                                  std::uint8_t y,
                                  std::uint8_t length,
                                  DisplayPixelColor::PixelColor color) override;
        Status drawVerticalLine(std::uint8_t x,
                                std::uint8_t y,
                                std::uint8_t length,
                                DisplayPixelColor::PixelColor color) override;
        Status fillRectangle(std::uint8_t x,
                             std::uint8_t y,
                             std::uint8_t width,
                             std::uint8_t height,
                             DisplayPixelColor::PixelColor color) override;
        Status setPixel(std::uint8_t x,
                        std::uint8_t y,
                        DisplayPixelColor::PixelColor color) override;
        Status getPixel(std::uint8_t x,
                        std::uint8_t y,
                        DisplayPixelColor::PixelColor &color) const override;
        Status getXSize(std::uint8_t &size) const override;
        Status getYSize(std::uint8_t &size) const override;

    protected:
        /**
         * @brief Initializes the ST7735 display.
         *
         * This function initializes the display and prepares it for use. Note that SPI is used
         * to communicate with the device, but it is obtained directly by the library, so
         * this function does not manage GPIO pins for SPI or the SPI peripheral itself.
         *
         * @return True if initialization was successful, false otherwise.
         */
        bool onInitialize() override;

        /**
         * @brief Starts the display driver.
         *
         * This function starts the display driver and makes it ready for drawing operations. It ensures
         * the display is turned on and ready to receive commands and data.
         *
         * @return True if the driver was started successfully, false otherwise.
         */
        bool onStart() override;

        /**
         * @brief Stops the display driver.
         *
         * This function stops the display driver, typically turning off the display or putting it into a low-power
         * state. This can be used when the display is no longer needed to save power.
         *
         * @return True if the driver was stopped successfully, false otherwise.
         */
        bool onStop() override;

        /**
         * @brief Resets the display driver.
         *
         * This function resets the display.
         *
         * @return True if the driver was reset successfully, false otherwise.
         */
        bool onReset() override;
    };

}

#endif // ST7735DisplayDISPLAY_H_
