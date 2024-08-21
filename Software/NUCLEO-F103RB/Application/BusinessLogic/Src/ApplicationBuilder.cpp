#include "ApplicationBuilder.hpp"
#include "PulseCounterIdentifier.hpp"
#include "UartIdentifier.hpp"

namespace BusinessLogic
{

    ApplicationBuilder::ApplicationBuilder(IPlatformFactory &platformFactory)
        : sourceBuilder(platformFactory.createPulseCounterDriver(Driver::PulseCounterIdentifier::bncA),
                        platformFactory.createPulseCounterDriver(Driver::PulseCounterIdentifier::bncB),
                        platformFactory.createPulseCounterDriver(Driver::PulseCounterIdentifier::bncC),
                        platformFactory.createPulseCounterDriver(Driver::PulseCounterIdentifier::bncD),
                        platformFactory.createUartDriver(Driver::UartIdentifier::MeasurementReceiver)),

          storesBuilder(platformFactory.createUartDriver(Driver::UartIdentifier::DataTransmitterViaWiFiModule),
                        platformFactory.createSdCardDriver()),

          dataStore(),
          measurementCoordinator(dataStore),

          hmiFactory(platformFactory),
          hmiBuilder(hmiFactory)

    {
    }

    bool ApplicationBuilder::initialize()
    {
        // can we recover from fault at any place here? I dont know.
        bool status = false;

        // clang-format off
                if ( sourceBuilder.initialize()
                    && storesBuilder.initialize()
                    && dataStore.initialize()
                    && measurementCoordinator.initialize()
                    && hmiBuilder.initialize()
                    /*&& */)
        // clang-format on
        {
            status = true;
        }

        sourceBuilder.registerSources(measurementCoordinator);
        storesBuilder.registerStores(dataStore);

        return status;
    }

    bool ApplicationBuilder::start()
    {
        // can we recover from fault at any place here? I dont know.
        bool status = false;

        dataStore.start();
        hmiBuilder.start();
        /*
                // clang-format off
                if (
                   // && measurementCoordinator.start()
                    && )
                // clang-format on
                {
                    status = true;
                }
        */
        return status;
    }

    bool ApplicationBuilder::stop()
    {
        return true;
    }

    bool ApplicationBuilder::tick()
    {
        // can we recover from fault at any place here? I dont know.
        bool status = false;

        dataStore.notifyObservers();
        // clang-format off
                if (/*measurementCoordinator.tick()
                    &&*/ hmiBuilder.tick())
        // clang-format on
        {
            status = true;
        }

        return status;
    }
} // namespace BusinessLogic
