/**
 * @file St7735DisplayDriverStub.hpp
 * @brief Defines the St7735DisplayDriverStub class for interacting with ST7735 LCD displays.
 * *

 */

#ifndef ST7735DisplayDISPLAY_H_
#define ST7735DisplayDISPLAY_H_
#include "st7735.h"
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

        // Used by lib wrapper in python to render display data
        // POTENTIALLY DUPLICATE getPixel
        DisplayPixelColor::PixelColor getPixelValue(uint8_t x, uint8_t y) const;

    protected:
        /**
         * @brief Initializes the ST7735 display.
         *

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

    private:
        // No mater if the dispaly is configured as horisontal or vertical, ST7735_HEIGHT is the longer dimention so it will always fit
        static const uint8_t MAX_WIDTH = ST7735_HEIGHT;
        static const uint8_t MAX_HEIGHT = ST7735_HEIGHT;

        IDisplayDriver::Orientation orientation = IDisplayDriver::Orientation::Vertical;

        DisplayPixelColor::PixelColor content[MAX_WIDTH][MAX_HEIGHT] = {0u};
    };

}

#endif // ST7735DisplayDISPLAY_H_