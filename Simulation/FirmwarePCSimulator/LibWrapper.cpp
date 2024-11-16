#include "LibWrapper.hpp"
#include <stdint.h>

#include "PlatformFactoryStm32.hpp"
#include "MyApplication.hpp"

#include "St7735DisplayDriverStub.hpp"
#include "DisplayPixelColor.hpp"

extern Driver::St7735DisplayDriverStub st7735DisplayDriverStub;

void LibWrapper_Init()
{
    app_init();
}

void LibWrapper_Tick()
{

    app_tick();
}

// I need display, key presses, BNC pulses and output from uart, wifi and sd card

bool LibWrapper_PressKey()
{
    // return displayDriver.getDisplayWidth();

    return true;
}

uint8_t LibWrapper_GetDisplayWidth()
{
    uint8_t width = 0u;

    st7735DisplayDriverStub.getXSize(width);
    return width;
}

uint8_t LibWrapper_GetDisplayHeight()
{
    uint8_t height = 0u;

    st7735DisplayDriverStub.getYSize(height);
    return height;
}

PixelValue LibWrapper_GetPixelValue(uint8_t x, uint8_t y)
{
    //    Driver::DisplayPixelColor value = displayDriver.getPixel(x, y);
    if (st7735DisplayDriverStub.content[x][y] > 0)
    {
        // PixelValue pixel{value.RED, value.GREEN, value.BLUE};
        PixelValue pixel{0, 0, 0};
        return pixel;
    }
    else
    {
        // PixelValue pixel{value.RED, value.GREEN, value.BLUE};
        PixelValue pixel{5, 5, 5};
        return pixel;
    }
}
