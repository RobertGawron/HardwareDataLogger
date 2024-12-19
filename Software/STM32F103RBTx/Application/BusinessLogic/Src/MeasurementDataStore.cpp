#include "BusinessLogic/Inc/MeasurementDataStore.hpp"
#include "Device/Inc/MeasurementType.hpp"

#include <cstddef>

namespace BusinessLogic
{
    bool MeasurementDataStore::initialize()
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
        }

        return status;
    }

    bool MeasurementDataStore::start()
    {
        bool status = true;

        // abort on first fail
        for (std::size_t i = 0u; i < observers.size(); i++)
        {
            status = observers[i]->start();

            if (!status)
            {
                break;
            }
        }

        return status;
    }
    bool MeasurementDataStore::addObserver(Device::IMeasurementRecorder &observer)
    {
        const bool status = observers.add(&observer);
        return status;
    }

    bool MeasurementDataStore::removeObserver(Device::IMeasurementRecorder &observer)
    {

        const bool status = observers.remove(&observer);
        return status;
    }

    bool MeasurementDataStore::notifyObservers(Device::MeasurementType measurement)
    {
        for (std::size_t i = 0u; i < observers.size(); i++)
        {
            observers[i]->notify(measurement);
        }

        return true;
    }
}
