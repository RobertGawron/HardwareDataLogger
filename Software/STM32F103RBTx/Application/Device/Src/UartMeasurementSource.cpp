#include "Device/Inc/UartMeasurementSource.hpp"

namespace Device
{

    UartMeasurementSource::UartMeasurementSource(Driver::IUartDriver &_driver) : driver(_driver)
    {
    }

    bool UartMeasurementSource::init()
    {
        return true;
    }

    bool UartMeasurementSource::deinit()
    {
        return true;
    }

    bool UartMeasurementSource::isMeasurementAvailable()
    {
        return true;
    }

    void UartMeasurementSource::getMeasurement()
    {
    }
}
