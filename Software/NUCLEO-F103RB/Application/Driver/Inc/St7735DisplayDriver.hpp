/**
 * @file St7735DisplayDriver.hpp
 * @brief Defines the St7735DisplayDriver class for interacting with ST7735 LCD displays.
 */

#ifndef ST7735DisplayDISPLAY_H_
#define ST7735DisplayDISPLAY_H_

#include "IDisplayDriver.hpp"
#include "fonts.h"

namespace Driver
{

    /**
     * @class St7735DisplayDriver
     * @brief Driver class for the ST7735 LCD display.
     *
     * This class provides implementation for controlling the ST7735 LCD display. It includes functions
     * to initialize the display, draw pixels, write text, fill rectangles, draw images, and invert colors.
     * ST7735 is a low cost popular 128x160 RGB LCD display.
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
        virtual ~St7735DisplayDriver() = default;

        // Delete copy constructor and assignment operator
        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        St7735DisplayDriver(const St7735DisplayDriver &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         */
        St7735DisplayDriver &operator=(const St7735DisplayDriver &) = delete;

        /**
         * @brief Draws a single pixel on the display.
         *
         * This function draws a pixel at the specified (x, y) coordinate with the given color.
         *
         * @param x The x-coordinate of the pixel.
         * @param y The y-coordinate of the pixel.
         * @param color The color of the pixel.
         * @return True if the pixel was drawn successfully; false otherwise.
         */
        virtual bool drawPixel(uint16_t x, uint16_t y, uint16_t color) override;

        /**
         * @brief Writes a string to the display.
         *
         * This function writes a string at the specified (x, y) coordinate using the specified font, text color, and background color.
         *
         * @param x The x-coordinate of the starting point of the string.
         * @param y The y-coordinate of the starting point of the string.
         * @param str The string to write.
         * @param font The font to use for writing the string.
         * @param color The color of the text.
         * @param bgcolor The background color behind the text.
         * @return True if the string was written successfully; false otherwise.
         */
        virtual bool writeString(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor) override;

        /**
         * @brief Fills a rectangle on the display with a specified color.
         *
         * This function fills a rectangle at the specified (x, y) coordinate with the given width, height, and color.
         *
         * @param x The x-coordinate of the top-left corner of the rectangle.
         * @param y The y-coordinate of the top-left corner of the rectangle.
         * @param w The width of the rectangle.
         * @param h The height of the rectangle.
         * @param color The color to fill the rectangle with.
         * @return True if the rectangle was filled successfully; false otherwise.
         */
        virtual bool fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) override;

        /**
         * @brief Fills the entire display with a specified color.
         *
         * This function fills the entire screen with the given color.
         *
         * @param color The color to fill the screen with.
         * @return True if the screen was filled successfully; false otherwise.
         */
        virtual bool fillScreen(uint16_t color) override;

        /**
         * @brief Draws an image on the display.
         *
         * This function draws an image at the specified (x, y) coordinate with the given width and height.
         *
         * @param x The x-coordinate of the top-left corner of the image.
         * @param y The y-coordinate of the top-left corner of the image.
         * @param w The width of the image.
         * @param h The height of the image.
         * @param data A pointer to the image data.
         * @return True if the image was drawn successfully; false otherwise.
         */
        virtual bool drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data) override;

        /**
         * @brief Inverts the colors of the display.
         *
         * This function inverts the colors of the display based on the `invert` flag.
         *
         * @param invert If true, inverts the colors; if false, restores the original colors.
         */
        virtual void invertColors(bool invert) override;

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