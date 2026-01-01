#include "Device/Inc/PulseCounterMeasurementSource.hpp"

#include "Device/Interface/IMeasurementSource.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Driver/Interface/IPulseCounterDriver.hpp"

namespace Device
{

    bool PulseCounterMeasurementSource::initialize() noexcept
    {
        return pulseCounterDriver.initialize();
    }

    bool PulseCounterMeasurementSource::start() noexcept
    {
        return pulseCounterDriver.start();
    }

    bool PulseCounterMeasurementSource::stop() noexcept
    {
        return pulseCounterDriver.stop();
    }

    bool PulseCounterMeasurementSource::isMeasurementAvailable() const noexcept
    {
        return true;
    }

    MeasurementType PulseCounterMeasurementSource::getMeasurement() noexcept
    {
        return MeasurementType{
            .source = deviceId,
            .data = pulseCounterDriver.getMeasurement()};
    }
}