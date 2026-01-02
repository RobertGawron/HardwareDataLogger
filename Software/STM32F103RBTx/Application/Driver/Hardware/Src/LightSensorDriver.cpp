/**
 * @file LightSensorDriver.cpp
 * @brief Implementation of ADC+DMA ambient light sensor
 */

#include "Driver/Hardware/Inc/LightSensorDriver.hpp"
#include "stm32f1xx_hal_adc.h"

#include <numeric>
#include <cstdint>

namespace Driver
{

    bool LightSensorDriver::onStart() noexcept
    {
        return startAdc();
    }

    bool LightSensorDriver::onStop() noexcept
    {
        return stopAdc();
    }

    std::uint32_t LightSensorDriver::getAmbientLightLevel() const noexcept
    {
        const auto sum = std::accumulate(adcBuffer.begin(),
                                         adcBuffer.end(),
                                         std::uint32_t{0});

        return sum / adcBuffer.size();
    }

    bool LightSensorDriver::startAdc() noexcept
    {
        const auto status = HAL_ADC_Start_DMA(&hadc,
                                              reinterpret_cast<std::uint32_t *>(adcBuffer.data()),
                                              static_cast<std::uint32_t>(adcBuffer.size()));

        return status == HAL_OK;
    }

    bool LightSensorDriver::stopAdc() noexcept
    {
        const auto status = HAL_ADC_Stop_DMA(&hadc);

        return status == HAL_OK;
    }

} // namespace Driver