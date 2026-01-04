module;

#include <cstdint>

module Device.UartSource;

import Device.MeasurementSource;
import Device.MeasurementType;
import Device.MeasurementDeviceId;

import Driver.UartDriver;

namespace Device
{
    UartSource::UartSource(
        const MeasurementDeviceId deviceId,
        Driver::UartDriver &driver) noexcept
        : deviceId(deviceId),
          driver(driver)
    {
    }

    auto UartSource::onInit() noexcept -> bool
    {
        // return driver.init();

        return true;
    }

    auto UartSource::onStart() noexcept -> bool
    {
        // return driver.start();
        return true;
    }

    auto UartSource::onStop() noexcept -> bool
    {
        //  return driver.stop();
        return true;
    }

    auto UartSource::isMeasurementAvailable() const noexcept -> bool
    {
        return true;
    }

    auto UartSource::getMeasurement() noexcept -> MeasurementType
    {
        constexpr std::uint16_t DUMMY_DATA = 5U;

        return MeasurementType{
            .source = deviceId,
            .data = DUMMY_DATA};
    }
}