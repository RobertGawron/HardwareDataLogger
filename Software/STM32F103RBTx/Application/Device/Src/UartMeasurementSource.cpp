#include "Device/Inc/UartMeasurementSource.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"

#include <cstdint>

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
        const std::uint16_t dummyData = 5u;

        MeasurementType m;
        m.source = MeasurementDeviceId::DEVICE_PULSE_COUNTER_1;
        m.data = dummyData;

        return m;
    }
}
