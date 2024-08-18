#include "KeyboardFourPushButtonsDriver.hpp"
#include "main.h"

namespace Driver
{

    bool KeyboardFourPushButtonsDriver::init()
    {
        return true;
    }

    void KeyboardFourPushButtonsDriver::tick()
    {
        keyUp = getKeyState(KEY_UP_GPIO_Port, KEY_UP_Pin);
        keyDown = getKeyState(KEY_DOWN_GPIO_Port, KEY_DOWN_Pin);
        keyLeft = getKeyState(KEY_LEFT_GPIO_Port, KEY_LEFT_Pin);
        keyRight = getKeyState(KEY_RIGHT_GPIO_Port, KEY_RIGHT_Pin);
    }

    KeyboardKeyState KeyboardFourPushButtonsDriver::getState(const KeyboardKeyId key) const
    {
        KeyboardKeyState state;

        switch (key)
        {
        case KeyboardKeyId::Up:
            state = keyUp;
            break;
        case KeyboardKeyId::Down:
            state = keyDown;
            break;
        case KeyboardKeyId::Left:
            state = keyLeft;
            break;
        case KeyboardKeyId::Right:
            state = keyRight;
            break;
        }

        return state;
    }

    Driver::KeyboardKeyState KeyboardFourPushButtonsDriver::getKeyState(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
    {
        KeyboardKeyState state;

        if (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) != GPIO_PIN_SET)
        {
            state = KeyboardKeyState::Pressed;
        }
        else
        {
            state = KeyboardKeyState::NotPressed;
        }

        return state;
    }
}
