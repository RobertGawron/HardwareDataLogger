#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"
#include "BusinessLogic/Inc/MeasurementDataStore.hpp"

#include <cstdint>
#include <stdio.h>

namespace BusinessLogic
{

    MeasurementCoordinator::MeasurementCoordinator(IMeasurementDataStore &_storage) : storage(_storage)
    {
    }

    bool MeasurementCoordinator::initialize()
    {
        bool status = true;

        // abort on first fail
        for (std::size_t i = 0u; i < observers.size(); i++)
        {
            status = observers[i]->initialize();

            if (!status)
            {
                break;
            }

            status = observers[i]->start();

            if (!status)
            {
                break;
            }
        }

        return status;
    }

    bool MeasurementCoordinator::tick()
    {
        updateMeasurements();

        return true;
    }

    // Updates measurements from all devices
    void MeasurementCoordinator::updateMeasurements()
    {
        for (std::size_t i = 0u; i < observers.size(); i++)
        {
            const bool isMeasurementReady = observers[i]->isMeasurementAvailable();

            if (isMeasurementReady)
            {

                Device::MeasurementType measurement = observers[i]->getMeasurement();
                storage.notifyObservers(measurement);

                //  printf("updateMeasurements() %d\n", measurement);
            }
        }
    }

    // Register an input device observer
    bool MeasurementCoordinator::addObserver(Device::IMeasurementSource &observer)
    {
        const bool status = observers.add(&observer);
        return status;
    }

    bool MeasurementCoordinator::removeObserver(Device::IMeasurementSource &observer)
    {
        const bool status = observers.remove(&observer);
        return status;
    }
}
