#include "KeyboardKeysDriver.h"
#include "stm32f1xx_hal.h"
#include "main.h"

namespace Driver
{

KeyboardKeysDriver::KeyboardKeysDriver() :
    keyUp(::Driver::KeboardKeyState::NotPressed), keyDown(
    		::Driver::KeboardKeyState::NotPressed), keyLeft(
    				::Driver::KeboardKeyState::NotPressed), keyRight(
    						::Driver::KeboardKeyState::NotPressed)
{
}

void KeyboardKeysDriver::init()
{
}

void KeyboardKeysDriver::tick()
{
    // TODO move it to driver
    keyUp = (HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin) == GPIO_PIN_SET) ?
            KeboardKeyState::NotPressed : KeboardKeyState::Pressed;
    keyDown =
        (HAL_GPIO_ReadPin(KEY_DOWN_GPIO_Port, KEY_DOWN_Pin) == GPIO_PIN_SET) ?
        KeboardKeyState::NotPressed : KeboardKeyState::Pressed;
    keyLeft =
        (HAL_GPIO_ReadPin(KEY_LEFT_GPIO_Port, KEY_LEFT_Pin) == GPIO_PIN_SET) ?
        KeboardKeyState::NotPressed : KeboardKeyState::Pressed;
    keyRight =
        (HAL_GPIO_ReadPin(KEY_RIGHT_GPIO_Port, KEY_RIGHT_Pin)
         == GPIO_PIN_SET) ?
        KeboardKeyState::NotPressed : KeboardKeyState::Pressed;

}

KeboardKeyState KeyboardKeysDriver::getState(KeboardKeyId key)
{
    KeboardKeyState state;

    switch(key)
    {
    case KeboardKeyId::Up:
        state = keyUp;
        break;
    case KeboardKeyId::Down:
        state = keyDown;
        break;
    case KeboardKeyId::Left:
        state = keyLeft;
        break;
    case KeboardKeyId::Right:
        state = keyRight;
        break;
    }

    return state;
}

}
