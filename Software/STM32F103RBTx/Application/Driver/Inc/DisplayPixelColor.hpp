#ifndef DisplayPixelColor_h
#define DisplayPixelColor_h

#include <stdint.h>

namespace Driver
{
    /**
     * @class DisplayPixelColor
     * @brief Provides utilities to convert RGB values to the RGB565 color format used by certain displays.
     */
    class DisplayPixelColor
    {
    public:
        using PixelColor = uint16_t;
        /**
         * @brief Converts 8-bit RGB values to a 16-bit RGB565 format.
         *
         * This function converts 8-bit red, green, and blue color values (ranging from 0 to 255)
         * into a 16-bit color value following the RGB565 format, where red is 5 bits, green is 6 bits,
         * and blue is 5 bits.
         *
         * @param red The red component of the color, ranging from 0 to 255.
         * @param green The green component of the color, ranging from 0 to 255.
         * @param blue The blue component of the color, ranging from 0 to 255.
         * @return The 16-bit RGB565 color representation.
         */
        static PixelColor getColor(uint8_t red, uint8_t green, uint8_t blue);

        /// Predefined color: black in RGB565 format.
        static const PixelColor BLACK;
        /// Predefined color: blue in RGB565 format.
        static const PixelColor BLUE;
        /// Predefined color: red in RGB565 format.
        static const PixelColor RED;
        /// Predefined color: green in RGB565 format.
        static const PixelColor GREEN;
        /// Predefined color: cyan in RGB565 format.
        static const PixelColor CYAN;
        /// Predefined color: magenta in RGB565 format.
        static const PixelColor MAGENTA;
        /// Predefined color: yellow in RGB565 format.
        static const PixelColor YELLOW;
        /// Predefined color: white in RGB565 format.
        static const PixelColor WHITE;

    protected:
        /**
         * @brief Converts 8-bit RGB values to a 16-bit RGB565 format.
         *
         * This is an internal utility function used by the class to perform the actual conversion.
         * It takes into account the extra bit for the green component due to the human eye's
         * higher sensitivity to green light.
         *
         * @param red The red component of the color, ranging from 0 to 255.
         * @param green The green component of the color, ranging from 0 to 255.
         * @param blue The blue component of the color, ranging from 0 to 255.
         * @return The 16-bit RGB565 color representation.
         */
        static PixelColor getColorRGB565(uint8_t red, uint8_t green, uint8_t blue);

        /// Bit position shift for the red component in RGB565 format.
        static constexpr int RED_SHIFT = 11;
        /// Bit position shift for the green component in RGB565 format.
        static constexpr int GREEN_SHIFT = 5;
        /// Bit position shift for the blue component in RGB565 format.
        static constexpr int BLUE_SHIFT = 0;

        /// Number of bits used for the red component in RGB565 format.
        static constexpr int RED_BITS = 5;
        /// Number of bits used for the green component in RGB565 format.
        static constexpr int GREEN_BITS = 6;
        /// Number of bits used for the blue component in RGB565 format.
        static constexpr int BLUE_BITS = 5;

        /// Mask for isolating the red component in RGB565 format.
        static constexpr uint16_t RED_MASK = (1 << RED_BITS) - 1; // 0b11111
        /// Mask for isolating the green component in RGB565 format.
        static constexpr uint16_t GREEN_MASK = (1 << GREEN_BITS) - 1; // 0b111111
        /// Mask for isolating the blue component in RGB565 format.
        static constexpr uint16_t BLUE_MASK = (1 << BLUE_BITS) - 1; // 0b11111
    };
}

#endif