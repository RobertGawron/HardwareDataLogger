#include "Device/Inc/UartMeasurementRecorder.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"

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
