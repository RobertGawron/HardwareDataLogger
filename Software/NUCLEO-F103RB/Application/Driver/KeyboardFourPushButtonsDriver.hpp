#ifndef DRIVER_KeyboardFourPushButtonsDriver_H_
#define DRIVER_KeyboardFourPushButtonsDriver_H_

#include "IKeyboardDriver.hpp"
#include "stm32f1xx_hal.h"

namespace Driver
{
    /// @brief periodically reads state of the keys via GPIO
    class KeyboardFourPushButtonsDriver : public IKeyboardDriver
    {
    public:
        KeyboardFourPushButtonsDriver() = default;
        virtual ~KeyboardFourPushButtonsDriver() = default;

        virtual bool init();
        virtual void tick();
        virtual KeyboardKeyState getState(const KeyboardKeyId key) const;

    private:
        Driver::KeyboardKeyState getKeyState(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

        KeyboardKeyState keyUp = Driver::KeyboardKeyState::NotPressed;
        KeyboardKeyState keyDown = Driver::KeyboardKeyState::NotPressed;
        KeyboardKeyState keyLeft = Driver::KeyboardKeyState::NotPressed;
        KeyboardKeyState keyRight = Driver::KeyboardKeyState::NotPressed;
    };

}

#endif
