#include "LibWrapper.hpp"
#include "PlatformFactory.hpp"
#include "MyApplication.hpp"

#include "Driver/Interface/KeyboardKeyState.hpp"
#include "Driver/Interface/KeyboardKeyIdentifier.hpp"
#include "Driver/Interface/DisplayPixelColor.hpp"

#include "PulseCounterDriverStub.hpp"
#include "KeyboardDriverStub.hpp"
#include "St7735DisplayDriverStub.hpp"

#include "HmiEventHandlers.hpp"

#include <array>
#include <cstdint>

// move it to builder
extern BusinessLogic::PlatformFactory platform;

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
    // Cast the interface reference to the specific Stub implementation
    auto &keyboardStub = static_cast<Driver::KeyboardDriverStub &>(platform.getKeyboardDriver());

    keyboardStub.setKeyState(
        static_cast<Driver::KeyboardKeyIdentifier>(keyId),
        Driver::KeyboardKeyState::Pressed);
}

void LibWrapper_KeyReleased(KeyboardKeyIdentifier keyId)
{
    auto &keyboardStub = static_cast<Driver::KeyboardDriverStub &>(platform.getKeyboardDriver());

    keyboardStub.setKeyState(
        static_cast<Driver::KeyboardKeyIdentifier>(keyId),
        Driver::KeyboardKeyState::NotPressed);
}

std::uint8_t LibWrapper_GetDisplayWidth()
{
    std::uint8_t width = 0U;

    const auto &displayStub = static_cast<Driver::St7735DisplayDriverStub &>(platform.getDisplayDriver());
    displayStub.getXSize(width);

    return width;
}

std::uint8_t LibWrapper_GetDisplayHeight()
{
    std::uint8_t height = 0U;

    const auto &displayStub = static_cast<Driver::St7735DisplayDriverStub &>(platform.getDisplayDriver());
    displayStub.getYSize(height);

    return height;
}

std::uint16_t LibWrapper_GetPixelValue(std::uint8_t x, std::uint8_t y)
{
    const auto &displayStub = static_cast<Driver::St7735DisplayDriverStub &>(platform.getDisplayDriver());

    const Driver::DisplayPixelColor::PixelColor value = displayStub.getPixelValue(x, y);

    return value;
}

void LibWrapper_UpdatePulseCounters(const std::array<std::uint16_t, PULSE_COUNTER_COUNT> &pulseCounters)
{
    for (std::uint8_t i = 0U; i < PULSE_COUNTER_COUNT; ++i)
    {
        setPulseCounter(i, pulseCounters.at(i));
    }
}

void LibWrapper_RegisterSerialTxCallback(SerialTxCallback callback)
{
    registerSerialTxCallback(callback);
}
