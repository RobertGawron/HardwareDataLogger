#include "PlatformFactoryStm32.hpp"

#include "Driver/Inc/AmbientLightSensorDriver.hpp"
#include "Driver/Inc/St7735DisplayBrightnessDriver.hpp"
#include "Driver/Inc/St7735DisplayDriver.hpp"
#include "Driver/Inc/KeyboardFourPushButtonsDriver.hpp"
#include "Driver/Inc/UartDriver.hpp"
#include "Driver/Inc/SdCardDriver.hpp"
#include "Driver/Inc/PulseCounterDriver.hpp"

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_tim.h"

// I'm not sure if it should be here.
extern UART_HandleTypeDef huart3;
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim3;

namespace BusinessLogic
{

    Driver::IAmbientLightSensorDriver &PlatformFactoryStm32::createAmbientLightSensorDriver()
    {
        static Driver::AmbientLightSensorDriver driver{hadc1};
        return driver;
    }

    Driver::IDisplayBrightnessDriver &PlatformFactoryStm32::createDisplayBrightnessDriver()
    {
        static Driver::St7735DisplayBrightnessDriver driver{htim3};
        return driver;
    }

    Driver::IDisplayDriver &PlatformFactoryStm32::createDisplayDriver()
    {
        static Driver::St7735DisplayDriver driver;
        return driver;
    }

    Driver::IKeyboardDriver &PlatformFactoryStm32::createKeyboardDriver()
    {
        static Driver::KeyboardFourPushButtonsDriver driver;
        return driver;
    }

    Driver::IUartDriver &PlatformFactoryStm32::createUartDriver(const Driver::UartIdentifier id)
    {
        // TODO
        static Driver::UartDriver driver{huart3};
        return driver;
    }

    Driver::ISdCardDriver &PlatformFactoryStm32::createSdCardDriver()
    {
        static Driver::SdCardDriver driver;
        return driver;
    }

    Driver::IPulseCounterDriver &PlatformFactoryStm32::createPulseCounterDriver(const Driver::PulseCounterIdentifier id)
    {
        // TODO
        static Driver::PulseCounterDriver driver;
        return driver;
    }
}
