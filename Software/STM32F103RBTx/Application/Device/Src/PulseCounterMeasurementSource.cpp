#include "Device/Inc/PulseCounterMeasurementSource.hpp"
#include "Driver/Interfaces/IPulseCounterDriver.hpp"

namespace Device
{

    PulseCounterMeasurementSource::PulseCounterMeasurementSource(Driver::IPulseCounterDriver &_pulseCounterDriver)
        : pulseCounterDriver(_pulseCounterDriver)
    {
    }

    bool PulseCounterMeasurementSource::init()
    {
        pulseCounterDriver.initialize();
        return true;
    }

    bool PulseCounterMeasurementSource::deinit()
    {
        return true;
    }

    bool PulseCounterMeasurementSource::isMeasurementAvailable()
    {
        return true;
    }

    void PulseCounterMeasurementSource::getMeasurement()
    {
    }

}
