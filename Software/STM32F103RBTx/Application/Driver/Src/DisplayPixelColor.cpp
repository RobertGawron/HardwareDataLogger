#include "Driver/Inc/DisplayPixelColor.hpp"

namespace Driver
{

    DisplayPixelColor::PixelColor DisplayPixelColor::getColor(uint8_t red, uint8_t green, uint8_t blue)
    {
        return getColorRGB565(red, green, blue);
    }

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
    DisplayPixelColor::PixelColor DisplayPixelColor::getColorRGB565(uint8_t red, uint8_t green, uint8_t blue)
    {
        // Extract the top bits for each color channel and combine them
        uint16_t r = (red >> (8 - RED_BITS)) & RED_MASK;       // 5 bits for red
        uint16_t g = (green >> (8 - GREEN_BITS)) & GREEN_MASK; // 6 bits for green
        uint16_t b = (blue >> (8 - BLUE_BITS)) & BLUE_MASK;    // 5 bits for blue

        // Combine the bits into a single 16-bit value according to RGB565 format
        return (r << RED_SHIFT) | (g << GREEN_SHIFT) | (b << BLUE_SHIFT);
    }

    const DisplayPixelColor::PixelColor DisplayPixelColor::BLACK = DisplayPixelColor::getColor(0x00, 0x00, 0x00);
    const DisplayPixelColor::PixelColor DisplayPixelColor::BLUE = DisplayPixelColor::getColor(0x00, 0x00, 0xFF);
    const DisplayPixelColor::PixelColor DisplayPixelColor::RED = DisplayPixelColor::getColor(0xFF, 0x00, 0x00);
    const DisplayPixelColor::PixelColor DisplayPixelColor::GREEN = DisplayPixelColor::getColor(0x00, 0xFF, 0x00);
    const DisplayPixelColor::PixelColor DisplayPixelColor::CYAN = DisplayPixelColor::getColor(0x00, 0xFF, 0xFF);
    const DisplayPixelColor::PixelColor DisplayPixelColor::MAGENTA = DisplayPixelColor::getColor(0xFF, 0x00, 0xFF);
    const DisplayPixelColor::PixelColor DisplayPixelColor::YELLOW = DisplayPixelColor::getColor(0xFF, 0xFF, 0x00);
    const DisplayPixelColor::PixelColor DisplayPixelColor::WHITE = DisplayPixelColor::getColor(0xFF, 0xFF, 0xFF);
} // namespace Driver