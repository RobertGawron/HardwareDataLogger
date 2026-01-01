#ifndef CACHE_MEASUREMENT_RECORDER_HPP
#define CACHE_MEASUREMENT_RECORDER_HPP

#include "Device/Interface/IMeasurementRecorder.hpp"
#include "Device/Interface/IMeasurementReader.hpp"
#include "Device/Inc/MeasurementDeviceId.hpp"

#include <array>
#include <cstdint>

namespace Device
{
    /**
     * @class CacheMeasurementRecorder
     * @brief Caches and provides access to the latest measurements from various devices.
     *
     * Implements both IMeasurementRecorder (to record incoming measurements)
     * and IMeasurementReader (to retrieve the last recorded value per source).
     */
    class CacheMeasurementRecorder : public IMeasurementRecorder, public IMeasurementReader
    {
    public:
        constexpr CacheMeasurementRecorder() noexcept = default;
        ~CacheMeasurementRecorder() override = default;

        // Non-copyable and non-movable
        CacheMeasurementRecorder(const CacheMeasurementRecorder &) = delete;
        CacheMeasurementRecorder(CacheMeasurementRecorder &&) = delete;
        CacheMeasurementRecorder &operator=(const CacheMeasurementRecorder &) = delete;
        CacheMeasurementRecorder &operator=(CacheMeasurementRecorder &&) = delete;

        /**
         * @brief Record a new measurement.
         * @param measurement The measurement to record.
         * @return true if the measurement was successfully recorded.
         */
        [[nodiscard]] bool notify(const MeasurementType &measurement) noexcept override;

    protected:
        /**
         * @brief Initialize the recorder.
         * @return true if initialization succeeded.
         */
        [[nodiscard]] bool onInitialize() noexcept override;

        /**
         * @brief Start the recorder.
         * @return true if startup succeeded.
         */
        [[nodiscard]] bool onStart() noexcept override;

        /**
         * @brief Stop the recorder.
         * @return true if shutdown succeeded.
         */
        [[nodiscard]] bool onStop() noexcept override;

        /**
         * @brief Reset the recorder state.
         * @return true if reset succeeded.
         */
        [[nodiscard]] bool onReset() noexcept override;

        /**
         * @brief Retrieve the last measurement for a given device source.
         * @param source Identifier of the measurement device.
         * @return The last recorded value for that source.
         */
        [[nodiscard]] std::uint32_t getLatestMeasurement(MeasurementDeviceId source) const noexcept override;

    private:
        /**
         * @brief Internal write operation to update the cache.
         * @param measurement The measurement to cache.
         * @return true if the write was successful.
         */
        [[nodiscard]] virtual bool write(const MeasurementType &measurement) noexcept;

        static constexpr std::size_t MEASUREMENT_SOURCE_COUNT{
            static_cast<std::size_t>(MeasurementDeviceId::LAST_NOT_USED)};

        std::array<std::uint32_t, MEASUREMENT_SOURCE_COUNT> lastMeasurement{};
    };

} // namespace Device

#endif // CACHE_MEASUREMENT_RECORDER_HPP