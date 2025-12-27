
#include "PlatformFactory.hpp"
/*#include "PlatformFactory.hpp"
#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal_conf.h"
#include "stm32f1xx.h"
#include "stm32f1xx_hal_def.h"

// stm32f1xx.h:254
*/
#include "Driver/Hardware/Inc/AmbientLightSensorDriver.hpp"
#include "Driver/Hardware/Inc/St7735DisplayBrightnessDriver.hpp"
#include "Driver/Hardware/Inc/St7735DisplayDriver.hpp"
#include "Driver/Hardware/Inc/KeyboardFourPushButtonsDriver.hpp"
#include "Driver/Hardware/Inc/UartDriver.hpp"
#include "Driver/Hardware/Inc/SdCardDriver.hpp"
#include "Driver/Hardware/Inc/PulseCounterDriver.hpp"

// #include "stm32f1xx_hal_conf.h"
#include "stm32f1xx_hal_def.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_tim.h"

// I'm not sure if it should be here.
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef husart3;

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim3;

namespace BusinessLogic
{

    Driver::IAmbientLightSensorDriver &PlatformFactory::getAmbientLightSensorDriver()
    {
        static Driver::AmbientLightSensorDriver driver{hadc1};
        return driver;
    }

    Driver::IDisplayBrightnessDriver &PlatformFactory::getDisplayBrightnessDriver()
    {
        static Driver::St7735DisplayBrightnessDriver driver{htim3};
        return driver;
    }

    Driver::IDisplayDriver &PlatformFactory::getDisplayDriver()
    {
        static Driver::St7735DisplayDriver driver;
        return driver;
    }

    Driver::IKeyboardDriver &PlatformFactory::getKeyboardDriver()
    {
        static Driver::KeyboardFourPushButtonsDriver driver;
        return driver;
    }

    Driver::IUartDriver &PlatformFactory::getUartDriver(const Driver::UartId id)
    {
        // hack
        static Driver::UartDriver driver1(huart1);
        static Driver::UartDriver driver2(huart2);
        static Driver::UartDriver driver3(husart3);

        switch (id)
        {
        case Driver::UartId::MEASUREMENT_RECEIVER:
            return driver3;
            break;
        case Driver::UartId::TRANSMIT_VIA_USB:
            return driver2;
            break;
        case Driver::UartId::TRANSMIT_VIA_WIFI:
            return driver1;
            break;
        }

        return driver1; // tmp
    }

    Driver::ISdCardDriver &PlatformFactory::getSdCardDriver()
    {
        static Driver::SdCardDriver driver;
        return driver;
    }

    Driver::IPulseCounterDriver &PlatformFactory::getPulseCounterDriver(const Driver::PulseCounterId id)
    {
        // TODO
        static Driver::PulseCounterDriver driver(id);
        return driver;
    }
}
