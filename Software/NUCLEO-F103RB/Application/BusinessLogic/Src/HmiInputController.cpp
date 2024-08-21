#include "HmiInputController.hpp"

namespace BusinessLogic
{

    HmiInputController::HmiInputController(Device::IKeyboard &_keyboard)
        : keyboard(_keyboard)
    {
    }

    bool HmiInputController::initialize()
    {
        keyboard.init();

        return true;
    }

    bool HmiInputController::start()
    {

        return true;
    }

    bool HmiInputController::stop()
    {
        return true;
    }

    bool HmiInputController::tick()
    {
        keyboard.tick();
        auto x = keyboard.getKeyState(Driver::KeyboardKeyIdentifier::Down);
        return true;
    }
}
