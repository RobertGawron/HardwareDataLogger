#include "Simulation.hpp"
#include <stdint.h>

#include "PlatformFactoryStm32.hpp"
#include "MyApplication.hpp"

#include "DisplayDriverStub.hpp"

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
    Driver::DisplayDriverStub::PixelRGBP value = displayDriver.getPixel(x, y);

    PixelValue pixel{value.red, value.green, value.blue};
    return pixel;
}
