#include "BusinessLogic/Inc/MeasurementStoresFactory.hpp"
#include "Device/Interfaces/IMeasurementRecorder.hpp"
namespace BusinessLogic
{

    MeasurementStoresFactory::MeasurementStoresFactory(Driver::IUartDriver &uartForWiFi,
                                                       Driver::ISdCardDriver &sdCard)
        : wifiRecorder(uartForWiFi),
          sdCardRecorder(sdCard)
    {
    }

    bool MeasurementStoresFactory::initialize()
    {
        wifiRecorder.initialize();
        sdCardRecorder.initialize();

        return true;
    }

    bool MeasurementStoresFactory::registerStores(MeasurementDataStore &coordinator)
    {

        bool status = false;

        // clang-format off
        if (coordinator.addObserver(wifiRecorder) 
            && coordinator.addObserver(sdCardRecorder))
        // clang-format on
        {
            status = true;
        }

        return status;
    }
}
