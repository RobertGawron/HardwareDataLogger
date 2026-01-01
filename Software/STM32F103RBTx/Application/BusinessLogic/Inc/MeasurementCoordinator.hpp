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
#include <span>

namespace BusinessLogic
{
    template <std::size_t SourceCount, std::size_t RecorderCount>
    class MeasurementCoordinator final
    {
    public:
        /**
         * @brief Constructs a MeasurementCoordinator with references to sources and recorders arrays.
         */
        explicit MeasurementCoordinator(
            std::array<std::reference_wrapper<Device::IMeasurementSource>, SourceCount> &sourcesArray,
            std::array<std::reference_wrapper<Device::IMeasurementRecorder>, RecorderCount> &recordersArray) noexcept
            : sources(sourcesArray), recorders(recordersArray)
        {
        }

        MeasurementCoordinator() = delete;
        ~MeasurementCoordinator() = default;

        MeasurementCoordinator(const MeasurementCoordinator &) = delete;
        MeasurementCoordinator &operator=(const MeasurementCoordinator &) = delete;
        MeasurementCoordinator(MeasurementCoordinator &&) = delete;
        MeasurementCoordinator &operator=(MeasurementCoordinator &&) = delete;

        /**
         * @brief Initializes the MeasurementCoordinator and its registered measurement sources.
         * @return True if initialization was successful; false otherwise.
         */
        [[nodiscard]] bool initialize() noexcept
        {
            // Initialize all sources
            const bool sourcesInitialized = std::ranges::all_of(sources,
                                                                [](auto &source)
                                                                { return source.get().initialize(); });

            if (!sourcesInitialized)
            {
                return false;
            }

            // Initialize all recorders
            return std::ranges::all_of(recorders,
                                       [](auto &recorder)
                                       { return recorder.get().initialize(); });
        }

        [[nodiscard]] bool start() noexcept
        {
            const bool sourcesStarted = std::ranges::all_of(sources,
                                                            [](auto &source)
                                                            { return source.get().start(); });

            const bool recordersStarted = std::ranges::all_of(recorders,
                                                              [](auto &recorder)
                                                              { return recorder.get().start(); });

            return sourcesStarted && recordersStarted;
        }

        [[nodiscard]] bool stop() noexcept
        {
            const bool sourcesStopped = std::ranges::all_of(sources,
                                                            [](auto &source)
                                                            { return source.get().stop(); });

            const bool recordersStopped = std::ranges::all_of(recorders,
                                                              [](auto &recorder)
                                                              { return recorder.get().stop(); });

            return sourcesStopped && recordersStopped;
        }

        /**
         * @brief Periodic function that should be called to perform regular updates.
         * @return True if the tick operation was successful, false otherwise.
         */
        [[nodiscard]] bool tick() noexcept
        {
            bool status = true;

            for (auto &source : sources)
            {
                if (source.get().isMeasurementAvailable())
                {
                    const Device::MeasurementType measurement = source.get().getMeasurement();

                    // Notify all recorders
                    for (auto &recorder : recorders)
                    {
                        status = status && recorder.get().notify(measurement);
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