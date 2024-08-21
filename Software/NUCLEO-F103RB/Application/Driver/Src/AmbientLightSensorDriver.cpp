#include "AmbientLightSensorDriver.hpp"

// declare a buffer to hold ADC values
static const uint8_t AdcBufferSize{10};
uint32_t adcBuffer[AdcBufferSize];

namespace Driver
{
    AmbientLightSensorDriver::AmbientLightSensorDriver(ADC_HandleTypeDef &_hadc) : hadc(_hadc)
    {
    }

    bool AmbientLightSensorDriver::onInitialize()
    {
        return true;
    }

    bool AmbientLightSensorDriver::onStart()
    {
        const bool status = startAdcWithDma();

        return status;
    }

    bool AmbientLightSensorDriver::onStop()
    {
        const bool status = stopAdcWithDma();

        return status;
    }

    bool AmbientLightSensorDriver::onReset()
    {
        return true;
    }

    uint32_t AmbientLightSensorDriver::getAmbientLightLevel() const
    {
        uint32_t adcResult = adcBuffer[0u];

        return adcResult;
    }

    bool AmbientLightSensorDriver::startAdcWithDma()
    {
        HAL_StatusTypeDef statusFromHal = HAL_ADC_Start_DMA(&hadc, (uint32_t *)adcBuffer, AdcBufferSize);

        return (statusFromHal == HAL_OK);
    }

    bool AmbientLightSensorDriver::stopAdcWithDma()
    {
        HAL_StatusTypeDef statusFromHal = HAL_ADC_Stop_DMA(&hadc);

        return (statusFromHal == HAL_OK);
    }

}
