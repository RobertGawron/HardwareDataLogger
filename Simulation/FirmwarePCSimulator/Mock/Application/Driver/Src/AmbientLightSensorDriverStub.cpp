#include "AmbientLightSensorDriverStub.hpp"

namespace Driver
{

    bool AmbientLightSensorDriverStub::onInitialize()
    {
        return true;
    }

    bool AmbientLightSensorDriverStub::onStart()
    {
        return true;
    }

    bool AmbientLightSensorDriverStub::onStop()
    {
        return true;
    }

    bool AmbientLightSensorDriverStub::onReset()
    {
        return true;
    }

    uint32_t AmbientLightSensorDriverStub::getAmbientLightLevel() const
    {
        volatile uint32_t adcResult;

        return adcResult;
    }

}
