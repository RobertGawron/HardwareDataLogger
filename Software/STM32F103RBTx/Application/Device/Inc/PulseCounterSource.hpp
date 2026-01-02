/**
 * @file PulseCounterSource.hpp
 * @brief Defines the PulseCounterSource class responsible for managing measurements
 *        from a pulse counter device.
 */

#ifndef PULSE_COUNTER_SOURCE_HPP
#define PULSE_COUNTER_SOURCE_HPP

#include "Device/Inc/MeasurementSource.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Device/Inc/DeviceComponent.hpp"

#include "PulseCounterDriver.hpp"

namespace Device
{
    /**
     * @class PulseCounterSource
     * @brief Manages the retrieval and initialization of measurement data from a pulse counter device.
     *
     * The PulseCounterSource class interfaces with a pulse counter driver to initialize
     * the device, retrieve measurements, and manage the availability of new data.
     */
    class PulseCounterSource final : public DeviceComponent
    {
    public:
        /**
         * @brief Constructs a PulseCounterSource with device ID and pulse counter driver.
         *
         * @param deviceId The unique identifier for this measurement source.
         * @param pulseCounterDriver Reference to the driver responsible for interfacing with the pulse counter device.
         */
        explicit constexpr PulseCounterSource(
            MeasurementDeviceId deviceId,
            Driver::PulseCounterDriver &pulseCounterDriver) noexcept
            : deviceId{deviceId}, pulseCounterDriver{pulseCounterDriver}
        {
        }

        ~PulseCounterSource() = default;

        // Non-copyable and non-movable
        PulseCounterSource() = delete;
        PulseCounterSource(const PulseCounterSource &) = delete;
        PulseCounterSource(PulseCounterSource &&) = delete;
        PulseCounterSource &operator=(const PulseCounterSource &) = delete;
        PulseCounterSource &operator=(PulseCounterSource &&) = delete;

        [[nodiscard]] bool onInit() noexcept;
        [[nodiscard]] bool onStart() noexcept;
        [[nodiscard]] bool onStop() noexcept;
        [[nodiscard]] bool isMeasurementAvailable() const noexcept;
        [[nodiscard]] MeasurementType getMeasurement() noexcept;

    private:
        MeasurementDeviceId deviceId;
        Driver::PulseCounterDriver &pulseCounterDriver;
    };

    static_assert(Device::MeasurementSource<Device::PulseCounterSource>,
                  "PulseCounterSource must satisfy MeasurementSource concept");

} // namespace Device

#endif // PULSE_COUNTER_MEASUREMENT_SOURCE_HPP