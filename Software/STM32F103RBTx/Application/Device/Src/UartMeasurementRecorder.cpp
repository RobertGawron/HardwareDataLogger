#include "Device/Inc/UartMeasurementRecorder.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"

namespace Device
{

    UartMeasurementRecorder::UartMeasurementRecorder(Driver::IUartDriver &_driver) : driver(_driver)
    {
    }

    void UartMeasurementRecorder::write()
    {
    }

    void UartMeasurementRecorder::flush()
    {
    }

    void UartMeasurementRecorder::notify()
    {
    }

}
