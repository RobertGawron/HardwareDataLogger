#ifndef MAIN_H_
#define MAIN_H_

#include <cstdint>

// Mock definitions for GPIO_TypeDef and GPIO-related functions

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

#define KEY_LEFT_Pin 1u
#define KEY_LEFT_GPIO_Port &portPinLeft
#define KEY_RIGHT_Pin 2u
#define KEY_RIGHT_GPIO_Port &portPinRight
#define KEY_UP_Pin 3u
#define KEY_UP_GPIO_Port &portPinUp
#define KEY_DOWN_Pin 4u
#define KEY_DOWN_GPIO_Port &portPinDown

#endif // MAIN_H_
