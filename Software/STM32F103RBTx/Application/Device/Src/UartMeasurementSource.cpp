#include "Device/Inc/UartMeasurementSource.hpp"

#include "Device/Interface/IMeasurementSource.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Driver/Interface/IUartDriver.hpp"

#include <cstdint>

namespace Device
{
    UartMeasurementSource::UartMeasurementSource(
        const MeasurementDeviceId deviceId,
        Driver::IUartDriver &driver) noexcept
        : deviceId(deviceId),
          driver(driver)
    {
    }

    bool UartMeasurementSource::initialize() noexcept
    {
        return driver.initialize();
    }

    bool UartMeasurementSource::start() noexcept
    {
        return true;
    }

    bool UartMeasurementSource::stop() noexcept
    {
        return true;
    }

    bool UartMeasurementSource::isMeasurementAvailable() const noexcept
    {
        return true;
    }

    MeasurementType UartMeasurementSource::getMeasurement() noexcept
    {
        constexpr std::uint16_t DUMMY_DATA = 5U;

        return MeasurementType{
            .source = deviceId,
            .data = DUMMY_DATA};
    }
}