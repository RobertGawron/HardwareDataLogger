#include "St7735DisplayDriverStub.hpp"

namespace Driver
{
    uint8_t St7735DisplayDriverStub::getDisplayWidth() const
    {
        return ST7735_WIDTH;
    }
    uint8_t St7735DisplayDriverStub::getDisplayHeight() const
    {
        return ST7735_HEIGHT;
    }

    St7735DisplayDriverStub::PixelRGBP St7735DisplayDriverStub::getPixel(uint8_t x, uint8_t y) const
    {
        PixelRGBP test{12, 222, 2};
        return test;
    }
}
