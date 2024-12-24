#include "BusinessLogic/Inc/MeasurementDataStore.hpp"
#include "Device/Inc/MeasurementType.hpp"

#include <cstddef>
#include <algorithm>

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

        auto it = std::find(std::begin(observers), std::end(observers), nullptr);
        if (it != std::end(observers))
        {
            *it = &observer;
            status = true;
        }

        return status;
    }

    bool MeasurementDataStore::removeObserver(Device::IMeasurementRecorder &observer)
    {
        bool status = false;
        const std::size_t shiftOffset = 1; // Offset to shift remaining elements

        auto it = std::find(std::begin(observers), std::end(observers), &observer);
        if (it != std::end(observers))
        {
            // Shift remaining elements to the left
            for (auto shiftIt = it; shiftIt != std::end(observers) - shiftOffset; ++shiftIt)
            {
                *shiftIt = *(shiftIt + shiftOffset);
            }
            *(std::end(observers) - shiftOffset) = nullptr; // Clear the last slot
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
                observer->notify(measurement);
            }
        }

        return status;
    }
}
