module;

#include <array>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <thread>

export module Simulation.PulseCounterScheduler;

import Driver.PulseCounterDriver;

export namespace Simulation
{
    class PulseCounterScheduler
    {
    public:
#warning Magic number
        static constexpr std::size_t CounterCount = 4;

        PulseCounterScheduler()
        {
            for (std::size_t i = 0; i < CounterCount; ++i)
            {
                workers[i] = std::jthread([this, i](std::stop_token st)
                                          { workerLoop(static_cast<std::uint8_t>(i), st); });
            }
        }

        bool updateFrequency(std::uint8_t counterId,
                             std::uint32_t newPulsesPerMinute)
        {
            bool status = false;

            if (counterId < CounterCount)
            {
                frequencies[counterId].store(newPulsesPerMinute, std::memory_order_relaxed);
                status = true;
            }

            return status;
        }

    private:
        void workerLoop(std::uint8_t counterId, std::stop_token stopToken)
        {
            using namespace std::chrono;

            while (!stopToken.stop_requested())
            {
                const auto ppm = frequencies[counterId].load(std::memory_order_relaxed);

                if (ppm > 0U)
                {
                    const auto interval = milliseconds(60000 / ppm);

                    incrementPulseCounter(counterId);

                    std::this_thread::sleep_for(interval);
                }
                else
                {
                    // If frequency is 0 -> idle sleep
                    std::this_thread::sleep_for(milliseconds(100));
                }
            }
        }

    private:
        std::array<std::jthread, CounterCount> workers{};
        std::array<std::atomic<std::uint32_t>, CounterCount> frequencies{};
    };

}