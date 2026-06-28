/**
 * @file PulseCounterSource.cppm
 * @brief Defines the PulseCounterSource class responsible for managing measurements
 *        from a pulse counter device.
 */
export module Device.PulseCounterSource;

import Device.DeviceComponent;
import Device.MeasurementSource;
import Device.MeasurementType;
import Device.MeasurementDeviceId;

import Driver.PulseCounterDriver;

export namespace Device
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

        [[nodiscard]] auto onInit() noexcept -> bool;
        [[nodiscard]] auto onStart() noexcept -> bool;
        [[nodiscard]] auto onStop() noexcept -> bool;
        [[nodiscard]] auto isMeasurementAvailable() const noexcept -> bool;
        [[nodiscard]] auto getMeasurement() noexcept -> MeasurementType;

    private:
        MeasurementDeviceId deviceId;
        Driver::PulseCounterDriver &pulseCounterDriver;
    };

    static_assert(Device::MeasurementSource<Device::PulseCounterSource>,
                  "PulseCounterSource must satisfy MeasurementSource concept");

} // namespace Device