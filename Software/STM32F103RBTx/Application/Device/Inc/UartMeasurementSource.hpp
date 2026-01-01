/**
 * @file UartMeasurementSource.hpp
 * @brief Defines the UartMeasurementSource class responsible for receiving measurement data via UART.
 */

#ifndef UartMeasurementSource_H_
#define UartMeasurementSource_H_

#include "Device/Interface/IMeasurementSource.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Driver/Interface/IUartDriver.hpp"

namespace Device
{
    /**
     * @class UartMeasurementSource
     * @brief Receives measurement data from a UART device.
     *
     * The UartMeasurementSource class is responsible for receiving measurement data from a UART device.
     * In the future, it may support communication with the device via SCPI (Standard Commands for Programmable Instruments),
     * enabling more advanced control of the measurement process.
     */
    class UartMeasurementSource final : public IMeasurementSource
    {
    public:
        /**
         * @brief Constructs a UartMeasurementSource with a device ID and UART driver reference.
         *
         * @param deviceId Unique identifier for the measurement source device
         * @param driver Reference to the UART driver responsible for communication
         */
        explicit UartMeasurementSource(
            MeasurementDeviceId deviceId,
            Driver::IUartDriver &driver) noexcept;

        UartMeasurementSource() = delete;
        ~UartMeasurementSource() override = default;

        UartMeasurementSource(const UartMeasurementSource &) = delete;
        UartMeasurementSource &operator=(const UartMeasurementSource &) = delete;
        UartMeasurementSource(UartMeasurementSource &&) = delete;
        UartMeasurementSource &operator=(UartMeasurementSource &&) = delete;

        [[nodiscard]] bool initialize() noexcept override;
        [[nodiscard]] bool start() noexcept override;
        [[nodiscard]] bool stop() noexcept override;
        [[nodiscard]] bool isMeasurementAvailable() const noexcept override;
        [[nodiscard]] MeasurementType getMeasurement() noexcept override;

    private:
        MeasurementDeviceId deviceId;
        Driver::IUartDriver &driver;
    };
}

#endif // UartMeasurementSource_H_