/**
 * @file MeasurementCoordinator.hpp
 * @brief Defines the MeasurementCoordinator class which manages the coordination between
 *        measurement sources and storage.
 */

#ifndef MeasurementCoordinator_h
#define MeasurementCoordinator_h

#include <stdint.h>
#include "Device/Interfaces/IMeasurementSource.hpp"
#include "BusinessLogic/Inc/MeasurementDataStore.hpp"
#include "BusinessLogic/Inc/SaferArray.hpp"

namespace BusinessLogic
{
    /**
     * @class MeasurementCoordinator
     * @brief Coordinates the interaction between input devices (measurement sources) and the
     *        storage mechanism for measurement data.
     *
     * The MeasurementCoordinator class is responsible for registering input devices that provide
     * measurement data, periodically querying them for new data, and then notifying the storage
     * system to store this data. This class employs an observer pattern to manage multiple input
     * devices.
     */
    class MeasurementCoordinator
    {
    public:
        /**
         * @brief Constructs a MeasurementCoordinator with a reference to a MeasurementDataStore.
         *
         * @param storage Reference to a MeasurementDataStore object that handles the storage of measurement data.
         */
        explicit MeasurementCoordinator(MeasurementDataStore &storage);

        /**
         * @brief Deleted default constructor to prevent instantiation without a storage reference.
         */
        MeasurementCoordinator() = delete;

        /**
         * @brief Default destructor for MeasurementCoordinator.
         */
        virtual ~MeasurementCoordinator() = default;

        /**
         * @brief Initializes the MeasurementCoordinator and its registered measurement sources.
         *
         * This function sets up the coordinator and prepares all registered sources for gathering measurements.
         *
         * @return True if initialization was successful; false otherwise.
         */
        virtual bool initialize();

        /**
         * @brief Periodic function that should be called to perform regular updates.
         *
         * This function handles tasks that need to be performed periodically, such as updating measurements
         * and notifying observers about the availability of new data.
         *
         * @return True if the tick operation was successful, false otherwise.
         */
        virtual bool tick();

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        MeasurementCoordinator(const MeasurementCoordinator &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return MeasurementCoordinator& The assigned object.
         */
        MeasurementCoordinator &operator=(const MeasurementCoordinator &) = delete;

        /**
         * @brief Updates measurements from all registered input devices.
         *
         * This function queries all registered measurement sources for new data, processes it,
         * and ensures the data is ready to be stored.
         */
        void updateMeasurements();

        /**
         * @brief Registers an input device observer to be periodically queried for measurement data.
         *
         * The observer should implement the IMeasurementSource interface, and this method will add it
         * to the list of measurement sources managed by the MeasurementCoordinator.
         *
         * @param observer Reference to an object that implements IMeasurementSource.
         * @return True if the observer was successfully added; false otherwise.
         */
        bool addObserver(Device::IMeasurementSource &observer);

        /**
         * @brief Unregisters an input device observer.
         *
         * This method removes an observer from the list of registered measurement sources,
         * stopping it from providing data to the system.
         *
         * @param observer Reference to an object that implements IMeasurementSource.
         * @return True if the observer was successfully removed; false otherwise.
         * @note Removing the observer does not automatically deinitialize it.
         */
        bool removeObserver(Device::IMeasurementSource &observer);

    private:
        /** @brief Maximum number of observers that can be registered. */
        static const uint8_t MaxObservers{5u};

        /** @brief Array to store references to registered measurement source observers. */
        SaferArray<Device::IMeasurementSource, MaxObservers> observers;

        /**
         * @brief Reference to the MeasurementDataStore object responsible for storing measurement data.
         *
         * This member is responsible for notifying the storage objects when new measurement data is ready.
         */
        MeasurementDataStore &storage;
    };
}

#endif // MeasurementCoordinator_h