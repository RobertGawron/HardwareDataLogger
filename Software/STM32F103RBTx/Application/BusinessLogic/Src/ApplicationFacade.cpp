module;

#include <functional>

module BusinessLogic.ApplicationFacade;

import BusinessLogic.ApplicationComponent;
import BusinessLogic.MeasurementCoordinator;
import BusinessLogic.HmiFacade;

import BusinessLogic.TickDelegate;

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
          measurement{sources, recorders},
          display{drivers.display},
          brightness{drivers.lightSensor, drivers.displayBrightness},
          keyboard{drivers.keyboard},
          hmi{display, brightness, keyboard},

          registry{TickDelegate(measurement), TickDelegate(hmi)},
          scheduler{Scheduler::Config{slotTable, registry, 2U}}
    {
    }

    auto ApplicationFacade::onInit() noexcept -> bool
    {
        // todo
        bool status = true;

        measurement.init();
        hmi.init();

        status = scheduler.bindTask(TaskId::MEASUREMENT, measurement) && status;
        status = scheduler.bindTask(TaskId::HMI, hmi) && status;

        status = scheduler.start() && status;

        return true;
    }

    auto ApplicationFacade::onStart() noexcept -> bool
    {
        // dont have storage card , wokaround
        bool status = measurement.start();
        status = hmi.start();
        return status;

        //    return measurement.start() && hmi.start();
    }

    auto ApplicationFacade::onStop() noexcept -> bool
    {
        return measurement.stop() && hmi.stop();
    }

    auto ApplicationFacade::onTick() noexcept -> bool
    {
        scheduler.runPending();
        return true;
        // return measurement.tick() && hmi.tick();
    }

} // namespace BusinessLogic