#ifndef HmiMeasurementModel_h
#define HmiMeasurementModel_h

#include "Device/Interfaces/IMeasurementReader.hpp"

/**
 * @file HmiMeasurementModel.hpp
 * @brief Defines the HmiMeasurementModel class responsible for retrieving measurement data
 *        from physical devices for HMI presentation.
 */

namespace BusinessLogic
{
    /**
     * @class HmiMeasurementModel
     * @brief Provides measurement data to the Human-Machine Interface (HMI) layer.
     *
     * This class acts as a bridge between the device measurement infrastructure and the HMI layer,
     * encapsulating the logic for retrieving the latest measurements from various device sources.
     * It follows the Single Responsibility Principle by focusing solely on measurement data access.
     */
    class HmiMeasurementModel
    {
    public:
        /**
         * @brief Constructs a HmiMeasurementModel with a reference to a measurement reader.
         * 
         * @param reader Reference to the measurement reader that provides access to device data.
         */
        explicit HmiMeasurementModel(Device::IMeasurementReader &reader);

        /**
         * @brief Deleted default constructor to prevent instantiation without dependencies.
         */
        HmiMeasurementModel() = delete;

        /**
         * @brief Default virtual destructor.
         *
         */
        virtual ~HmiMeasurementModel() = default;

        /**
         * @brief Deleted copy constructor.
         *

         */
        HmiMeasurementModel(const HmiMeasurementModel &) = delete;

        /**
         * @brief Deleted copy assignment operator.
         *
         */
        HmiMeasurementModel &operator=(const HmiMeasurementModel &) = delete;

        /**
         * @brief Retrieves the latest measurement value from a specified device.
         * 
         * @param source The unique identifier of the measurement device to query.
         * @return std::uint32_t The latest measurement value from the specified device.
         * @retval 0 if no measurement is available or if the device is not found.
         * 
         */
        [[nodiscard]] std::uint32_t getLatestMeasurement(Device::MeasurementDeviceId source) const;

    private:
        /** 
         * @brief Reference to the measurement reader that interfaces with physical devices.
         * 
         * This dependency injection allows the model to remain decoupled from specific
         * device implementations, following the Dependency Inversion Principle.
         */
        Device::IMeasurementReader &reader;
    };
}

#endif // HmiMeasurementModel_h
