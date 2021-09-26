#ifndef DRIVER_KEYBOARDKEYSDRIVER_H_
#define DRIVER_KEYBOARDKEYSDRIVER_H_

#include "IKeyboardKeysDriver.h"

namespace Driver
{

class KeyboardKeysDriver : public IKeyboardKeysDriver
{
public:
	KeyboardKeysDriver();
    virtual ~KeyboardKeysDriver() = default;

    virtual void init();
    virtual void tick();
    virtual KeboardKeyState getState(KeboardKeyId key);

private:
    KeboardKeyState keyUp;
    KeboardKeyState keyDown;
    KeboardKeyState keyLeft;
    KeboardKeyState keyRight;
};

}



#endif
