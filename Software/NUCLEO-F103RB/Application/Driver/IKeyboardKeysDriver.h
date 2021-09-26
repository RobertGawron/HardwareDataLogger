#ifndef DRIVER_IKEYBOARDKEYSDRIVER_H_
#define DRIVER_IKEYBOARDKEYSDRIVER_H_

#include "KeboardKeyState.h"
#include "KeboardKeyId.h"

namespace Driver
{

class IKeyboardKeysDriver
{
public:
    virtual ~IKeyboardKeysDriver() = default;

    virtual void init() = 0;
    virtual void tick() = 0;
    virtual KeboardKeyState getState(KeboardKeyId key) = 0;
};

}

#endif
