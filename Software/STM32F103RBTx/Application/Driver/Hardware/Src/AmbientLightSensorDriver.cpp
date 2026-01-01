#include "Driver/Hardware/Inc/AmbientLightSensorDriver.hpp"

#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_def.h"

#include <cstdint>
#include <numeric>

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
        const uint32_t totalSum = std::accumulate(adcBuffer.begin(),
                                                  adcBuffer.end(),
                                                  static_cast<std::uint32_t>(0U));

        const uint32_t average = (totalSum / adcBuffer.size());

        return average;
    }

    bool AmbientLightSensorDriver::startAdcWithDma()
    {
        const HAL_StatusTypeDef status = HAL_ADC_Start_DMA(&hadc,
                                                           reinterpret_cast<uint32_t *>(adcBuffer.data()),
                                                           static_cast<std::uint32_t>(adcBuffer.size()));

        return (status == HAL_OK);
    }

    bool AmbientLightSensorDriver::stopAdcWithDma()
    {
        const HAL_StatusTypeDef statusFromHal = HAL_ADC_Stop_DMA(&hadc);

        return (statusFromHal == HAL_OK);
    }

}
