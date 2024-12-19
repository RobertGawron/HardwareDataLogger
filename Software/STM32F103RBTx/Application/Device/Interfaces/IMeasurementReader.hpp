#ifndef IMeasurementReader_h
#define IMeasurementReader_h

#include "Device/Inc/MeasurementType.hpp"
#include "Driver/Inc/DriverState.hpp"

namespace Device
{
    class IMeasurementReader
    {
    public:
        /**
         * @brief Default constructor.
         */
        IMeasurementReader() = default;

        /**
         * @brief Virtual destructor.
         */
        virtual ~IMeasurementReader() = default;

        [[nodiscard]] virtual std::uint32_t getLatestMeasurement(MeasurementDeviceId source) const = 0;
    };
}

#endif
