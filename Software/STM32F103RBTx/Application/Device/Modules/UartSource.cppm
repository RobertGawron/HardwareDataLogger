/**
 * @file UartSource.cppm
 * @brief Defines the UartSource class responsible for receiving measurement data via UART.
 */
export module Device.UartSource;

import Device.DeviceComponent;
import Device.MeasurementSource;
import Device.MeasurementType;
import Device.MeasurementDeviceId;

import Driver.UartDriver;

export namespace Device
{
    /**
     * @class UartSource
     * @brief Receives measurement data from a UART device.
     *
     * The UartSource class is responsible for receiving measurement data from a UART device.
     * In the future, it may support communication with the device via SCPI (Standard Commands for Programmable Instruments),
     * enabling more advanced control of the measurement process.
     */
    class UartSource final : public DeviceComponent
    {
    public:
        /**
         * @brief Constructs a UartSource with a device ID and UART driver reference.
         *
         * @param deviceId Unique identifier for the measurement source device
         * @param driver Reference to the UART driver responsible for communication
         */
        explicit UartSource(
            MeasurementDeviceId deviceId,
            Driver::UartDriver &driver) noexcept;

        UartSource() = delete;
        ~UartSource() = default;

        UartSource(const UartSource &) = delete;
        UartSource &operator=(const UartSource &) = delete;
        UartSource(UartSource &&) = delete;
        UartSource &operator=(UartSource &&) = delete;

        [[nodiscard]] auto onInit() noexcept -> bool;
        [[nodiscard]] auto onStart() noexcept -> bool;
        [[nodiscard]] auto onStop() noexcept -> bool;

        [[nodiscard]] auto isMeasurementAvailable() const noexcept -> bool;
        [[nodiscard]] auto getMeasurement() noexcept -> MeasurementType;

    private:
        MeasurementDeviceId deviceId;
        Driver::UartDriver &driver;
    };

    static_assert(Device::MeasurementSource<Device::UartSource>,
                  "UartSource must satisfy MeasurementSource concept");
}