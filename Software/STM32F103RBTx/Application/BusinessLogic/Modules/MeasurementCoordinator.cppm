module;

#include <cstdint>
#include <array>
#include <variant>
#include <ranges>
#include <functional>

export module BusinessLogic.MeasurementCoordinator;

import BusinessLogic.ApplicationComponent;
import Device;

export namespace BusinessLogic
{
    // ------------------------------------------------------------
    // visit_range : applies f(obj) for each concrete object
    // ------------------------------------------------------------
    template <std::ranges::forward_range Range, class F>
    inline auto visit_range(Range &range, F &&f) noexcept -> void
    {
        for (auto &element : range)
        {
            std::visit(
                [&](auto &ref) noexcept
                {
                    f(ref.get());
                },
                element);
        }
    }

    // ------------------------------------------------------------
    // reduce_range : boolean AND aggregation
    // ------------------------------------------------------------
    template <std::ranges::forward_range Range, class F>
    [[nodiscard]] inline auto reduce_range(Range &range, F &&f) noexcept -> bool
    {
        bool result{true};

        visit_range(range,
                    [&](auto &obj) noexcept
                    {
                        result = result && std::invoke(f, obj);
                    });

        return result;
    }

    // ------------------------------------------------------------
    // MeasurementCoordinator
    // ------------------------------------------------------------
    template <
        std::ranges::forward_range SourceRange,
        std::ranges::forward_range RecorderRange>
    class MeasurementCoordinator final : public ApplicationComponent
    {
    public:
        constexpr MeasurementCoordinator(
            SourceRange &sourcesRange,
            RecorderRange &recordersRange) noexcept
            : sources(sourcesRange),
              recorders(recordersRange)
        {
        }

        MeasurementCoordinator() = delete;
        ~MeasurementCoordinator() = default;

        MeasurementCoordinator(const MeasurementCoordinator &) = delete;
        MeasurementCoordinator(MeasurementCoordinator &&) = delete;
        MeasurementCoordinator &operator=(const MeasurementCoordinator &) = delete;
        MeasurementCoordinator &operator=(MeasurementCoordinator &&) = delete;

        [[nodiscard]] auto onInit() noexcept -> bool
        {
            bool result{true};

            result = result && reduce_range(sources,
                                            [](auto &obj) noexcept
                                            { return obj.init(); });

            result = result && reduce_range(recorders,
                                            [](auto &obj) noexcept
                                            { return obj.init(); });

            return result;
        }

        [[nodiscard]] auto onStart() noexcept -> bool
        {
            bool result{true};

            result = result && reduce_range(sources,
                                            [](auto &obj) noexcept
                                            { return obj.start(); });

            result = result && reduce_range(recorders,
                                            [](auto &obj) noexcept
                                            { return obj.start(); });

            return result;
        }

        [[nodiscard]] auto onStop() noexcept -> bool
        {
            bool result{true};

            result = result && reduce_range(sources,
                                            [](auto &obj) noexcept
                                            { return obj.stop(); });

            result = result && reduce_range(recorders,
                                            [](auto &obj) noexcept
                                            { return obj.stop(); });

            return result;
        }

        [[nodiscard]] auto onTick() noexcept -> bool
        {
            bool status{true};

            visit_range(sources,
                        [&](auto &source) noexcept
                        {
                            if (source.isMeasurementAvailable())
                            {
                                const auto measurement = source.getMeasurement();

                                visit_range(recorders,
                                            [&](auto &recorder) noexcept
                                            {
                                                status = status &&
                                                         recorder.notify(measurement);
                                            });
                            }
                        });

            return status;
        }

    private:
        SourceRange &sources;
        RecorderRange &recorders;
    };
}