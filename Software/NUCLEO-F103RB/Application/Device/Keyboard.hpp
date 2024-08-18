#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "IKeyboardDriver.hpp"
#include "KeyboardKeyActionState.hpp"
#include "KeyboardKeyId.hpp"

#include <stdint.h>

namespace Device
{
    /// @brief responsible for debouncing and detecting long/short key press
    class Keyboard
    {
    public:
        Keyboard(Driver::IKeyboardDriver &keyboardDriver);
        virtual ~Keyboard() = default;

        void init();
        void tick();
        KeyboardKeyActionState getState(Driver::KeyboardKeyId key);

    private:
        Driver::IKeyboardDriver &keyboardDriver;

        static const uint8_t AmountOfKeys = static_cast<uint8_t>(Driver::KeyboardKeyId::LastNotUsed);
        KeyboardKeyActionState keyActionState[AmountOfKeys];
    };

}

#endif
