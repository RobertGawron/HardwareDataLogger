module;

#include <array>
#include <cstddef>
#include <functional>
#include <utility>

module BusinessLogic.MeasurementSubsystem;

import BusinessLogic.ApplicationComponent;
import BusinessLogic.MeasurementCoordinator;
import BusinessLogic.EveryNCalls;

import Device;
import Driver.PlatformFactory;

namespace BusinessLogic
{
    MeasurementSubsystem::MeasurementSubsystem(Driver::PlatformFactory &drivers) noexcept
        : pulseCounter1{Device::MeasurementDeviceId::PULSE_COUNTER_1, drivers.counter1},
          pulseCounter2{Device::MeasurementDeviceId::PULSE_COUNTER_2, drivers.counter2},
          pulseCounter3{Device::MeasurementDeviceId::PULSE_COUNTER_3, drivers.counter3},
          pulseCounter4{Device::MeasurementDeviceId::PULSE_COUNTER_4, drivers.counter4},
          uartReceiver{Device::MeasurementDeviceId::DEVICE_UART_1, drivers.measurementUart},
          sources{std::ref(pulseCounter1),
                  std::ref(pulseCounter2),
                  std::ref(pulseCounter3),
                  std::ref(pulseCounter4),
                  std::ref(uartReceiver)},
          wifiRecorder{drivers.wifiUart},
          sdCardRecorder{drivers.sdCard},
          recorders{std::ref(wifiRecorder),
                    std::ref(sdCardRecorder)},
          measurement{sources, recorders},
          measurementEveryMinute{measurement}
    {
    }

    auto MeasurementSubsystem::onInit() noexcept -> bool
    {
        return measurement.init();
    }

    auto MeasurementSubsystem::onStart() noexcept -> bool
    {
        return measurement.start();
    }

    auto MeasurementSubsystem::onStop() noexcept -> bool
    {
        return measurement.stop();
    }

    auto MeasurementSubsystem::onTick() noexcept -> bool
    {
        // Delegates to the throttled wrapper
        return measurementEveryMinute.tick();
    }

} // namespace BusinessLogic