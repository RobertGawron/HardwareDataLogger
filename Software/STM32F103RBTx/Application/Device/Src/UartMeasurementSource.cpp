#include "Device/Inc/UartMeasurementSource.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"

namespace Device
{

    UartMeasurementSource::UartMeasurementSource(Driver::IUartDriver &_driver) : driver(_driver)
    {
    }

    bool UartMeasurementSource::init()
    {
        const bool status = driver.initialize();
        return status;
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
