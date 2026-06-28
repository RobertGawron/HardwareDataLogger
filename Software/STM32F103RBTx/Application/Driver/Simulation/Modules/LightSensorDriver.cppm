module;

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>

export module Driver.LightSensorDriver;

import Driver.DriverComponent;
import Driver.LightSensorDriverConcept;

export namespace Driver
{
    class LightSensorDriver : public DriverComponent
    {
    public:
        /**
         * @brief Default constructor.
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

        [[nodiscard]] bool onStart() noexcept { return true; }
        [[nodiscard]] bool onStop() noexcept { return true; }

        [[nodiscard]] auto samples() const noexcept -> std::span<const std::uint16_t>;

    private:
        static constexpr std::size_t ADC_BUFFER_SIZE = 10U;
        alignas(4) std::array<std::uint16_t, ADC_BUFFER_SIZE> adcDmaBuffer{};

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