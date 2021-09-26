#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "IKeyboardKeysDriver.h"
#include "KeboardKeyState.h"
#include "KeboardKeyId.h"

namespace Device
{

class Keyboard
{
public:
    Keyboard(::Driver::IKeyboardKeysDriver& keyboardKeysDriver);
    virtual ~Keyboard() = default;

    void init();
    void tick();
    ::Driver::KeboardKeyState getState(::Driver::KeboardKeyId key);

private:
    ::Driver::IKeyboardKeysDriver& keyboardKeysDriver;

    ::Driver::KeboardKeyState keyUp;
    ::Driver::KeboardKeyState keyDown;
    ::Driver::KeboardKeyState keyLeft;
    ::Driver::KeboardKeyState keyRight;
};

}

#endif
