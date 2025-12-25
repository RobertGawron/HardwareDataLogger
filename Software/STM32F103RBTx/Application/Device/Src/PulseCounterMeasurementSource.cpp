#include "Device/Inc/PulseCounterMeasurementSource.hpp"

#include "Device/Interface/IMeasurementSource.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Driver/Interface/IPulseCounterDriver.hpp"

// #include <stdio.h>

namespace Device
{

    PulseCounterMeasurementSource::PulseCounterMeasurementSource(MeasurementDeviceId id, Driver::IPulseCounterDriver &_pulseCounterDriver)
        : IMeasurementSource(id),
          pulseCounterDriver(_pulseCounterDriver)
    {
    }

    bool PulseCounterMeasurementSource::initialize()
    {
        const bool status = pulseCounterDriver.initialize();
        return status;
    }

    bool PulseCounterMeasurementSource::start()
    {
        const bool status = pulseCounterDriver.start();
        return status;
    }

    bool PulseCounterMeasurementSource::stop()
    {
        const bool status = pulseCounterDriver.stop();
        return status;
    }

    bool PulseCounterMeasurementSource::isMeasurementAvailable()
    {
        return true;
    }

    MeasurementType PulseCounterMeasurementSource::getMeasurement()
    {
        MeasurementType measurement{
            .data = pulseCounterDriver.getMeasurement(),
            .source = getMyId()};

        return measurement;
    }

}
