export module Device.SdCardRecorder;

import Device.DeviceComponent;
import Device.MeasurementRecorder;
import Device.MeasurementType;

import Driver.SdCardDriver;
import Driver.SdCardStatus;

export namespace Device
{
    /**
     * @class SdCardRecorder
     * @brief Handles writing measurement data to an SD card.
     *
     * The SdCardRecorder class interacts with an SD card driver to store measurement data.
     * It provides methods for writing, flushing, and managing the lifecycle of the recording process.
     */
    class SdCardRecorder final : public DeviceComponent
    {
    public:
        /**
         * @brief Constructs a SdCardRecorder with a reference to an SD card driver.
         *
         * @param driver Reference to the SD card driver responsible for managing SD card interactions.
         */
        explicit constexpr SdCardRecorder(Driver::SdCardDriver &driver) noexcept
            : driver{driver}
        {
        }

        ~SdCardRecorder() = default;

        // Non-copyable and non-movable
        SdCardRecorder() = delete;
        SdCardRecorder(const SdCardRecorder &) = delete;
        SdCardRecorder(SdCardRecorder &&) = delete;
        SdCardRecorder &operator=(const SdCardRecorder &) = delete;
        SdCardRecorder &operator=(SdCardRecorder &&) = delete;

        /**
         * @brief Notifies the recorder to process new data.
         *
         * This method is called to notify the recorder that new measurement data is available
         * and should be written to the SD card.
         */
        [[nodiscard]] auto notify(const MeasurementType &measurement) noexcept -> bool;

        /**
         * @brief Initializes the SdCardRecorder.
         *
         * This method is responsible for initializing the recorder and preparing it for operation.
         * @return True if initialization was successful, false otherwise.
         */
        [[nodiscard]] auto onInit() noexcept -> bool;

        /**
         * @brief Starts the SdCardRecorder.
         *
         * This method starts the recorder, enabling it to begin writing measurement data to the SD card.
         * @return True if the recorder started successfully, false otherwise.
         */
        [[nodiscard]] auto onStart() noexcept -> bool;

        /**
         * @brief Stops the SdCardRecorder.
         *
         * This method stops the recorder, halting any further writing of measurement data.
         * @return True if the recorder stopped successfully, false otherwise.
         */
        [[nodiscard]] auto onStop() noexcept -> bool;

    private:
        Driver::SdCardDriver &driver;
    };

    // Compile-time verification
    static_assert(MeasurementRecorder<SdCardRecorder>,
                  "SdCardRecorder must satisfy MeasurementRecorder concept");

} // namespace Device