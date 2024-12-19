/**
 * @file UartMeasurementSource.hpp
 * @brief Defines the UartMeasurementSource class responsible for receiving measurement data via UART.
 */

#ifndef UartMeasurementSource_H_
#define UartMeasurementSource_H_

#include "Device/Interfaces/IMeasurementSource.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"

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
    class UartMeasurementSource : public IMeasurementSource
    {
    public:
        /**
         * @brief Constructs a UartMeasurementSource with a reference to a UART driver.
         *
         * @param driver Reference to the UART driver responsible for managing communication with the UART device.
         */
        explicit UartMeasurementSource(MeasurementDeviceId id, Driver::IUartDriver &driver);

        /**
         * @brief Deleted default constructor to prevent instantiation without a driver.
         */
        UartMeasurementSource() = delete;

        /**
         * @brief Default destructor for UartMeasurementSource.
         */
        ~UartMeasurementSource() override = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        UartMeasurementSource(const UartMeasurementSource &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return UartMeasurementSource& The assigned object.
         */
        UartMeasurementSource &operator=(const UartMeasurementSource &) = delete;

        bool initialize() override;
        bool start() override;
        bool stop() override;

        /**
         * @brief Checks if new measurement data is available from the UART device.
         *
         * @return True if new measurement data is available, false otherwise.
         */
        bool isMeasurementAvailable() override;

        /**
         * @brief Retrieves the current measurement data from the UART device.
         *
         * This method fetches the latest measurement data received via UART.
         */
        MeasurementType getMeasurement() override;

    private:
        /** @brief Reference to the UART driver used for communication with the UART device. */
        Driver::IUartDriver &driver;
    };

}

#endif // UartMeasurementSource_H_
