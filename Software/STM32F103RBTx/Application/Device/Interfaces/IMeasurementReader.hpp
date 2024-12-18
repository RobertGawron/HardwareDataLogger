#ifndef IMeasurementReader_h
#define IMeasurementReader_h

#include "Device/Inc/MeasurementType.hpp"
#include "Driver/Inc/DriverState.hpp"

namespace Device
{

    class IMeasurementReader //: public Driver::DriverState
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

        virtual int getDataDummy() = 0;

#if 0
        /**
         * @brief Flushes the data to the storage medium.
         *
         * This method should be implemented to flush any buffered data to the storage medium, ensuring
         * that all data is physically written and not just stored in a temporary buffer.
         */
        virtual bool flush() = 0;

        /**
         * @brief Notifies about new data to be saved.
         *
         * This method should be implemented to handle any necessary actions when new data is ready to be saved.
         */
        virtual bool notify(Device::MeasurementType &measurement) = 0;

#endif
    };
}

#endif
