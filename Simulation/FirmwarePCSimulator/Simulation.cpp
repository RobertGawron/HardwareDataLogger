#include "Simulation.hpp"
#include <stdint.h>

#include "PlatformFactoryStm32.hpp"
#include "MyApplication.hpp"

#include "DisplayDriverStub.hpp"
#include "DisplayPixelColor.hpp"

extern Driver::DisplayDriverStub displayDriver;

void Simulation_Init()
{
    app_init();
}

void Simulation_Tick()
{
    app_tick();
}

// I need display, key presses, BNC pulses and output from uart, wifi and sd card

bool Simulation_PressKey()
{
    // return displayDriver.getDisplayWidth();

    return true;
}

// bool

uint8_t Simulation_GetDisplayWidth()
{
    return displayDriver.getDisplayWidth();
}

uint8_t Simulation_GetDisplayHeight()
{
    return displayDriver.getDisplayHeight();
}

PixelValue Simulation_GetPixelValue(uint8_t x, uint8_t y)
{
    Driver::DisplayPixelColor value = displayDriver.getPixel(x, y);

    PixelValue pixel{value.RED, value.GREEN, value.BLUE};
    return pixel;
}
