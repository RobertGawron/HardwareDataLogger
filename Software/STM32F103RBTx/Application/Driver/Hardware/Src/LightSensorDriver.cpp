module;

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_adc.h"

#include <array>
#include <span>
#include <cstdint>

module Driver.LightSensorDriver;

namespace Driver
{
    auto LightSensorDriver::onStart() noexcept -> bool
    {
        const HAL_StatusTypeDef halStatus =
            HAL_ADC_Start_DMA(&adc,
                              reinterpret_cast<std::uint32_t *>(adcDmaBuffer.data()),
                              static_cast<std::uint32_t>(adcDmaBuffer.size()));

        return (halStatus == HAL_OK);
    }

    auto LightSensorDriver::onStop() noexcept -> bool
    {
        return (HAL_ADC_Stop_DMA(&adc) == HAL_OK);
    }

    auto LightSensorDriver::samples() const noexcept
        -> std::span<const std::uint16_t>
    {
        return std::span{adcDmaBuffer};
    }
}
