/**
 * @file UartRecorder.cppm
 * @brief Defines the UartRecorder class responsible for sending measurement data
 *        to a COM port via UART over USB.
 */
export module Device.UartRecorder;

import Device.DeviceComponent;
import Device.MeasurementRecorder;
import Device.MeasurementType;

import Driver.UartDriver;

export namespace Device
{
    /**
     * @class UartRecorder
     * @brief Handles sending measurement data to a computer's COM port via UART over USB.
     *
     * The UartRecorder class interacts with a UART driver to send measurement data
     * over a COM port, typically using UART over USB. It provides methods to manage the
     * initialization, transmission, and lifecycle of the data recording process.
     */
    class UartRecorder final : public DeviceComponent
    {
    public:
        /**
         * @brief Constructs a UartRecorder with a reference to a UART driver.
         *
         * @param driver Reference to the UART driver responsible for managing UART communication.
         */
        explicit constexpr UartRecorder(Driver::UartDriver &driver) noexcept
            : driver{driver}
        {
        }

        /**
         * @brief Default destructor for UartRecorder.
         */
        ~UartRecorder() = default;

        // Non-copyable and non-movable
        UartRecorder(const UartRecorder &) = delete;
        UartRecorder(UartRecorder &&) = delete;
        UartRecorder &operator=(const UartRecorder &) = delete;
        UartRecorder &operator=(UartRecorder &&) = delete;

        /**
         * @brief Notifies the recorder to process new data.
         *
         * This method is called to notify the recorder that new measurement data is available
         * and should be sent to the COM port via UART.
         */
        [[nodiscard]] auto notify(const MeasurementType &measurement) noexcept -> bool;

        /**
         * @brief Initializes the UartRecorder.
         *
         * This method is responsible for initializing the recorder and preparing it for operation.
         * @return True if initialization was successful, false otherwise.
         */
        [[nodiscard]] auto onInit() noexcept -> bool;

        /**
         * @brief Starts the UartRecorder.
         *
         * This method starts the recorder, enabling it to begin sending measurement data to the COM port via UART.
         * @return True if the recorder started successfully, false otherwise.
         */
        [[nodiscard]] auto onStart() noexcept -> bool;

        /**
         * @brief Stops the UartRecorder.
         *
         * This method stops the recorder, halting any further transmission of measurement data.
         * @return True if the recorder stopped successfully, false otherwise.
         */
        [[nodiscard]] auto onStop() noexcept -> bool;

    private:
        Driver::UartDriver &driver;
    };

    // Compile-time verification
    static_assert(MeasurementRecorder<UartRecorder>,
                  "UartRecorder must satisfy MeasurementRecorder concept");

} // namespace Device