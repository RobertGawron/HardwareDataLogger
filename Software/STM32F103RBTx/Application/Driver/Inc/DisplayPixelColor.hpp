/**
 * @file DisplayPixelColor.hpp
 * @brief Provides utilities for converting RGB values to the RGB565 color format used by certain displays.
 */

#ifndef DisplayPixelColor_h
#define DisplayPixelColor_h

#include <cstdint>

namespace Driver
{
    /**
     * @class DisplayPixelColor
     * @brief A utility class for handling colors in RGB565 format.
     *
     * The `DisplayPixelColor` class provides methods for converting standard 8-bit RGB values
     * into the 16-bit RGB565 format, commonly used in embedded systems for display drivers.
     * It also includes predefined color constants for convenience.
     */
    class DisplayPixelColor
    {
    public:
        /// Alias for the RGB565 color representation.
        using PixelColor = std::uint16_t;

        /**
         * @brief Converts 8-bit RGB values to a 16-bit RGB565 format.
         *
         * Converts 8-bit red, green, and blue components into a single 16-bit value
         * using the RGB565 format. This format allocates 5 bits for red, 6 bits for green,
         * and 5 bits for blue.
         *
         * @param red The red component of the color, ranging from 0 to 255.
         * @param green The green component of the color, ranging from 0 to 255.
         * @param blue The blue component of the color, ranging from 0 to 255.
         * @return The 16-bit RGB565 color representation.
         */
        static constexpr PixelColor getColor(std::uint8_t red, std::uint8_t green, std::uint8_t blue) noexcept
        {
            return getColorRGB565(red, green, blue);
        }

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
         * Converts 8-bit RGB values to a 16-bit RGB565 format.
         *
         * The RGB565 format is commonly used in TFT displays. It allocates 5 bits
         * for red, 6 bits for green, and 5 bits for blue. This format is memory-efficient
         * while still providing a reasonable range of colors.
         *
         * The human eye is more sensitive to green, which is why green is given
         * an extra bit compared to red and blue.
         *
         * Since the original 8-bit color values (0-255) need to be reduced to fit
         * into 5 or 6 bits, the lower bits are truncated, which can result in some
         * loss of color precision.
         */
        static constexpr PixelColor getColorRGB565(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
        {
            constexpr std::uint8_t BITS_IN_BYTE = 8;

            // Extract the top bits for each color channel and combine them
            std::uint16_t r = (red >> (BITS_IN_BYTE - RED_BITS)) & RED_MASK;       // 5 bits for red
            std::uint16_t g = (green >> (BITS_IN_BYTE - GREEN_BITS)) & GREEN_MASK; // 6 bits for green
            std::uint16_t b = (blue >> (BITS_IN_BYTE - BLUE_BITS)) & BLUE_MASK;    // 5 bits for blue

            // Combine the bits into a single 16-bit value according to RGB565 format
            return (r << RED_SHIFT) | (g << GREEN_SHIFT) | (b << BLUE_SHIFT);
        }

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
        static constexpr std::uint16_t RED_MASK = (1 << RED_BITS) - 1; // 0b11111
        /// Mask for isolating the green component in RGB565 format.
        static constexpr std::uint16_t GREEN_MASK = (1 << GREEN_BITS) - 1; // 0b111111
        /// Mask for isolating the blue component in RGB565 format.
        static constexpr std::uint16_t BLUE_MASK = (1 << BLUE_BITS) - 1; // 0b11111
    };
}

#endif // DisplayPixelColor_h
