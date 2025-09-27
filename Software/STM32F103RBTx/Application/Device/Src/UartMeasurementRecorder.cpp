#include "Device/Inc/UartMeasurementRecorder.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Driver/Interface/IUartDriver.hpp"

#include <cstring>
// #include <array>
//  #include <iostream>

namespace Device
{

    UartMeasurementRecorder::UartMeasurementRecorder(Driver::IUartDriver &_driver) : driver(_driver)
    {
    }

    bool UartMeasurementRecorder::flush()
    {
        return true;
    }

    bool UartMeasurementRecorder::notify(Device::MeasurementType &measurement)
    {
        (void)measurement; // Explicitly suppresses "unused parameter" warning

        return true;
    }

}
