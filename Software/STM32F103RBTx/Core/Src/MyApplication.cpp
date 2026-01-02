#include "MyApplication.hpp"
#include "PlatformFactory.hpp"
#include "BusinessLogic/Inc/ApplicationFacade.hpp"

#include "Driver/Hardware/Inc/LightSensorDriver.hpp"
#include "Driver/Hardware/Inc/BrightnessDriver.hpp"
#include "Driver/Hardware/Inc/DisplayDriver.hpp"
#include "Driver/Hardware/Inc/KeyboardDriver.hpp"
#include "Driver/Hardware/Inc/UartDriver.hpp"
#include "Driver/Hardware/Inc/SdCardDriver.hpp"
#include "Driver/Hardware/Inc/PulseCounterDriver.hpp"

#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_tim.h"

#include <optional>

// HAL handles from main
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef husart3;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim3;

// Static concrete driver instances
static Driver::LightSensorDriver LightSensor{hadc1};
static Driver::BrightnessDriver displayBrightness{htim3};
static Driver::DisplayDriver display;
static Driver::KeyboardDriver keyboard;

// UART drivers
static Driver::UartDriver wifiUart{huart1};
static Driver::UartDriver usbUart{huart2};
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

BusinessLogic::ApplicationFacade facade{platform};

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
