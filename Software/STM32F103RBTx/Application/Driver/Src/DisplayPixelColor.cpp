#include "Driver/Inc/DisplayPixelColor.hpp"

namespace Driver
{
    const DisplayPixelColor::PixelColor DisplayPixelColor::BLACK = DisplayPixelColor::getColor(0x00, 0x00, 0x00);
    const DisplayPixelColor::PixelColor DisplayPixelColor::BLUE = DisplayPixelColor::getColor(0x00, 0x00, 0xFF);
    const DisplayPixelColor::PixelColor DisplayPixelColor::RED = DisplayPixelColor::getColor(0xFF, 0x00, 0x00);
    const DisplayPixelColor::PixelColor DisplayPixelColor::GREEN = DisplayPixelColor::getColor(0x00, 0xFF, 0x00);
    const DisplayPixelColor::PixelColor DisplayPixelColor::CYAN = DisplayPixelColor::getColor(0x00, 0xFF, 0xFF);
    const DisplayPixelColor::PixelColor DisplayPixelColor::MAGENTA = DisplayPixelColor::getColor(0xFF, 0x00, 0xFF);
    const DisplayPixelColor::PixelColor DisplayPixelColor::YELLOW = DisplayPixelColor::getColor(0xFF, 0xFF, 0x00);
    const DisplayPixelColor::PixelColor DisplayPixelColor::WHITE = DisplayPixelColor::getColor(0xFF, 0xFF, 0xFF);
} // namespace Driver
