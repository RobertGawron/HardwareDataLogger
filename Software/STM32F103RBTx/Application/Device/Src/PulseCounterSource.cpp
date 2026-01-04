module Device.PulseCounterSource;

import Device.MeasurementType;
import Device.MeasurementDeviceId;

import Driver.PulseCounterDriver;

namespace Device
{

    auto PulseCounterSource::onInit() noexcept -> bool
    {
        return pulseCounterDriver.init();
    }

    auto PulseCounterSource::onStart() noexcept -> bool
    {
        return pulseCounterDriver.start();
    }

    auto PulseCounterSource::onStop() noexcept -> bool
    {
        return pulseCounterDriver.stop();
    }

    auto PulseCounterSource::isMeasurementAvailable() const noexcept -> bool
    {
        return true;
    }

    auto PulseCounterSource::getMeasurement() noexcept -> MeasurementType
    {
        return MeasurementType{
            .source = deviceId,
            .data = pulseCounterDriver.getMeasurement()};
    }
}