#include "Device/Inc/UartSource.hpp"

#include "Device/Inc/MeasurementSource.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "UartDriver.hpp"

#include <cstdint>

namespace Device
{
    UartSource::UartSource(
        const MeasurementDeviceId deviceId,
        Driver::UartDriver &driver) noexcept
        : deviceId(deviceId),
          driver(driver)
    {
    }

    bool UartSource::onInit() noexcept
    {
        // return driver.init();

        return true;
    }

    bool UartSource::onStart() noexcept
    {
        // return driver.start();
        return true;
    }

    bool UartSource::onStop() noexcept
    {
        //  return driver.stop();
        return true;
    }

    bool UartSource::isMeasurementAvailable() const noexcept
    {
        return true;
    }

    MeasurementType UartSource::getMeasurement() noexcept
    {
        constexpr std::uint16_t DUMMY_DATA = 5U;

        return MeasurementType{
            .source = deviceId,
            .data = DUMMY_DATA};
    }
}