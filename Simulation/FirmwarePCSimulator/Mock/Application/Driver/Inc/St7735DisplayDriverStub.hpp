/**
 * @file St7735DisplayDriverStub.hpp
 * @brief Defines the St7735DisplayDriverStub class for interacting with ST7735 LCD displays.
 * *
 * This is a class used in simulation, for simplicity then for get its state  via c wrapper and then in python HMI, all fields that contains its state are public.
 */

#ifndef ST7735DisplayDISPLAY_H_
#define ST7735DisplayDISPLAY_H_

#include "Driver/Interfaces/IDisplayDriver.hpp"
#include "Driver/Inc/DisplayPixelColor.hpp"
namespace Driver
{

    /**
     * @class St7735DisplayDriverStub
     * @brief Driver class for the ST7735 LCD display.
     *
     * This class provides implementation for controlling the ST7735 LCD display. It includes functions
     * to initialize the display, draw pixels, write text, fill rectangles, draw images, and invert colors.
     * ST7735 is a low cost popular 128x160 RGB LCD display.
     */
    class St7735DisplayDriverStub : public Driver::IDisplayDriver
    {
    public:
        /**
         * @brief Default constructor for St7735DisplayDriverStub.
         */
        explicit St7735DisplayDriverStub() = default;

        /**
         * @brief Virtual destructor for St7735DisplayDriverStub.
         *
         * Ensures proper cleanup of derived classes.
         */
        virtual ~St7735DisplayDriverStub() = default;

        // Delete copy constructor and assignment operator
        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        St7735DisplayDriverStub(const St7735DisplayDriverStub &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         */
        St7735DisplayDriverStub &operator=(const St7735DisplayDriverStub &) = delete;

        virtual Status displayOn() override;
        virtual Status displayOff() override;
        virtual Status setOrientation(Orientation orientation) override;
        virtual Status getOrientation(Orientation &orientation) const override;
        virtual Status setCursor(uint8_t x, uint8_t y) override;
        virtual Status drawBitmap(uint8_t x, uint8_t y, uint8_t &bitmap) override;
        virtual Status fillRGBRectangle(uint8_t x,
                                        uint8_t y,
                                        uint8_t &data,
                                        uint8_t width,
                                        uint8_t height) override;
        virtual Status drawHorizontalLine(uint8_t x,
                                          uint8_t y,
                                          uint8_t length, DisplayPixelColor::PixelColor color) override;
        virtual Status drawVerticalLine(uint8_t x,
                                        uint8_t y,
                                        uint8_t length,
                                        DisplayPixelColor::PixelColor color) override;
        virtual Status fillRectangle(uint8_t x,
                                     uint8_t y,
                                     uint8_t width,
                                     uint8_t height,
                                     DisplayPixelColor::PixelColor color) override;
        virtual Status setPixel(uint8_t x,
                                uint8_t y,
                                DisplayPixelColor::PixelColor color) override;
        virtual Status getPixel(uint8_t x,
                                uint8_t y,
                                DisplayPixelColor::PixelColor &color) const override;
        virtual Status getXSize(uint8_t &size) const override;
        virtual Status getYSize(uint8_t &size) const override;

        static const uint16_t MAX_WIDTH = 300;
        static const uint16_t MAX_HEIGHT = 300;

        DisplayPixelColor::PixelColor content[MAX_WIDTH][MAX_HEIGHT] = {0u};

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