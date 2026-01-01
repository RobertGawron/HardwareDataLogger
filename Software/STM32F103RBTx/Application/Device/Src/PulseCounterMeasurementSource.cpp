#include "Device/Inc/PulseCounterMeasurementSource.hpp"

#include "Device/Interface/IMeasurementSource.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Driver/Interface/IPulseCounterDriver.hpp"

namespace Device
{

    PulseCounterMeasurementSource::PulseCounterMeasurementSource(MeasurementDeviceId _deviceId, Driver::IPulseCounterDriver &_pulseCounterDriver)
        : deviceId(_deviceId),
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
        const MeasurementType measurement{
            .data = pulseCounterDriver.getMeasurement(),
            .source = deviceId};

        return measurement;
    }

}
