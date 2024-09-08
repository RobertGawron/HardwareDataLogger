#include "BusinessLogic/Inc/MeasurementDataStore.hpp"

namespace BusinessLogic
{
    bool MeasurementDataStore::initialize()
    {
        bool status = true;

        // abort on first fail
        for (int i = 0; (i < observers.size()) && status; i++)
        {
            status &= observers[i]->initialize();
        }

        return status;
    }

    bool MeasurementDataStore::start()
    {
        bool status = true;

        // abort on first fail
        for (int i = 0; (i < observers.size()) && status; i++)
        {
            status &= observers[i]->start();
        }

        return status;
    }
    bool MeasurementDataStore::addObserver(Device::IMeasurementRecorder &observer)
    {
        bool status = observers.add(&observer);
        return status;
    }

    bool MeasurementDataStore::removeObserver(Device::IMeasurementRecorder &observer)
    {

        bool status = observers.remove(&observer);
        return status;
    }

    void MeasurementDataStore::notifyObservers()
    {
        for (int i = 0; i < observers.size(); i++)
        {
            observers[i]->notify();
            // int dummy = 55;
        }
    }

}
