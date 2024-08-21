#include "PulseCounterMeasurementSource.hpp"

namespace Device
{

    PulseCounterMeasurementSource::PulseCounterMeasurementSource(Driver::IPulseCounterDriver &_pulseCounterDriver)
        : pulseCounterDriver(_pulseCounterDriver)
    {
    }

    bool PulseCounterMeasurementSource::init()
    {
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
