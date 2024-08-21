/**
 * @file MeasurementDataStore.hpp
 * @brief Defines the MeasurementDataStore class which manages the storage of measurement data
 *        using the observer pattern.
 */

#ifndef MeasurementDataStore_H_
#define MeasurementDataStore_H_

#include "IMeasurementRecorder.hpp"
#include "SaferArray.hpp"
#include <stdint.h>

namespace BusinessLogic
{
    /**
     * @class MeasurementDataStore
     * @brief Implements the observer pattern to manage a collection of measurement recorders.
     *
     * This class allows clients to add or remove observers that store measurement data.
     * Observers can represent different storage methods such as SD card, Wi-Fi, UART, etc.
     * It is responsible for initializing and notifying all registered observers when new
     * measurement data is ready.
     */
    class MeasurementDataStore
    {
    public:
        /**
         * @brief Default constructor for MeasurementDataStore.
         */
        explicit MeasurementDataStore() = default;

        /**
         * @brief Destructor for MeasurementDataStore.
         */
        virtual ~MeasurementDataStore() = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        MeasurementDataStore(const MeasurementDataStore &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return MeasurementDataStore& The assigned object.
         */
        MeasurementDataStore &operator=(const MeasurementDataStore &) = delete;

        /**
         * @brief Adds an observer that records measurement data.
         *
         * The observer should implement the IMeasurementRecorder interface, and this method will
         * add it to the list of observers managed by the MeasurementDataStore.
         *
         * @param observer Reference to an object that implements IMeasurementRecorder.
         * @return True if the observer was successfully added; false otherwise.
         */
        bool addObserver(Device::IMeasurementRecorder &observer);

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
        bool removeObserver(Device::IMeasurementRecorder &observer);

        /**
         * @brief Initializes the MeasurementDataStore and all registered observers.
         *
         * This function initializes the MeasurementDataStore and all the objects
         * registered via addObserver().
         *
         * @return True if initialization was successful; false otherwise.
         * @note Observers should not be initialized manually in other classes such as ApplicationBuilder.
         */
        bool initialize();

        /**
         * @brief Starts the MeasurementDataStore and all registered observers.
         *
         * This function starts the MeasurementDataStore and prepares all registered observers to start
         * recording measurement data.
         *
         * @return True if start was successful; false otherwise.
         */
        bool start();

        /**
         * @brief Notifies all registered observers that new measurement data is ready to be stored.
         *
         * This function iterates through the list of registered observers and notifies each one
         * that new measurement data is available for storage.
         */
        void notifyObservers();

    private:
        /** @brief Maximum number of observers that can be registered. */
        static const uint8_t MaxObservers{4u};

        /** @brief Array to store references to registered observers. */
        SaferArray<Device::IMeasurementRecorder, MaxObservers> observers;
    };
}

#endif // MeasurementDataStore_H_