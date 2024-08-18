#include "HMI.hpp"

namespace BusinessLogic
{

    HMI::HMI(
        Device::DisplayBacklight &_displayBacklight,
        Device::Keyboard &_keyboard,
        Device::IDisplay &_display) : displayBacklight(_displayBacklight),
                                      keyboard(_keyboard),
                                      display(_display),
                                      displayBrightnessActual(0)

    {
    }

    void HMI::init()
    {
    }

    void HMI::tick()
    {

        auto upState = keyboard.getState(::Driver::KeyboardKeyId::Up);
        auto downState = keyboard.getState(::Driver::KeyboardKeyId::Down);

        auto displayBrightnessActual = displayBacklight.getBrightnessPercentage();
        if (upState == Device::KeyboardKeyActionState::PressEndShort)
        {
            displayBrightnessActual -= 10;
            displayBacklight.setBrightnessPercentage(displayBrightnessActual);
        }
        /*     if (downState == Device::KeyboardKeyActionState::PressEndShort)
             {
                 displayBrightnessActual--;
                 displayBacklight.setBrightnessPercentage(displayBrightnessActual);
             }
*/
    }

}
