/**
 * @file IMeasurementDataStore.hpp
 * @brief Defines the IMeasurementDataStore class which manages the storage of measurement data
 *        using the observer pattern.
 */

#ifndef IMeasurementDataStore_H_
#define IMeasurementDataStore_H_

#include "Device/Interface/IMeasurementRecorder.hpp"
#include "Device/Interface/IMeasurementSource.hpp"

#include <cstdint>

namespace BusinessLogic
{
    /**
     * @class IMeasurementDataStore
     * @brief Implements the observer pattern to manage a collection of measurement recorders.
     *
     * This class allows clients to add or remove observers that store measurement data.
     * Observers can represent different storage methods such as SD card, Wi-Fi, UART, etc.
     * It is responsible for initializing and notifying all registered observers when new
     * measurement data is ready.
     */
    class IMeasurementDataStore
    {
    public:
        /**
         * @brief Default constructor for IMeasurementDataStore.
         */
        explicit IMeasurementDataStore() = default;

        /**
         * @brief Destructor for IMeasurementDataStore.
         */
        virtual ~IMeasurementDataStore() = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        IMeasurementDataStore(const IMeasurementDataStore &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return IMeasurementDataStore& The assigned object.
         */
        IMeasurementDataStore &operator=(const IMeasurementDataStore &) = delete;

        /**
         * @brief Adds an observer that records measurement data.
         *
         * The observer should implement the IMeasurementRecorder interface, and this method will
         * add it to the list of observers managed by the IMeasurementDataStore.
         *
         * @param observer Reference to an object that implements IMeasurementRecorder.
         * @return True if the observer was successfully added; false otherwise.
         */
        virtual bool addObserver(Device::IMeasurementRecorder &observer) = 0;

        /**
         * @brief Removes an observer that records measurement data.
         *
         * This method removes an observer from the list of registered observers, stopping it
         * from receiving updates about new measurement data.
         *
         * @param observer Reference to an object that implements IMeasurementRecorder.
         * @return True if the observer was successfully removed; false otherwise.
         * @note Removing the observer does not automatically deinitialize it.
         */
        virtual bool removeObserver(Device::IMeasurementRecorder &observer) = 0;

        /**
         * @brief Initializes the IMeasurementDataStore and all registered observers.
         *
         * This function initializes the IMeasurementDataStore and all the objects
         * registered via addObserver().
         *
         * @return True if initialization was successful; false otherwise.
         * @note Observers should not be initialized manually in other classes such as ApplicationBuilder.
         */
        virtual bool initialize() = 0;

        /**
         * @brief Starts the IMeasurementDataStore and all registered observers.
         *
         * This function starts the IMeasurementDataStore and prepares all registered observers to start
         * recording measurement data.
         *
         * @return True if start was successful; false otherwise.
         */
        virtual bool start() = 0;

        /**
         * @brief Notifies all registered observers that new measurement data is ready to be stored.
         *
         * This function iterates through the list of registered observers and notifies each one
         * that new measurement data is available for storage.
         */
        virtual bool notifyObservers(Device::MeasurementType measurement) = 0;
    };
}

#endif // IMeasurementDataStore_H_
