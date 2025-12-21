#include "Driver/Inc/AmbientLightSensorDriver.hpp"

#include "stm32f1xx_hal_adc.h"

// #include "stm32f1xx_hal_def.h"

#include <cstdint>

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

    uint16_t AmbientLightSensorDriver::getAmbientLightLevel() const
    {
        // Calculate average of all buffer values
        uint32_t sum = 0;
        for (size_t i = 0; i < AdcBufferSize; i++)
        {
            sum += adcBuffer[i];
        }
        sum = static_cast<uint16_t>(sum / AdcBufferSize);
        return sum;
    }

    bool AmbientLightSensorDriver::startAdcWithDma()
    {
        // Cast to uint32_t* for HAL compatibility
        return (HAL_ADC_Start_DMA(&hadc,
                                  reinterpret_cast<uint32_t *>(adcBuffer),
                                  AdcBufferSize) == HAL_OK);
    }

    bool AmbientLightSensorDriver::stopAdcWithDma()
    {
        const HAL_StatusTypeDef statusFromHal = HAL_ADC_Stop_DMA(&hadc);

        return (statusFromHal == HAL_OK);
    }

}
