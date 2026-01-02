/**
 * @file LightSensorDriver.hpp
 * @brief Modern C++23 ambient light sensor driver using ADC+DMA
 */

#ifndef AMBIENTLIGHTSENSORDRIVER_H_
#define AMBIENTLIGHTSENSORDRIVER_H_

#include "Driver/Interface/LightSensorDriverConcept.hpp"
#include "Driver/Interface/DriverComponent.hpp"

#include "stm32f1xx_hal.h"

#include <array>
#include <cstddef>
#include <cstdint>

namespace Driver
{
    /**
     * @class LightSensorDriver
     * @brief Zero-CPU-overhead light sensor using ADC with DMA transfers
     *
     * Interfaces with phototransistor voltage divider via ADC. DMA continuously
     * fills buffer without CPU intervention. Readings averaged for stability.
     */
    class LightSensorDriver final : public DriverComponent
    {
    public:
        explicit constexpr LightSensorDriver(ADC_HandleTypeDef &_hadc) noexcept
            : hadc(_hadc)
        {
        }

        ~LightSensorDriver() = default;

        LightSensorDriver() = delete;
        LightSensorDriver(const LightSensorDriver &) = delete;
        LightSensorDriver &operator=(const LightSensorDriver &) = delete;
        LightSensorDriver(LightSensorDriver &&) = delete;
        LightSensorDriver &operator=(LightSensorDriver &&) = delete;

        [[nodiscard]] std::uint32_t getAmbientLightLevel() const noexcept;

        //  [[nodiscard]] constexpr bool onInit() noexcept  { return true; }
        [[nodiscard]] bool onStart();
        [[nodiscard]] bool onStop();

    private:
        static constexpr std::size_t ADC_BUFFER_SIZE = 10U;

        [[nodiscard]] bool startAdc() noexcept;
        [[nodiscard]] bool stopAdc() noexcept;

        ADC_HandleTypeDef &hadc;
        std::array<std::uint16_t, ADC_BUFFER_SIZE> adcBuffer{};
    };

    static_assert(Driver::Concepts::LightSensorDriverConcept<LightSensorDriver>,
                  "LightSensorDriver must satisfy the concept requirements");

} // namespace Driver

#endif // AMBIENTLIGHTSENSORDRIVER_H_