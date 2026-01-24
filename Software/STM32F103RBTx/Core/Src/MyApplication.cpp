module;

#include "MyApplication.hpp"

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_dma.h"
#include "stm32f1xx_hal_usart.h"
#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_tim.h"

#include "main.h"

export module MyApplication;

import BusinessLogic.ApplicationFacade;
import Driver.PlatformFactory;

import Driver.DisplayDriver;
import Driver.PulseCounterId;

import Driver.LightSensorDriver;
import Driver.BrightnessDriver;
import Device.DisplayPixelColor;
import Driver.KeyboardDriver;
import Driver.UartDriver;
import Driver.SdCardDriver;
import Driver.PulseCounterDriver;

// Static concrete driver instances
static Driver::LightSensorDriver lightSensor{hadc1};
static Driver::BrightnessDriver displayBrightness{htim3};
static Driver::DisplayDriver display;
static Driver::KeyboardDriver keyboard;

// UART drivers
static Driver::UartDriver wifiUart{husart1};
static Driver::UartDriver usbUart{husart2};
static Driver::UartDriver measurementUart{husart3};

// Storage driver
static Driver::SdCardDriver sdCard;

// Pulse counters
static Driver::PulseCounterDriver counter1{Driver::PulseCounterId::bncA};
static Driver::PulseCounterDriver counter2{Driver::PulseCounterId::bncB};
static Driver::PulseCounterDriver counter3{Driver::PulseCounterId::bncC};
static Driver::PulseCounterDriver counter4{Driver::PulseCounterId::bncD};

// Global platform drivers instance
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

static BusinessLogic::ApplicationFacade facade{platform};

extern "C"
{

    bool app_init()
    {
        return facade.init();
    }

    bool app_start()
    {
        return facade.start();
    }

    bool app_tick()
    {
        return facade.tick();
    }

    void app_timeSlotIsr()
    {
        facade.onTimeSlot();
    }

} // extern "C"