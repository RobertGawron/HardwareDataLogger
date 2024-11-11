#include "LibWrapper.hpp"
#include <stdint.h>

#include "PlatformFactoryStm32.hpp"
#include "MyApplication.hpp"

// #include "DisplayDriverStub.hpp"
#include "DisplayPixelColor.hpp"

// extern Driver::DisplayDriverStub displayDriver;

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

// bool

uint8_t LibWrapper_GetDisplayWidth()
{
    // return displayDriver.getDisplayWidth();
    return 5;
}

uint8_t LibWrapper_GetDisplayHeight()
{
    //  return displayDriver.getDisplayHeight();
    return 5;
}

PixelValue LibWrapper_GetPixelValue(uint8_t x, uint8_t y)
{
    //    Driver::DisplayPixelColor value = displayDriver.getPixel(x, y);

    // PixelValue pixel{value.RED, value.GREEN, value.BLUE};
    PixelValue pixel{5, 5, 5};
    return pixel;
}
