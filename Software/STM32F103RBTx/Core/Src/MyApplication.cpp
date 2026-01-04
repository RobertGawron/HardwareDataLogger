module;

#include "MyApplication.hpp"

#include "stm32f1xx_hal.h"       // 1. Base HAL FIRST (includes hal_def.h internally)
#include "stm32f1xx_hal_dma.h"   // 2. DMA second
#include "stm32f1xx_hal_usart.h" // 3. UART (depends on DMA)
#include "stm32f1xx_hal_adc.h"   // 4. ADC (depends on DMA)
#include "stm32f1xx_hal_tim.h"   // 5. TIM (depends on DMA)

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
/*
// HAL handles from main
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef husart3;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim3;
*/
// Static concrete driver instances
static Driver::LightSensorDriver LightSensor{hadc1};
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

static BusinessLogic::ApplicationFacade facade{platform};

// C linkage functions
extern "C"
{

    void app_init()
    {
        facade.init();
    }

    void app_start()
    {
        facade.start();
    }

    void app_tick()
    {
        facade.tick();
    }

} // extern "C"