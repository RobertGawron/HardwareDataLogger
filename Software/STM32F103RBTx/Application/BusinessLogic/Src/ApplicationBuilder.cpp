#include "BusinessLogic/Interfaces/IPlatformFactory.hpp"
#include "BusinessLogic/Inc/ApplicationBuilder.hpp"
#include "Driver/Interfaces/PulseCounterIdentifier.hpp"
#include "Driver/Inc/UartIdentifier.hpp"

namespace BusinessLogic
{

    ApplicationBuilder::ApplicationBuilder(IPlatformFactory &platformFactory)
        : sourceBuilder(platformFactory.createPulseCounterDriver(Driver::PulseCounterIdentifier::bncA),
                        platformFactory.createPulseCounterDriver(Driver::PulseCounterIdentifier::bncB),
                        platformFactory.createPulseCounterDriver(Driver::PulseCounterIdentifier::bncC),
                        platformFactory.createPulseCounterDriver(Driver::PulseCounterIdentifier::bncD),
                        platformFactory.createUartDriver(Driver::UartIdentifier::MeasurementReceiver)),

          storesBuilder(
              cacheRecorder,
              platformFactory.createUartDriver(Driver::UartIdentifier::DataTransmitterViaWiFi),
              platformFactory.createSdCardDriver()),
          measurementCoordinator(dataStore),
          hmiFactory(cacheRecorder, platformFactory)
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

        //  storesBuilder.registerStoresToHmi(hmiFactory);

        return status;
    }

    bool ApplicationBuilder::start()
    {
        // can we recover from fault at any place here? I dont know.
        bool status = false;

        // clang-format off
        if (/*measurementCoordinator.start()
            &&*/ hmiFactory.start())
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

        // clang-format off
        if (measurementCoordinator.tick()
            && hmiFactory.tick())
        // clang-format on
        {
            status = true;
        }

        return status;
    }
} // namespace BusinessLogic
