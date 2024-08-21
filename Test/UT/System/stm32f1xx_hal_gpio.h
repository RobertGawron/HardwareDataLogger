#ifndef stm32f1xx_hal_gpio_h
#define stm32f1xx_hal_gpio_h

#include <gmock/gmock.h>
#include <stdint.h>
#include "main.h"

// Mock class for HAL functions
class MockHAL
{
public:
    MOCK_METHOD(GPIO_PinState, HAL_GPIO_ReadPin, (GPIO_TypeDef * GPIOx, uint16_t GPIO_Pin), ());
};

// Global pointer to the MockHAL instance, which will be set in the tests
extern MockHAL *mockHAL;

// Mock function to replace HAL_GPIO_ReadPin
inline GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    return mockHAL->HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

#endif
