module;

#include <cstdint>
#include <array>
#include <algorithm>
#include <variant>

export module BusinessLogic.MeasurementCoordinator;

import BusinessLogic.ApplicationComponent;
import Device;

export namespace BusinessLogic
{
    template <class Range, class F>
    [[nodiscard]] inline bool all_ok(Range &range, F &&f) noexcept
    {
        return std::ranges::all_of(range, [&](auto &v) noexcept
                                   { return std::visit([&](auto &objref) noexcept
                                                       { return f(objref.get()); }, v); });
    }

    template <std::size_t SourceCount, std::size_t RecorderCount>
    class MeasurementCoordinator final : public ApplicationComponent
    {
    public:
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
            return all_ok(sources, [](auto &s) noexcept
                          { return s.init(); }) &&
                   all_ok(recorders, [](auto &r) noexcept
                          { return r.init(); });
        }

        [[nodiscard]] bool onStart() noexcept
        {
            return all_ok(sources, [](auto &s) noexcept
                          { return s.start(); }) &&
                   all_ok(recorders, [](auto &r) noexcept
                          { return r.start(); });
        }

        [[nodiscard]] bool onStop() noexcept
        {
            return all_ok(sources, [](auto &s) noexcept
                          { return s.stop(); }) &&
                   all_ok(recorders, [](auto &r) noexcept
                          { return r.stop(); });
        }

        [[nodiscard]] bool onTick() noexcept
        {
            bool status = true;

            for (auto &sourceVariant : sources)
            {
                std::visit([&](auto &source) noexcept
                           {
                    auto& s = source.get();
                    if (!s.isMeasurementAvailable())
                        return;

                    const Device::MeasurementType measurement = s.getMeasurement();

                    for (auto& recorderVariant : recorders)
                    {
                        std::visit([&](auto& recorder) noexcept {
                            status = status && recorder.get().notify(measurement);
                        }, recorderVariant);
                    } }, sourceVariant);
            }

            return status;
        }

    private:
        std::array<Device::SourceVariant, SourceCount> &sources;
        std::array<Device::RecorderVariant, RecorderCount> &recorders;
    };
}