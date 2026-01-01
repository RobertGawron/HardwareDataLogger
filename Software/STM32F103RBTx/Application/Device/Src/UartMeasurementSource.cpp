#include "Device/Inc/UartMeasurementSource.hpp"

#include "Device/Interface/IMeasurementSource.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Driver/Interface/IUartDriver.hpp"

#include <cstdint>

namespace Device
{

    UartMeasurementSource::UartMeasurementSource(MeasurementDeviceId _deviceId, Driver::IUartDriver &_driver)
        : deviceId(_deviceId),
          driver(_driver)
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
        const std::uint16_t dummyData = 5U;

        const MeasurementType measurement{
            .data = dummyData,
            .source = deviceId};

        return measurement;
    }
}
