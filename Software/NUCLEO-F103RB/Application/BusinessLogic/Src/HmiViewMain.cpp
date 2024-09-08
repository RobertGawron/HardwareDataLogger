#include "BusinessLogic/Inc/HmiViewMain.hpp"

namespace BusinessLogic
{

    HmiViewMain::HmiViewMain(Driver::IDisplayDriver &_displayDriver)
        : displayDriver(_displayDriver)
    {
    }

    void HmiViewMain::updateDisplay(const HmiDataModel &model)
    {
    }

    void HmiViewMain::init()
    {
    }

}
