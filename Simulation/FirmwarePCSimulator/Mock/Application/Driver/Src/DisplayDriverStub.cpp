#include "DisplayDriverStub.hpp"
#include "stm32f1xx_hal.h" // st7735.h needs
#include "st7735.h"        // for ST7735_WIDTH and ST7735_HEIGHT

namespace Driver
{

    bool DisplayDriverStub::onInitialize()
    {
        return true;
    }

    bool DisplayDriverStub::onStart()
    {
        return true;
    }

    bool DisplayDriverStub::onStop()
    {
        return true;
    }

    bool DisplayDriverStub::onReset()
    {
        return true;
    }

    uint8_t DisplayDriverStub::getDisplayWidth() const
    {
        return ST7735_WIDTH;
    }
    uint8_t DisplayDriverStub::getDisplayHeight() const
    {
        return ST7735_HEIGHT;
    }

    DisplayPixelColor DisplayDriverStub::getPixel(uint8_t x, uint8_t y) const
    {
        DisplayPixelColor pixel;
        // dummy
        return pixel;
    }

    bool DisplayDriverStub::drawPixel(uint16_t x, uint16_t y, uint16_t color)
    {
        return true;
    }
    bool DisplayDriverStub::writeString(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor)
    {
        return true;
    }

    bool DisplayDriverStub::fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
    {
        return true;
    }

    bool DisplayDriverStub::fillScreen(uint16_t color)
    {
        return true;
    }

    bool DisplayDriverStub::drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data)
    {
        return true;
    }

    void DisplayDriverStub::invertColors(bool invert)
    {
    }

}
