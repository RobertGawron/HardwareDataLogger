/**
 * @file PulseCounterMeasurementSource.hpp
 * @brief Defines the PulseCounterMeasurementSource class responsible for managing measurements
 *        from a pulse counter device.
 */

#ifndef PULSE_COUNTER_MEASUREMENT_SOURCE_HPP
#define PULSE_COUNTER_MEASUREMENT_SOURCE_HPP

#include "Device/Interface/IMeasurementSource.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Driver/Interface/IPulseCounterDriver.hpp"

namespace Device
{
    /**
     * @class PulseCounterMeasurementSource
     * @brief Manages the retrieval and initialization of measurement data from a pulse counter device.
     *
     * The PulseCounterMeasurementSource class interfaces with a pulse counter driver to initialize
     * the device, retrieve measurements, and manage the availability of new data.
     */
    class PulseCounterMeasurementSource final : public IMeasurementSource
    {
    public:
        /**
         * @brief Constructs a PulseCounterMeasurementSource with device ID and pulse counter driver.
         *
         * @param deviceId The unique identifier for this measurement source.
         * @param pulseCounterDriver Reference to the driver responsible for interfacing with the pulse counter device.
         */
        explicit constexpr PulseCounterMeasurementSource(
            MeasurementDeviceId deviceId,
            Driver::IPulseCounterDriver &pulseCounterDriver) noexcept
            : deviceId{deviceId}, pulseCounterDriver{pulseCounterDriver}
        {
        }

        ~PulseCounterMeasurementSource() override = default;

        // Non-copyable and non-movable
        PulseCounterMeasurementSource() = delete;
        PulseCounterMeasurementSource(const PulseCounterMeasurementSource &) = delete;
        PulseCounterMeasurementSource(PulseCounterMeasurementSource &&) = delete;
        PulseCounterMeasurementSource &operator=(const PulseCounterMeasurementSource &) = delete;
        PulseCounterMeasurementSource &operator=(PulseCounterMeasurementSource &&) = delete;

        [[nodiscard]] bool initialize() noexcept override;
        [[nodiscard]] bool start() noexcept override;
        [[nodiscard]] bool stop() noexcept override;
        [[nodiscard]] bool isMeasurementAvailable() const noexcept override;
        [[nodiscard]] MeasurementType getMeasurement() noexcept override;

    private:
        MeasurementDeviceId deviceId;
        Driver::IPulseCounterDriver &pulseCounterDriver;
    };

} // namespace Device

#endif // PULSE_COUNTER_MEASUREMENT_SOURCE_HPP