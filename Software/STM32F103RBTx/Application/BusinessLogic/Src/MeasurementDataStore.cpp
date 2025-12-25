#include "BusinessLogic/Inc/MeasurementDataStore.hpp"
#include "Device/Inc/MeasurementType.hpp"

#include <algorithm>
#include <iterator> // for std::begin std::end

namespace BusinessLogic
{
    bool MeasurementDataStore::initialize()
    {
        bool status = true;

        // abort on first fail
        for (auto &observer : observers)
        {
            if (observer != nullptr)
            {
                status = observer->initialize();
                if (!status)
                {
                    break;
                }
            }
        }

        return status;
    }

    bool MeasurementDataStore::start()
    {
        bool status = true;

        // abort on first fail
        for (auto &observer : observers)
        {
            if (observer != nullptr)
            {
                status = observer->start();
                if (!status)
                {
                    break;
                }
            }
        }

        return status;
    }

    bool MeasurementDataStore::addObserver(Device::IMeasurementRecorder &observer)
    {
        bool status = false;

        if (auto *it = std::find(std::begin(observers), std::end(observers), nullptr); it != std::end(observers))
        {
            *it = &observer;
            status = true;
        }

        return status;
    }

    bool MeasurementDataStore::removeObserver(Device::IMeasurementRecorder &observer)
    {
        bool status = false;

        if (auto *it = std::find(std::begin(observers), std::end(observers), &observer); it != std::end(observers))
        {
            // Use std::move to shift remaining elements left.
            std::move(std::next(it), std::end(observers), it);

            // Clear the last slot using std::prev to avoid 'end - 1' arithmetic
            *std::prev(std::end(observers)) = nullptr;
            status = true;
        }

        return status;
    }

    bool MeasurementDataStore::notifyObservers(Device::MeasurementType measurement)
    {
        bool status = true;

        for (auto &observer : observers)
        {
            if (observer != nullptr)
            {
                status &= observer->notify(measurement);
            }
        }

        return status;
    }
}
