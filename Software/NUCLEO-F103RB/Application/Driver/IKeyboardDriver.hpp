#ifndef DRIVER_IKEYBOARDKEYSDRIVER_H_
#define DRIVER_IKEYBOARDKEYSDRIVER_H_

#include "KeyboardKeyState.hpp"
#include "KeyboardKeyId.hpp"

namespace Driver
{
    /// @brief four push buttons keyboard
    class IKeyboardDriver
    {
    public:
        virtual ~IKeyboardDriver() = default;

        virtual bool init() = 0;
        virtual void tick() = 0;
        virtual KeyboardKeyState getState(const KeyboardKeyId key) const = 0;
    };

}

#endif
