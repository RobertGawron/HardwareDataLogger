#ifndef CacheMeasurementRecorder_H_
#define CacheMeasurementRecorder_H_

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
        CacheMeasurementRecorder() = default;           ///< Default constructor.
        ~CacheMeasurementRecorder() override = default; ///< Default destructor.

        CacheMeasurementRecorder(const CacheMeasurementRecorder &) = delete;            ///< Deleted copy constructor.
        CacheMeasurementRecorder &operator=(const CacheMeasurementRecorder &) = delete; ///< Deleted assignment operator.

        /**
         * @brief Record a new measurement.
         * @param measurement The measurement to record.
         * @return true if the measurement was successfully recorded.
         */
        bool notify(Device::MeasurementType &measurement) override;

    protected:
        /**
         * @brief Initialize the recorder.
         * @return true if initialization succeeded.
         */
        bool onInitialize() override;

        /**
         * @brief Start the recorder.
         * @return true if startup succeeded.
         */
        bool onStart() override;

        /**
         * @brief Stop the recorder.
         * @return true if shutdown succeeded.
         */
        bool onStop() override;

        /**
         * @brief Reset the recorder state.
         * @return true if reset succeeded.
         */
        bool onReset() override;

        /**
         * @brief Ensure all pending data is processed.
         * @return true if flush succeeded.
         */
        bool flush() override;

        /**
         * @brief Retrieve the last measurement for a given device source.
         * @param source Identifier of the measurement device.
         * @return The last recorded value for that source.
         */
        [[nodiscard]] std::uint32_t getLatestMeasurement(MeasurementDeviceId source) const override;

    private:
        /**
         * @brief Internal write operation to update the cache.
         * @param measurement The measurement to cache.
         * @return true if the write was successful.
         */
        virtual bool write(Device::MeasurementType &measurement);

        static constexpr std::size_t MeasurementSourceCount =
            static_cast<std::size_t>(MeasurementDeviceId::LAST_NOT_USED); ///< Number of measurement sources.

        std::array<std::uint32_t, MeasurementSourceCount> lastMeasurement = {0u}; ///< Cached values per source.
    };

} // namespace Device

#endif // CacheMeasurementRecorder_H_
