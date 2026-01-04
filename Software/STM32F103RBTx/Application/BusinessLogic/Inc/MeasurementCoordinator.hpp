/**
 * @file MeasurementCoordinator.hpp
 * @brief Defines the MeasurementCoordinator class which manages the coordination between
 *        measurement sources and storage.
 */

#ifndef MeasurementCoordinator_h
#define MeasurementCoordinator_h

#include "BusinessLogic/Inc/ApplicationComponent.hpp"
#include "Device/Inc/RecorderVariant.hpp"
#include "Device/Inc/SourceVariant.hpp"
#include "Device/Inc/MeasurementSource.hpp"
#include "Device/Inc/WiFiRecorder.hpp"
#include "Device/Inc/SdCardRecorder.hpp"

#include <cstdint>
#include <array>
#include <functional>
#include <algorithm>
#include <span>
#include <variant>

namespace BusinessLogic
{

    template <std::size_t SourceCount, std::size_t RecorderCount>
    class MeasurementCoordinator final : public ApplicationComponent
    {
    public:
        /**
         * @brief Constructs a MeasurementCoordinator with references to sources and recorders arrays.
         */
        explicit MeasurementCoordinator(
            std::array<Device::SourceVariant, SourceCount> &sourcesArray,
            std::array<Device::RecorderVariant, RecorderCount> &recordersArray) noexcept
            : sources(sourcesArray), recorders(recordersArray)
        {
        }

        MeasurementCoordinator() = delete;
        ~MeasurementCoordinator() = default;

        MeasurementCoordinator(const MeasurementCoordinator &) = delete;
        MeasurementCoordinator &operator=(const MeasurementCoordinator &) = delete;
        MeasurementCoordinator(MeasurementCoordinator &&) = delete;
        MeasurementCoordinator &operator=(MeasurementCoordinator &&) = delete;

        [[nodiscard]] bool onInit() noexcept
        {
            bool status = std::ranges::all_of(
                sources,
                [](auto &sourceVariant)
                {
                    return std::visit([](auto &source)
                                      { return source.get().init(); }, sourceVariant);
                });

            if (status)
            {
                status = std::ranges::all_of(
                    recorders,
                    [](auto &recorderVariant)
                    {
                        return std::visit([](auto &recorder)
                                          { return recorder.get().init(); }, recorderVariant);
                    });
            }

            return status;
        }

        [[nodiscard]] bool onStart() noexcept
        {
            bool status = std::ranges::all_of(
                sources,
                [](auto &sourceVariant)
                {
                    return std::visit([](auto &source)
                                      { return source.get().start(); }, sourceVariant);
                });

            if (status)
            {
                status = std::ranges::all_of(
                    recorders,
                    [](auto &recorderVariant)
                    {
                        return std::visit([](auto &recorder)
                                          { return recorder.get().start(); }, recorderVariant);
                    });
            }

            return status;
        }

        [[nodiscard]] bool stop() noexcept
        {
            bool status = std::ranges::all_of(
                sources,
                [](auto &sourceVariant)
                {
                    return std::visit([](auto &source)
                                      { return source.get().stop(); }, sourceVariant);
                });

            if (status)
            {
                status = std::ranges::all_of(
                    recorders,
                    [](auto &recorderVariant)
                    {
                        return std::visit([](auto &recorder)
                                          { return recorder.get().stop(); }, recorderVariant);
                    });
            }
            return status;
        }

        [[nodiscard]] bool onTick() noexcept
        {
            bool status = true;

            for (auto &sourceVariant : sources)
            {
                std::visit([&](auto &source)
                           {
                if (source.get().isMeasurementAvailable())
                {
                    const Device::MeasurementType measurement = source.get().getMeasurement();

                    for (auto &recorderVariant : recorders)
                    {
                        std::visit([&measurement, &status](auto &recorder) {
                            status = status && recorder.get().notify(measurement);
            return status;
                        }, recorderVariant);
                    }
                } }, sourceVariant);
            }

            return status;
        }

    private:
        std::array<Device::SourceVariant, SourceCount> &sources;
        std::array<Device::RecorderVariant, RecorderCount> &recorders;
    };
}

#endif // MeasurementCoordinator_h