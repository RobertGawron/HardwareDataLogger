/**
 * @file SdCardMeasurementRecorder.hpp
 * @brief Defines the SdCardMeasurementRecorder class responsible for writing measurement data to an SD card.
 */

#ifndef SD_CARD_MEASUREMENT_RECORDER_HPP
#define SD_CARD_MEASUREMENT_RECORDER_HPP

#include "Device/Interface/IMeasurementRecorder.hpp"
#include "Driver/Interface/ISdCardDriver.hpp"

namespace Device
{
    /**
     * @class SdCardMeasurementRecorder
     * @brief Handles writing measurement data to an SD card.
     *
     * The SdCardMeasurementRecorder class interacts with an SD card driver to store measurement data.
     * It provides methods for writing, flushing, and managing the lifecycle of the recording process.
     */
    class SdCardMeasurementRecorder final : public IMeasurementRecorder
    {
    public:
        /**
         * @brief Constructs a SdCardMeasurementRecorder with a reference to an SD card driver.
         *
         * @param driver Reference to the SD card driver responsible for managing SD card interactions.
         */
        explicit constexpr SdCardMeasurementRecorder(Driver::ISdCardDriver &driver) noexcept
            : driver{driver}
        {
        }

        ~SdCardMeasurementRecorder() override = default;

        // Non-copyable and non-movable
        SdCardMeasurementRecorder() = delete;
        SdCardMeasurementRecorder(const SdCardMeasurementRecorder &) = delete;
        SdCardMeasurementRecorder(SdCardMeasurementRecorder &&) = delete;
        SdCardMeasurementRecorder &operator=(const SdCardMeasurementRecorder &) = delete;
        SdCardMeasurementRecorder &operator=(SdCardMeasurementRecorder &&) = delete;

        /**
         * @brief Notifies the recorder to process new data.
         *
         * This method is called to notify the recorder that new measurement data is available
         * and should be written to the SD card.
         */
        [[nodiscard]] bool notify(const MeasurementType &measurement) noexcept override;

    protected:
        /**
         * @brief Initializes the SdCardMeasurementRecorder.
         *
         * This method is responsible for initializing the recorder and preparing it for operation.
         * @return True if initialization was successful, false otherwise.
         */
        [[nodiscard]] bool onInitialize() noexcept override;

        /**
         * @brief Starts the SdCardMeasurementRecorder.
         *
         * This method starts the recorder, enabling it to begin writing measurement data to the SD card.
         * @return True if the recorder started successfully, false otherwise.
         */
        [[nodiscard]] bool onStart() noexcept override;

        /**
         * @brief Stops the SdCardMeasurementRecorder.
         *
         * This method stops the recorder, halting any further writing of measurement data.
         * @return True if the recorder stopped successfully, false otherwise.
         */
        [[nodiscard]] bool onStop() noexcept override;

        /**
         * @brief Resets the SdCardMeasurementRecorder.
         *
         * This method resets the recorder, clearing any internal state or buffers.
         * @return True if the recorder was reset successfully, false otherwise.
         */
        [[nodiscard]] bool onReset() noexcept override;

    private:
        Driver::ISdCardDriver &driver;
    };

} // namespace Device

#endif // SD_CARD_MEASUREMENT_RECORDER_HPP