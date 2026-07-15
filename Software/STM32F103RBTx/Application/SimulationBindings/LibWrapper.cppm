module;

#include <array>
#include <cstdint>
#include <cstdio>
#include <print>
#include <utility>
#include <source_location>

export module SimulationBindings;

import BusinessLogic.ApplicationFacade;

import Driver.PlatformFactory;

import Driver.PulseCounterDriver;
import Driver.KeyboardDriver;
import Driver.DisplayDriver;
import Driver.LightSensorDriver;
import Driver.BrightnessDriver;
import Driver.UartDriver;
import Driver.SdCardDriver;

import Driver.KeyState;
import Driver.KeyId;
import Driver.UartId;
import Driver.PulseCounterId;

import Simulation.PulseCounterScheduler;

static Driver::LightSensorDriver lightSensor;
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
    .lightSensor = lightSensor,
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

constexpr size_t PULSE_COUNTER_COUNT = 4U;
Simulation::PulseCounterScheduler pulseScheduler;

extern "C"
{

    void LibWrapper_Init()
    {
        if (!facade.init())
        {
            std::println(stderr, "ERROR {} failed!",
                         std::source_location::current().function_name());
        }
        else
        {
            std::println(stdout, "{}", std::source_location::current().function_name());
        }
    }

    void LibWrapper_Start()
    {
        if (!facade.start())
        {
            std::println(stderr, "ERROR {} failed!",
                         std::source_location::current().function_name());
        }
        else
        {
            std::println(stdout, "{}", std::source_location::current().function_name());
        }
    }

    void LibWrapper_Stop()
    {
        if (!facade.stop())
        {
            std::println(stderr, "ERROR {} failed!",
                         std::source_location::current().function_name());
        }
        else
        {
            std::println(stdout, "{}", std::source_location::current().function_name());
        }
    }

    void LibWrapper_Tick()
    {
        if (!facade.tick())
        {
#warning check what is the problem, dont pollute main log for now
            /*  std::println(stderr,
                           "ERROR {} failed!",
                           std::source_location::current().function_name());
                           */
        }
    }

    void LibWrapper_TimeSlot()
    {
        facade.onTimeSlot();
    }

    void LibWrapper_KeyPressed(Driver::KeyId keyId)
    {
        auto &keyboard = static_cast<Driver::KeyboardDriver &>(platform.keyboard);
        keyboard.setKeyState(static_cast<Driver::KeyId>(keyId),
                             Driver::KeyState::Pressed);

        std::println(stdout, "{}", std::source_location::current().function_name());
    }

    void LibWrapper_KeyReleased(Driver::KeyId keyId)
    {
        auto &keyboard = static_cast<Driver::KeyboardDriver &>(platform.keyboard);
        keyboard.setKeyState(static_cast<Driver::KeyId>(keyId),
                             Driver::KeyState::NotPressed);

        std::println(stdout, "{}", std::source_location::current().function_name());
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
        // const auto &display = static_cast<Driver::DisplayDriver &>(platform.display);
        // value = display.getPixelValue(xPosition, yPosition);
        return value;
    }

    bool LibWrapper_UpdatePulseCounterFrequency(std::uint8_t pulseCounterId,
                                                std::uint32_t newPulsesPerMinute)
    {
        bool status = false;

        if (pulseCounterId < PULSE_COUNTER_COUNT)
        {

            std::println(stderr, "F CALLED {} {} {}",
                         std::source_location::current().function_name(), pulseCounterId, newPulsesPerMinute);

            status = pulseScheduler.updateFrequency(pulseCounterId, newPulsesPerMinute);
        }
        else
        {
            std::println(stderr, "ERROR {} failed!",
                         std::source_location::current().function_name());
        }

        return status;
    }
}
