module;

#include <span>
#include <array>
#include <cstdint>
#include <cstddef>
#include <limits>

#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_adc.h"

import Driver.DriverComponent;
import Driver.LightSensorDriverConcept;

export module Driver.LightSensorDriver;

export namespace Driver
{
    class LightSensorDriver final : public DriverComponent
    {
    public:
        explicit constexpr LightSensorDriver(ADC_HandleTypeDef &_adc) noexcept
            : adc(_adc)
        {
        }

        LightSensorDriver() = delete;
        LightSensorDriver(const LightSensorDriver &) = delete;
        LightSensorDriver &operator=(const LightSensorDriver &) = delete;
        LightSensorDriver(LightSensorDriver &&) = delete;
        LightSensorDriver &operator=(LightSensorDriver &&) = delete;

        [[nodiscard]] auto onStart() noexcept -> bool;
        [[nodiscard]] auto onStop() noexcept -> bool;

        /// @brief Returns a read-only view of the ADC DMA buffer.
        /// @note The buffer may be modified by DMA concurrently.
        [[nodiscard]] auto samples() const noexcept -> std::span<const std::uint16_t>;

    private:
        ADC_HandleTypeDef &adc;

        static constexpr std::size_t ADC_BUFFER_SIZE = 10U;
        alignas(4) std::array<std::uint16_t, ADC_BUFFER_SIZE> adcDmaBuffer{};

        // duplication because adcDmaBuffer has already alignas,
        // but this is compile time check, so doesnt cost on
        // binary size or runtime performance
        static_assert(alignof(decltype(adcDmaBuffer)) >= alignof(std::uint16_t),
                      "DMA buffer must be at least 16-bit aligned (HALFWORD transfers).");

        static constexpr std::uint32_t ADC_MAX_SAMPLE = 4095U; // STM32F1 12-bit ADC
        static_assert(ADC_MAX_SAMPLE * ADC_BUFFER_SIZE <= std::numeric_limits<std::uint32_t>::max(),
                      "ADC sum will overflow uint32_t in client classes while calculating average value; use uint64_t accumulator in client classes.");
    };

    static_assert(Driver::Concepts::LightSensorDriverConcept<LightSensorDriver>,
                  "LightSensorDriver must satisfy the concept requirements");
}
