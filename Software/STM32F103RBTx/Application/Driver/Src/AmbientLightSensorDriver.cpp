#include "Driver/Inc/AmbientLightSensorDriver.hpp"
#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_def.h"
#include <cstdint>

std::uint32_t adcBuffer[AdcBufferSize];

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

    std::uint32_t AmbientLightSensorDriver::getAmbientLightLevel() const
    {
        const std::uint32_t adcResult = adcBuffer[0u];

        return adcResult;
    }

    bool AmbientLightSensorDriver::startAdcWithDma()
    {
        const HAL_StatusTypeDef statusFromHal = HAL_ADC_Start_DMA(&hadc, (std::uint32_t *)adcBuffer, AdcBufferSize);

        return (statusFromHal == HAL_OK);
    }

    bool AmbientLightSensorDriver::stopAdcWithDma()
    {
        const HAL_StatusTypeDef statusFromHal = HAL_ADC_Stop_DMA(&hadc);

        return (statusFromHal == HAL_OK);
    }

}
