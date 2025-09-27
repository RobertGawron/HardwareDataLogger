#ifndef stm32f1xx_hal_gpio_h
#define stm32f1xx_hal_gpio_h

#include <gmock/gmock.h>
#include <stdint.h>

#include "stm32f1xx_hal_def.h"

struct GPIO_TypeDef
{
    std::uint32_t ID; // Simple identifier, just to make the struct non-empty
};

enum GPIO_PinState : std::uint8_t
{
    GPIO_PIN_RESET = 0,
    GPIO_PIN_SET
};

extern GPIO_TypeDef portPinLeft;
extern GPIO_TypeDef portPinRight;
extern GPIO_TypeDef portPinUp;
extern GPIO_TypeDef portPinDown;

// Mock class for HAL functions
class MockHAL_GPIO
{
public:
    MOCK_METHOD(GPIO_PinState, HAL_GPIO_ReadPin, (GPIO_TypeDef * GPIOx, std::uint16_t GPIO_Pin), ());
};

// Global pointer to the MockHAL instance, which will be set in the tests
extern MockHAL_GPIO *mockHAL_GPIO;

// Mock function to replace HAL_GPIO_ReadPin
inline GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, std::uint16_t GPIO_Pin)
{
    return mockHAL_GPIO->HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
}

#endif
