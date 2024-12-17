#include "BusinessLogic/Inc/ApplicationBuilder.hpp"
#include "Driver/Inc/PulseCounterIdentifier.hpp"
#include "Driver/Inc/UartIdentifier.hpp"

#include "BusinessLogic/Interfaces/IPlatformFactory.hpp"

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
          measurementCoordinator(dataStore),
          hmiFactory(platformFactory)
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
                    && hmiFactory.initialize())
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

        // clang-format off
        if (dataStore.start()
            && hmiFactory.start())
        // clang-format on
        {
            status = true;
        }

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
        if (/*measurementCoordinator.tick()*/
             
            hmiFactory.tick())
        // clang-format on
        {
            status = true;
        }

        return status;
    }
} // namespace BusinessLogic
