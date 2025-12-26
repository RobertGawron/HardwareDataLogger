#include "BusinessLogic/Interface/IPlatformFactory.hpp"
#include "BusinessLogic/Inc/ApplicationFacade.hpp"
/*
#include "Driver/Interface/PulseCounterId.hpp"
#include "Driver/Interface/UartId.hpp"
*/
#include "Device/Inc/PulseCounterMeasurementSource.hpp"
#include "Driver/Interface/IPulseCounterDriver.hpp"
#include "Device/Inc/UartMeasurementSource.hpp"
#include "Driver/Interface/IUartDriver.hpp"
namespace BusinessLogic
{
    // In ApplicationFacade.cpp
    ApplicationFacade::ApplicationFacade(IPlatformFactory &platformFactory)

        : pulseCounter1(Device::MeasurementDeviceId::PULSE_COUNTER_1,
                        platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncA)),
          pulseCounter2(Device::MeasurementDeviceId::PULSE_COUNTER_2,
                        platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncB)),
          pulseCounter3(Device::MeasurementDeviceId::PULSE_COUNTER_3,
                        platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncC)),
          pulseCounter4(Device::MeasurementDeviceId::PULSE_COUNTER_4,
                        platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncC)),
          uartReceiver(Device::MeasurementDeviceId::DEVICE_UART_1,
                       platformFactory.getUartDriver(Driver::UartId::MEASUREMENT_RECEIVER)),
          wifiRecorder(platformFactory.getUartDriver(Driver::UartId::TRANSMIT_VIA_WIFI)),
          sdCardRecorder(platformFactory.getSdCardDriver()),
          sources{pulseCounter1, pulseCounter2, pulseCounter3, pulseCounter4, uartReceiver},
          recorders{wifiRecorder, sdCardRecorder},
          display(platformFactory.getDisplayDriver()),
          brightnessRegulator(
              platformFactory.getAmbientLightSensorDriver(),
              platformFactory.getDisplayBrightnessDriver()),
          keyboard(platformFactory.getKeyboardDriver()),
          hmi(display,
              brightnessRegulator,
              keyboard),
          measurementCoordinator(sources, recorders)
    {
    }
    /*
        ApplicationFacade::ApplicationFacade(IPlatformFactory &platformFactory)
            : pulseCounters{
                  Device::PulseCounterMeasurementSource(
                      Device::MeasurementDeviceId::PULSE_COUNTER_1,
                      platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncA)),
                  Device::PulseCounterMeasurementSource(
                      Device::MeasurementDeviceId::PULSE_COUNTER_2,
                      platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncB)),
                  Device::PulseCounterMeasurementSource(
                      Device::MeasurementDeviceId::PULSE_COUNTER_3,
                      platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncC)),
                  Device::PulseCounterMeasurementSource(
                      Device::MeasurementDeviceId::PULSE_COUNTER_4,
                      platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncC))}
      */

    /*      : sourceBuilder(platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncA),
            platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncB),
            platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncC),
            platformFactory.getPulseCounterDriver(Driver::PulseCounterId::bncD),
            platformFactory.getUartDriver(Driver::UartId::MEASUREMENT_RECEIVER)),

storesBuilder(
  cacheRecorder,
  platformFactory.getUartDriver(Driver::UartId::TRANSMIT_VIA_WIFI),
  platformFactory.getSdCardDriver()),
measurementCoordinator(dataStore),
hmiFactory(cacheRecorder, platformFactory)
*/
    //  {
    //  }

    bool ApplicationFacade::initialize()
    {
        measurementCoordinator.initialize();
        /* for (auto &source : sources)
         {
             source.get().initialize();
         }

         for (auto &recorder : recorders)
         {
             recorder.get().initialize();
         }*/

        // can we recover from fault at any place here? I dont know.
        /*
                // clang-format off
                const bool status = sourceBuilder.initialize()
                                    && storesBuilder.initialize()
                                    && dataStore.initialize()
                                    && measurementCoordinator.initialize()
                                    && hmiFactory.initialize()
                                    && sourceBuilder.registerSources(measurementCoordinator)
                                    && storesBuilder.registerStores(dataStore);
                // clang-format on

                //  storesBuilder.registerStoresToHmi(hmiFactory);

                return status;
          */
        return true;
    }

    bool ApplicationFacade::start()
    {
        measurementCoordinator.start();
        /*
        for (auto &source : sources)
        {
            source.get().start();
        }

        for (auto &recorder : recorders)
        {
            recorder.get().start();
        }*/
        /*
        // can we recover from fault at any place here? I dont know.
        bool status = hmiFactory.start();

        return status;
        */
        return true;
    }

    bool ApplicationFacade::stop()
    {
        measurementCoordinator.stop();
        /*
        for (auto &source : sources)
        {
            source.get().stop();
        }

        for (auto &recorder : recorders)
        {
            recorder.get().stop();
        }*/

        return true;
    }

    bool ApplicationFacade::tick()
    {

        measurementCoordinator.tick();
        /*
        for (auto &source : sources)
        {
            if (source.get().isMeasurementAvailable())
            {
                // const
                Device::MeasurementType measurement = source.get().getMeasurement();

                for (auto &recorder : recorders)
                {
                    recorder.get().notify(measurement);
                }
            }
        }*/

        /*
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

        */

        /*
        // can we recover from fault at any place here? I dont know.
        bool status = false;

        // clang-format off
        if (measurementCoordinator.tick()
            && hmiFactory.tick())
        // clang-format on
        {
            status = true;
        }

        return status;
        */
        return true;
    }
} // namespace BusinessLogic
