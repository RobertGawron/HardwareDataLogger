#include "BusinessLogic/Inc/MeasurementStoresFactory.hpp"
#include "BusinessLogic/Inc/MeasurementDataStore.hpp"
#include "Device/Inc/CacheMeasurementRecorder.hpp"
#include "Driver/Interface/IUartDriver.hpp"
#include "Driver/Interface/ISdCardDriver.hpp"

namespace BusinessLogic
{

    MeasurementStoresFactory::MeasurementStoresFactory(
        Device::CacheMeasurementRecorder &_cacheRecorder,
        Driver::IUartDriver &uartForWiFi,
        Driver::ISdCardDriver &sdCard)
        : cacheRecorder(_cacheRecorder),
          wifiRecorder(uartForWiFi),
          sdCardRecorder(sdCard)
    {
    }

    bool MeasurementStoresFactory::initialize()
    {
        wifiRecorder.initialize();
        sdCardRecorder.initialize();
        cacheRecorder.initialize();

        int i = 0;
        wifiRecorder.start();

        return true;
    }

    bool MeasurementStoresFactory::registerStores(MeasurementDataStore &coordinator)
    {

        bool status = false;

        // clang-format off
            if (coordinator.addObserver(wifiRecorder) 
                && coordinator.addObserver(sdCardRecorder)
                && coordinator.addObserver(cacheRecorder))
        // clang-format on
        {
            status = true;
        }

        return status;
    }
}
