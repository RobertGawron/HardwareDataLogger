#include "BusinessLogic/Inc/HmiViewHistogram.hpp"

namespace BusinessLogic
{
    HmiViewHistogram::HmiViewHistogram(Driver::IDisplayDriver &_displayDriver)
        : displayDriver(_displayDriver)
    {
    }

    void HmiViewHistogram::updateDisplay(const HmiDataModel &model)
    {
    }

    void HmiViewHistogram::init()
    {
    }
}
