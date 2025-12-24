#include "BusinessLogic/Interface/IMeasurementDataStore.hpp"
#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"
#include "Device/Inc/MeasurementType.hpp"

#include <array>
#include <algorithm>
#include <iterator>

namespace BusinessLogic
{
    MeasurementCoordinator::MeasurementCoordinator(IMeasurementDataStore &_storage)
        : storage(_storage)
    {
        observers.fill(nullptr);
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
        const bool status = updateMeasurements();
        return status;
    }

    bool MeasurementCoordinator::updateMeasurements()
    {
        bool status = true;

        for (auto *observer : observers)
        {
            if (observer == nullptr)
            {
                break;
            }

            if (observer->isMeasurementAvailable())
            {
                const Device::MeasurementType measurement = observer->getMeasurement();
                status &= storage.notifyObservers(measurement);
            }
        }

        return status;
    }

    bool MeasurementCoordinator::addObserver(Device::IMeasurementSource &observer)
    {
        bool status = false;

        if (auto *it = std::find(observers.begin(), observers.end(), nullptr); it != observers.end())
        {
            *it = &observer;
            status = true;
        }

        return status;
    }

    bool MeasurementCoordinator::removeObserver(Device::IMeasurementSource &observer)
    {
        bool status = false;

        if (auto *it = std::find(observers.begin(), observers.end(), &observer); it != observers.end())
        {
            // Use std::move to shift elements left.
            std::move(std::next(it), observers.end(), it);

            // Clear the last slot (which is now a duplicate of the 2nd to last)
            observers.back() = nullptr;

            status = true;
        }

        return status;
    }
}
