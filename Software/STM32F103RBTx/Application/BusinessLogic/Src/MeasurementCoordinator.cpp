#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"
#include "BusinessLogic/Inc/MeasurementDataStore.hpp"

#include <cstdint>

namespace BusinessLogic
{

    MeasurementCoordinator::MeasurementCoordinator(MeasurementDataStore &_storage) : storage(_storage)
    {
    }

    bool MeasurementCoordinator::initialize()
    {
        bool status = true;

        // abort on first fail
        for (std::size_t i = 0u; (i < observers.size()) && status; i++)
        {
            status &= observers[i]->init();
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
                observers[i]->getMeasurement();
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
