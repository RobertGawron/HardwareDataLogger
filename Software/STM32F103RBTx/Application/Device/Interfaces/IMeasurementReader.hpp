#ifndef IMeasurementReader_h
#define IMeasurementReader_h

#include "Device/Inc/MeasurementType.hpp"
#include "Driver/Interfaces/DriverState.hpp"

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
        /**
         * @brief Default constructor.
         */
        IMeasurementReader() = default;

        /**
         * @brief Virtual destructor to ensure proper cleanup of derived classes.
         */
        virtual ~IMeasurementReader() = default;

        /**
         * @brief Retrieves the latest measurement value for a specific source.
         *
         * This method should be implemented to return the most recent measurement value
         * available from the specified measurement source.
         *
         * @param source The identifier of the measurement source device.
         * @return The latest measurement value from the specified source.
         */
        [[nodiscard]] virtual std::uint32_t getLatestMeasurement(MeasurementDeviceId source) const = 0;
    };
}

#endif
