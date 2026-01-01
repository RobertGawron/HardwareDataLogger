#ifndef IMEASUREMENT_READER_HPP
#define IMEASUREMENT_READER_HPP

#include "Device/Inc/MeasurementDeviceId.hpp"

#include <cstdint>

namespace Device
{
    /**
     * @class IMeasurementReader
     * @brief Interface for retrieving the latest measurements from various sources.
     *
     * This interface defines a contract for classes that provide access to the most recent
     * measurement values from different measurement devices in the system.
     */
    class IMeasurementReader
    {
    public:
        constexpr IMeasurementReader() noexcept = default;
        virtual ~IMeasurementReader() = default;

        // Non-copyable and non-movable
        IMeasurementReader(const IMeasurementReader &) = delete;
        IMeasurementReader(IMeasurementReader &&) = delete;
        IMeasurementReader &operator=(const IMeasurementReader &) = delete;
        IMeasurementReader &operator=(IMeasurementReader &&) = delete;

        /**
         * @brief Retrieves the latest measurement value for a specific source.
         *
         * This method should be implemented to return the most recent measurement value
         * available from the specified measurement source.
         *
         * @param source The identifier of the measurement source device.
         * @return The latest measurement value from the specified source.
         */
        [[nodiscard]] virtual std::uint32_t getLatestMeasurement(MeasurementDeviceId source) const noexcept = 0;
    };

} // namespace Device

#endif // IMEASUREMENT_READER_HPP