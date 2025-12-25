/**
 * @file MeasurementCoordinator.hpp
 * @brief Defines the MeasurementCoordinator class which manages the coordination between
 *        measurement sources and storage.
 */

#ifndef MeasurementCoordinator_h
#define MeasurementCoordinator_h

#include "Device/Interface/IMeasurementSource.hpp"
#include "Device/Interface/IMeasurementRecorder.hpp"

#include <cstdint>
#include <array>
#include <functional>
#include <algorithm>

namespace BusinessLogic
{
    template <std::size_t SourceCount, std::size_t RecorderCount>
    class MeasurementCoordinator
    {
    public:
        /**
         * @brief Constructs a MeasurementCoordinator with references to sources and recorders arrays.
         */
        MeasurementCoordinator(
            std::array<std::reference_wrapper<Device::IMeasurementSource>, SourceCount> &sourcesArray,
            std::array<std::reference_wrapper<Device::IMeasurementRecorder>, RecorderCount> &recordersArray)
            : sources(sourcesArray), recorders(recordersArray)
        {
        }

        /**
         * @brief Deleted default constructor to prevent instantiation without a storage reference.
         */
        MeasurementCoordinator() = delete;

        /**
         * @brief Default destructor for MeasurementCoordinator.
         */
        virtual ~MeasurementCoordinator() = default;

        /**
         * @brief Deleted copy constructor to prevent copying of MeasurementCoordinator.
         */
        MeasurementCoordinator(const MeasurementCoordinator &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment of MeasurementCoordinator.
         *
         * @return Reference to the MeasurementCoordinator instance.
         */
        MeasurementCoordinator &operator=(const MeasurementCoordinator &) = delete;

        /**
         * @brief Initializes the MeasurementCoordinator and its registered measurement sources.
         *
         * This function sets up the coordinator and prepares all registered sources for gathering measurements.
         *
         * @return True if initialization was successful; false otherwise.
         */
        virtual bool initialize()
        {
            // Initialize all sources
            bool status = std::all_of(sources.begin(), sources.end(),
                                      [](auto &source)
                                      { return source.get().initialize(); });

            if (status)
            {
                // Initialize all recorders
                status = std::all_of(recorders.begin(), recorders.end(),
                                     [](auto &recorder)
                                     { return recorder.get().initialize(); });
            }

            return status;
        }

        virtual bool start()
        {
            bool status = true;

            for (auto &source : sources)
            {
                status &= source.get().start();
            }

            for (auto &recorder : recorders)
            {
                status &= recorder.get().start();
            }
            return status;
        }

        virtual bool stop()
        {
            bool status = true;

            for (auto &source : sources)
            {
                status &= source.get().stop();
            }

            for (auto &recorder : recorders)
            {
                status &= recorder.get().stop();
            }

            return status;
        }

        /**
         * @brief Periodic function that should be called to perform regular updates.
         *
         * This function handles tasks that need to be performed periodically, such as updating measurements
         * and notifying observers about the availability of new data.
         *
         * @return True if the tick operation was successful, false otherwise.
         */
        virtual bool tick()
        {
            bool status = true;

            // Check each source for available measurements
            for (auto &source : sources)
            {
                if (source.get().isMeasurementAvailable())
                {
                    Device::MeasurementType measurement = source.get().getMeasurement();

                    // Notify all recorders
                    for (auto &recorder : recorders)
                    {
                        status &= recorder.get().notify(measurement);
                    }
                }
            }

            return status;
        }

    private:
        std::array<std::reference_wrapper<Device::IMeasurementSource>, SourceCount> &sources;
        std::array<std::reference_wrapper<Device::IMeasurementRecorder>, RecorderCount> &recorders;
    };
}

#endif // MeasurementCoordinator_h
