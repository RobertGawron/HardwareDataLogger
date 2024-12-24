#include "BusinessLogic/Interfaces/IMeasurementDataStore.hpp"
#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"
#include "Device/Inc/MeasurementType.hpp"

#include <array>
#include <cstddef>

namespace BusinessLogic
{
    MeasurementCoordinator::MeasurementCoordinator(IMeasurementDataStore &_storage)
        : storage(_storage)
    {
        observers.fill(nullptr); // Initialize to nullptr
    }

    bool MeasurementCoordinator::initialize()
    {
        bool status = true;

        for (auto *observer : observers)
        {
            if (observer == nullptr)
            {
                status = true;
                break;
            }

            if (!observer->initialize())
            {
                status = false;
                break;
            }

            if (!observer->start())
            {
                status = false;
                break;
            }
        }

        return status;
    }

    bool MeasurementCoordinator::tick()
    {
        updateMeasurements();
        bool status = true;
        return status;
    }

    void MeasurementCoordinator::updateMeasurements()
    {
        for (auto *observer : observers)
        {
            if (observer == nullptr)
            {
                break;
            }

            if (observer->isMeasurementAvailable())
            {
                const Device::MeasurementType measurement = observer->getMeasurement();
                storage.notifyObservers(measurement);
            }
        }
    }

    bool MeasurementCoordinator::addObserver(Device::IMeasurementSource &observer)
    {
        bool status = true;

        auto it = std::find(observers.begin(), observers.end(), nullptr);
        if (it == observers.end())
        {
            status = false;
        }
        else
        {
            *it = &observer;
        }

        return status;
    }

    bool MeasurementCoordinator::removeObserver(Device::IMeasurementSource &observer)
    {
        bool status = false;
        auto it = std::find(observers.begin(), observers.end(), &observer);
        if (it != observers.end())
        {
            // Shift remaining elements left
            const std::size_t shiftOffset = 1; // Offset to shift remaining elements
            for (auto shiftIt = it; shiftIt != observers.end() - shiftOffset; ++shiftIt)
            {
                *shiftIt = *(shiftIt + shiftOffset);
            }

            *(observers.end() - shiftOffset) = nullptr; // Clear the last slot
            status = true;
        }

        return status;
    }
}
