#include "Device/Inc/UartMeasurementSource.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"

namespace Device
{

    UartMeasurementSource::UartMeasurementSource(Driver::IUartDriver &_driver) : driver(_driver)
    {
    }

    bool UartMeasurementSource::initialize()
    {
        const bool status = driver.initialize();
        return status;
    }

    bool UartMeasurementSource::start()
    {
        return true;
    }

    bool UartMeasurementSource::stop()
    {
        return true;
    }

    bool UartMeasurementSource::isMeasurementAvailable()
    {
        return true;
    }

    MeasurementType UartMeasurementSource::getMeasurement()
    {
        return (std::uint8_t)5;
    }
}
