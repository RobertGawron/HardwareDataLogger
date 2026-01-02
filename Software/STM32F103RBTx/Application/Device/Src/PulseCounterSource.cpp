#include "Device/Inc/PulseCounterSource.hpp"

#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "PulseCounterDriver.hpp"

namespace Device
{

    bool PulseCounterSource::onInit() noexcept
    {
        return pulseCounterDriver.init();
    }

    bool PulseCounterSource::onStart() noexcept
    {
        return pulseCounterDriver.start();
    }

    bool PulseCounterSource::onStop() noexcept
    {
        return pulseCounterDriver.stop();
    }

    bool PulseCounterSource::isMeasurementAvailable() const noexcept
    {
        return true;
    }

    MeasurementType PulseCounterSource::getMeasurement() noexcept
    {
        return MeasurementType{
            .source = deviceId,
            .data = pulseCounterDriver.getMeasurement()};
    }
}