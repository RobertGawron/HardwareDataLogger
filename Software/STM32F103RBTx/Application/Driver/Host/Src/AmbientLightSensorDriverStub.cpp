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

    std::uint32_t AmbientLightSensorDriverStub::getAmbientLightLevel() const
    {
        std::uint32_t adcResult = 10;

        return adcResult;
    }

}
