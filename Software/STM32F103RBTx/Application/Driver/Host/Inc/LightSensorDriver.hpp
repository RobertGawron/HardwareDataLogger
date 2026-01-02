#ifndef LightSensorDriver_H_
#define LightSensorDriver_H_

#include "Driver/Interface/LightSensorDriverConcept.hpp"
#include "Driver/Interface/DriverComponent.hpp"

#include <stdint.h>

namespace Driver
{

    class LightSensorDriver : public DriverComponent
    {
    public:
        /**
         * @brief Default constructor.
         *
         */
        LightSensorDriver() = default;

        /**
         * @brief Destructor for LightSensorDriver.
         */
        ~LightSensorDriver() = default;

        // Non-copyable and non-movable
        LightSensorDriver(const LightSensorDriver &) = delete;
        LightSensorDriver(LightSensorDriver &&) = delete;
        LightSensorDriver &operator=(const LightSensorDriver &) = delete;
        LightSensorDriver &operator=(LightSensorDriver &&) = delete;

        [[nodiscard]] bool onStart() { return true; }
        [[nodiscard]] bool onStop() { return true; }

        /**
         * @brief Retrieves the current ambient light level.
         *
         * This method returns the current ambient light level measured by the sensor.
         * The range of the returned value is dependent on the hardware configuration and sensor characteristics.
         *
         * @return std::uint32_t The current ambient light level.
         */
        [[nodiscard]] std::uint32_t getAmbientLightLevel() const noexcept;

        /**
         * @brief Starts the ADC conversion using DMA for data transfer.
         *
         * This method configures and starts the ADC in combination with DMA to handle data transfer
         * efficiently without burdening the CPU. The DMA continuously transfers the ADC conversion results
         * into a buffer, allowing the system to read the latest ambient light levels.
         *
         * @return true if ADC and DMA setup is successful, false otherwise.
         */
        bool startAdc() noexcept;

        /**
         * @brief Stops the ADC conversion and DMA transfer.
         *
         * This method stops the ongoing ADC conversions and halts the DMA transfer process. It is typically
         * used when the ambient light measurements are no longer needed, or before resetting or shutting down
         * the system.
         *
         * @return true if the ADC and DMA stop successfully, false otherwise.
         */
        bool stopAdc() noexcept;
    };

    static_assert(Driver::Concepts::LightSensorDriverConcept<LightSensorDriver>,
                  "LightSensorDriver must satisfy the concept requirements");

}

#endif // LightSensorDriver_H_
