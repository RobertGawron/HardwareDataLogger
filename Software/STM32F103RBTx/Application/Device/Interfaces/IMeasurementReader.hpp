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
    };
}

#endif
