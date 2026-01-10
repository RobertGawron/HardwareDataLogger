// LibWrapper.cpp
module;

#include <array>
#include <cstdint>
#include <cstdio>
#include <optional>
#include <functional>

// module LibWrapper;

import PlatformFactory;
import BusinessLogic.ApplicationFacade;
import Driver.Interface.KeyState;
import Driver.Interface.KeyIdentifier;
import Driver.PulseCounterDriver;
import Driver.KeyboardDriver;
import Driver.DisplayDriver;
import EventHandlers;
import Driver.LightSensorDriver;
import Driver.BrightnessDriver;
import Driver.UartDriver;
import Driver.SdCardDriver;
import Driver.Interface.UartId;
import Driver.Interface.PulseCounterId;

static Driver::LightSensorDriver LightSensor;
static Driver::BrightnessDriver displayBrightness;
static Driver::DisplayDriver display;
static Driver::KeyboardDriver keyboard;

// UART drivers
static Driver::UartDriver wifiUart{Driver::UartId::TRANSMIT_VIA_WIFI};
static Driver::UartDriver usbUart{Driver::UartId::TRANSMIT_VIA_USB};
static Driver::UartDriver measurementUart{Driver::UartId::MEASUREMENT_RECEIVER};

// Storage driver
static Driver::SdCardDriver sdCard;

// Pulse counters
static Driver::PulseCounterDriver counter1{Driver::PulseCounterId::bncA};
static Driver::PulseCounterDriver counter2{Driver::PulseCounterId::bncB};
static Driver::PulseCounterDriver counter3{Driver::PulseCounterId::bncC};
static Driver::PulseCounterDriver counter4{Driver::PulseCounterId::bncD};

// Platform drivers bundle
static Driver::PlatformFactory platform = {
    .LightSensor = LightSensor,
    .displayBrightness = displayBrightness,
    .display = display,
    .keyboard = keyboard,
    .wifiUart = wifiUart,
    .usbUart = usbUart,
    .measurementUart = measurementUart,
    .sdCard = sdCard,
    .counter1 = counter1,
    .counter2 = counter2,
    .counter3 = counter3,
    .counter4 = counter4};

BusinessLogic::ApplicationFacade facade{platform};

void LibWrapper_Init()
{
    if (!facade.init())
    {
        static_cast<void>(std::fprintf(stderr, "ERROR: facade.init() failed!\n"));
    }

    if (!facade.start())
    {
        static_cast<void>(std::fprintf(stderr, "ERROR: facade.start() failed!\n"));
    }
}

void LibWrapper_Tick()
{
    if (!facade.tick())
    {
        static_cast<void>(std::fprintf(stderr, "ERROR: facade.tick() failed!\n"));
    }
}

void LibWrapper_KeyPressed(KeyIdentifier keyId)
{
    /*
    auto &keyboard = static_cast<Driver::KeyboardDriver &>(platformDrivers.keyboard);
    keyboard.setKeyState(
        static_cast<Driver::KeyIdentifier>(keyId),
        Driver::KeyState::Pressed);
*/
}

void LibWrapper_KeyReleased(KeyIdentifier keyId)
{
    auto &keyboard = static_cast<Driver::KeyboardDriver &>(platform.keyboard);
    keyboard.setKeyState(
        static_cast<Driver::KeyIdentifier>(keyId),
        Driver::KeyState::NotPressed);
}

std::uint8_t LibWrapper_GetDisplayWidth()
{
    std::uint8_t width = 0U;
    const auto &display = static_cast<Driver::DisplayDriver &>(platform.display);
    static_cast<void>(display.getXSize(width));
    return width;
}

std::uint8_t LibWrapper_GetDisplayHeight()
{
    std::uint8_t height = 0U;
    const auto &display = static_cast<Driver::DisplayDriver &>(platform.display);
    static_cast<void>(display.getYSize(height));
    return height;
}

std::uint16_t LibWrapper_GetPixelValue(std::uint8_t xPosition, std::uint8_t yPosition)
{
    std::uint16_t value = 0U;
    const auto &display = static_cast<Driver::DisplayDriver &>(platform.display);
    value = display.getPixelValue(xPosition, yPosition);
    return value;
}

void LibWrapper_UpdatePulseCounters(const std::array<std::uint32_t, PULSE_COUNTER_COUNT> &pulseCounters)
{
    for (std::uint8_t i = 0U; i < PULSE_COUNTER_COUNT; ++i)
    {
        setPulseCounter(i, pulseCounters[i]);
    }
}

void LibWrapper_RegisterSerialTxCallback(SerialTxCallback callback)
{
    registerSerialTxCallback(callback);
}

void LibWrapper_RegisterSdCardOpenCallback(SdCardOpenCallback callback)
{
    registerSdCardOpenCallback(callback);
}

void LibWrapper_RegisterSdCardWriteCallback(SdCardWriteCallback callback)
{
    registerSdCardWriteCallback(callback);
}

void LibWrapper_RegisterSdCardCloseCallback(SdCardCloseCallback callback)
{
    registerSdCardCloseCallback(callback);
}

void LibWrapper_RegisterSdCardInitializeCallback(SdCardInitializeCallback callback)
{
    registerSdCardInitializeCallback(callback);
}

void LibWrapper_RegisterSdCardStartCallback(SdCardStartCallback callback)
{
    registerSdCardStartCallback(callback);
}

void LibWrapper_RegisterSdCardStopCallback(SdCardStopCallback callback)
{
    registerSdCardStopCallback(callback);
}

void LibWrapper_RegisterSdCardResetCallback(SdCardResetCallback callback)
{
    registerSdCardResetCallback(callback);
}