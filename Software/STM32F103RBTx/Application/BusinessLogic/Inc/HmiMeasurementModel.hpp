#ifndef HmiMeasurementModel_h
#define HmiMeasurementModel_h

#include "Device/Interfaces/IMeasurementReader.hpp"

namespace BusinessLogic
{

    class HmiMeasurementModel
    {
    public:
        HmiMeasurementModel(Device::IMeasurementReader &reader);

        HmiMeasurementModel() = delete;

        /**
         * @brief Default virtual destructor.
         *
         * Ensures proper cleanup of the HmiMeasurementModel instance and its resources.
         */
        virtual ~HmiMeasurementModel() = default;

        /**
         * @brief Deleted copy constructor.
         *
         * Prevents copying of HmiMeasurementModel instances.
         */
        HmiMeasurementModel(const HmiMeasurementModel &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         *
         * Prevents assignment of HmiMeasurementModel instances.
         * @return Reference to this object.
         */
        HmiMeasurementModel &operator=(const HmiMeasurementModel &) = delete;

        int dummyGetData();

        Device::IMeasurementReader &reader;
    };
}

#endif // HmiMeasurementModel_h