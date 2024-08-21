/**
 * @file IDisplayDriver.hpp
 * @brief Defines the IDisplayDriver interface for interacting with a display device.
 */

#ifndef IDISPLAYDRIVER_H_
#define IDISPLAYDRIVER_H_

#include <stdint.h>
#include "DriverState.hpp"
#include "fonts.h" // This is probably wrong, but good enough for now.

namespace Driver
{

    /**
     * @class IDisplayDriver
     * @brief Interface for display drivers to interact with different display hardware.
     *
     * This interface provides a set of pure virtual functions that must be implemented
     * by any display driver. It includes basic display operations like drawing pixels,
     * writing strings, filling rectangles, filling the screen, drawing images, and
     * inverting colors.
     */
    class IDisplayDriver : public DriverState
    {
    public:
        /** @brief Alias for the font definition used by the display. */
        using DisplayFont = FontDef;

        /**
         * @brief Virtual destructor for IDisplayDriver.
         *
         * Ensures proper cleanup of derived classes.
         */
        virtual ~IDisplayDriver() = default;

        /**
         * @brief Draws a single pixel on the display.
         *
         * This function sets the color of a single pixel at the specified coordinates.
         *
         * @param x The x-coordinate of the pixel.
         * @param y The y-coordinate of the pixel.
         * @param color The color to set the pixel to.
         * @return True if the pixel was drawn successfully; false otherwise.
         */
        virtual bool drawPixel(uint16_t x, uint16_t y, uint16_t color) = 0;

        /**
         * @brief Writes a string to the display at the specified coordinates.
         *
         * This function writes a string using a specified font and colors at the given
         * coordinates.
         *
         * @param x The x-coordinate for the start of the string.
         * @param y The y-coordinate for the start of the string.
         * @param str The string to be written.
         * @param font The font to use for the string.
         * @param color The color of the text.
         * @param bgcolor The background color behind the text.
         * @return True if the string was written successfully; false otherwise.
         */
        virtual bool writeString(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor) = 0;

        /**
         * @brief Fills a rectangle on the display with a specific color.
         *
         * This function fills a rectangular area starting from the specified coordinates
         * with the given width, height, and color.
         *
         * @param x The x-coordinate of the top-left corner of the rectangle.
         * @param y The y-coordinate of the top-left corner of the rectangle.
         * @param w The width of the rectangle.
         * @param h The height of the rectangle.
         * @param color The color to fill the rectangle with.
         * @return True if the rectangle was filled successfully; false otherwise.
         */
        virtual bool fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) = 0;

        /**
         * @brief Fills the entire screen with a specific color.
         *
         * This function fills the entire display area with the specified color.
         *
         * @param color The color to fill the screen with.
         * @return True if the screen was filled successfully; false otherwise.
         */
        virtual bool fillScreen(uint16_t color) = 0;

        /**
         * @brief Draws an image on the display.
         *
         * This function draws an image starting at the specified coordinates.
         * The image data must be provided as an array of color values.
         *
         * @param x The x-coordinate for the top-left corner of the image.
         * @param y The y-coordinate for the top-left corner of the image.
         * @param w The width of the image.
         * @param h The height of the image.
         * @param data A pointer to the image data.
         * @return True if the image was drawn successfully; false otherwise.
         */
        virtual bool drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data) = 0;

        /**
         * @brief Inverts the colors on the display.
         *
         * This function inverts the colors on the display. If `invert` is true, all colors
         * are inverted; if false, the display returns to normal colors.
         *
         * @param invert If true, colors are inverted; if false, colors are normal.
         */
        virtual void invertColors(bool invert) = 0;
    };

}

#endif // IDISPLAYDRIVER_H_