#include "Driver/Inc/St7735DisplayDriver.hpp"
#include "Driver/Inc/DisplayPixelColor.hpp"
#include "stm32f1xx_hal.h" // st7735.h needs
#include "st7735.h"

namespace Driver
{
    bool St7735DisplayDriver::onInitialize()
    {
        // This can fail but the lib is implemented in a way that everything returns void.
        //  ST7735_Unselect();

        ST7735_Init();
        // fillScreen(DisplayPixelColor::getColor(0xff, 0xff, 0));

        return true;
    }

    bool St7735DisplayDriver::onStart()
    {
        const bool status = true;

        return status;
    }

    bool St7735DisplayDriver::onStop()
    {
        const bool status = true;

        return status;
    }

    bool St7735DisplayDriver::onReset()
    {
        return true;
    }

    bool St7735DisplayDriver::drawPixel(uint16_t x, uint16_t y, uint16_t color)
    {
        ST7735_DrawPixel(x, y, color);

        return true;
    }
    bool St7735DisplayDriver::writeString(uint16_t x, uint16_t y, const char *str, DisplayFont font, uint16_t color, uint16_t bgcolor)
    {
        ST7735_WriteString(x, y, str, font, color, bgcolor);

        return true;
    }
    bool St7735DisplayDriver::fillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color)
    {
        ST7735_FillRectangle(x, y, w, h, color);

        return true;
    }
    bool St7735DisplayDriver::fillScreen(uint16_t color)
    {
        ST7735_FillScreen(color);

        return true;
    }
    bool St7735DisplayDriver::drawImage(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const uint16_t *data)
    {
        ST7735_DrawImage(x, y, w, h, data);

        return true;
    }
    void St7735DisplayDriver::invertColors(bool invert)
    {
        ST7735_InvertColors(invert);
    }
}
