/**
 * @file SdCardMeasurementRecorder.hpp
 * @brief Defines the SdCardMeasurementRecorder class responsible for writing measurement data to an SD card.
 */

#ifndef SdCardMeasurementRecorder_H_
#define SdCardMeasurementRecorder_H_

#include "Device/Interfaces/IMeasurementRecorder.hpp"
#include "Driver/Interfaces/ISdCardDriver.hpp"

namespace Device
{
    /**
     * @class SdCardMeasurementRecorder
     * @brief Handles writing measurement data to an SD card.
     *
     * The SdCardMeasurementRecorder class interacts with an SD card driver to store measurement data.
     * It provides methods for writing, flushing, and managing the lifecycle of the recording process.
     */
    class SdCardMeasurementRecorder : public IMeasurementRecorder
    {
    public:
        /**
         * @brief Constructs a SdCardMeasurementRecorder with a reference to an SD card driver.
         *
         * @param driver Reference to the SD card driver responsible for managing SD card interactions.
         */
        explicit SdCardMeasurementRecorder(Driver::ISdCardDriver &driver);

        /**
         * @brief Deleted default constructor to prevent instantiation without a driver.
         */
        SdCardMeasurementRecorder() = delete;

        /**
         * @brief Default destructor for SdCardMeasurementRecorder.
         */
        ~SdCardMeasurementRecorder() override = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        SdCardMeasurementRecorder(const SdCardMeasurementRecorder &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return SdCardMeasurementRecorder& The assigned object.
         */
        SdCardMeasurementRecorder &operator=(const SdCardMeasurementRecorder &) = delete;

            /**
         * @brief Flushes any remaining data to the SD card.
         *
         * This method ensures that any remaining buffered data is written to the SD card.
         */
        bool flush() override;

        /**
         * @brief Notifies the recorder to process new data.
         *
         * This method is called to notify the recorder that new measurement data is available
         * and should be written to the SD card.
         */
        bool notify(Device::MeasurementType &measurement) override;

    protected:
        /**
         * @brief Initializes the SdCardMeasurementRecorder.
         *
         * This method is responsible for initializing the recorder and preparing it for operation.
         * @return True if initialization was successful, false otherwise.
         */
        bool onInitialize() override;

        /**
         * @brief Starts the SdCardMeasurementRecorder.
         *
         * This method starts the recorder, enabling it to begin writing measurement data to the SD card.
         * @return True if the recorder started successfully, false otherwise.
         */
        bool onStart() override;

        /**
         * @brief Stops the SdCardMeasurementRecorder.
         *
         * This method stops the recorder, halting any further writing of measurement data.
         * @return True if the recorder stopped successfully, false otherwise.
         */
        bool onStop() override;

        /**
         * @brief Resets the SdCardMeasurementRecorder.
         *
         * This method resets the recorder, clearing any internal state or buffers.
         * @return True if the recorder was reset successfully, false otherwise.
         */
        bool onReset() override;

    private:
        /** @brief Reference to the SD card driver used for communication with the SD card. */
        Driver::ISdCardDriver &driver;
    };
}
#endif // SdCardMeasurementRecorder_H_
