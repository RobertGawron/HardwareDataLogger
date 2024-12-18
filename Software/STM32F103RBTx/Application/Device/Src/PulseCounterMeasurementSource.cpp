#include "Device/Inc/PulseCounterMeasurementSource.hpp"
#include "Device/Inc/MeasurementType.hpp"
#include "Driver/Interfaces/IPulseCounterDriver.hpp"

namespace Device
{

    PulseCounterMeasurementSource::PulseCounterMeasurementSource(Driver::IPulseCounterDriver &_pulseCounterDriver)
        : pulseCounterDriver(_pulseCounterDriver)
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
        return pulseCounterDriver.getMeasurement();
    }

}
