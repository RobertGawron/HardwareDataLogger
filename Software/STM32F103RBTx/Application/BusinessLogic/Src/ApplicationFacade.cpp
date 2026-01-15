module;

#include <functional>

module BusinessLogic.ApplicationFacade;

import BusinessLogic.ApplicationComponent;
import BusinessLogic.MeasurementCoordinator;
import BusinessLogic.HmiFacade;

import Device;

import Driver.PlatformFactory;

namespace BusinessLogic
{
    ApplicationFacade::ApplicationFacade(Driver::PlatformFactory &drivers) noexcept
        : pulseCounter1{Device::MeasurementDeviceId::PULSE_COUNTER_1, drivers.counter1},
          pulseCounter2{Device::MeasurementDeviceId::PULSE_COUNTER_2, drivers.counter2},
          pulseCounter3{Device::MeasurementDeviceId::PULSE_COUNTER_3, drivers.counter3},
          pulseCounter4{Device::MeasurementDeviceId::PULSE_COUNTER_4, drivers.counter4},
          uartReceiver{Device::MeasurementDeviceId::DEVICE_UART_1, drivers.measurementUart},
          sources{std::ref(pulseCounter1), std::ref(pulseCounter2),
                  std::ref(pulseCounter3), std::ref(pulseCounter4),
                  std::ref(uartReceiver)},
          wifiRecorder{drivers.wifiUart},
          sdCardRecorder{drivers.sdCard},
          recorders{std::ref(wifiRecorder), std::ref(sdCardRecorder)},
          measurementCoordinator{sources, recorders},
          display{drivers.display},
          brightness{drivers.LightSensor, drivers.displayBrightness},
          keyboard{drivers.keyboard},
          hmi{display, brightness, keyboard}
    {
    }

    auto ApplicationFacade::onInit() noexcept -> bool
    {
        return measurementCoordinator.init();
    }

    auto ApplicationFacade::onStart() noexcept -> bool
    {
        return measurementCoordinator.start();
    }

    auto ApplicationFacade::onStop() noexcept -> bool
    {
        return measurementCoordinator.stop();
    }

    auto ApplicationFacade::onTick() noexcept -> bool
    {
        return measurementCoordinator.tick();
    }

} // namespace BusinessLogic