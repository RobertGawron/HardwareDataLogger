#include "LibWrapper.hpp"

#include "PlatformFactoryStm32.hpp"
#include "MyApplication.hpp"

#include "KeyboardDriverStub.hpp"
#include "Driver/Interfaces/KeyboardKeyState.hpp"
#include "PulseCounterDriverStub.hpp"

#include "St7735DisplayDriverStub.hpp"
#include "DisplayPixelColor.hpp"

#include <array>
#include <cstdint>

extern Driver::St7735DisplayDriverStub st7735DisplayDriverStub;
extern Driver::KeyboardDriverStub keyboardDriverStub;

void LibWrapper_Init()
{
    app_init();
    app_start();
}

void LibWrapper_Tick()
{

    app_tick();
}

// I need display, key presses, BNC pulses and output from uart, wifi and sd card

void LibWrapper_KeyPressed(KeyboardKeyIdentifier keyId)
{
    keyboardDriverStub.keyState[keyId] = Driver::KeyboardKeyState::Pressed;
}

void LibWrapper_KeyReleased(KeyboardKeyIdentifier keyId)
{
    keyboardDriverStub.keyState[keyId] = Driver::KeyboardKeyState::NotPressed;
}

std::uint8_t LibWrapper_GetDisplayWidth()
{
    std::uint8_t width = 0u;

    st7735DisplayDriverStub.getXSize(width);
    return width;
}

std::uint8_t LibWrapper_GetDisplayHeight()
{
    std::uint8_t height = 0u;

    st7735DisplayDriverStub.getYSize(height);
    return height;
}

std::uint16_t LibWrapper_GetPixelValue(std::uint8_t x, std::uint8_t y)
{
    return st7735DisplayDriverStub.getPixelValue(x, y);
}

void LibWrapper_UpdatePulseCounters(const std::array<std::uint16_t, PULSE_COUNTER_COUNT> &pulseCounters)
{
    for (std::size_t i = 0; i < PULSE_COUNTER_COUNT; i++)
    {
        setPulseCounter(i, pulseCounters.at(i));
    }
}

void LibWrapper_RegisterSerialTxCallback(SerialTxCallback callback)
{
    registerSerialTxCallback(callback);
}
