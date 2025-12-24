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
        // clang-format off
        const bool status = wifiRecorder.initialize() 
                            && sdCardRecorder.initialize() 
                            && cacheRecorder.initialize() 
                            && wifiRecorder.start();
        // clang-format on

        return status;
    }

    bool MeasurementStoresFactory::registerStores(MeasurementDataStore &coordinator)
    {
        // clang-format off
        const bool status = coordinator.addObserver(wifiRecorder) 
                            && coordinator.addObserver(sdCardRecorder)
                            && coordinator.addObserver(cacheRecorder);
        // clang-format on

        return status;
    }
}
