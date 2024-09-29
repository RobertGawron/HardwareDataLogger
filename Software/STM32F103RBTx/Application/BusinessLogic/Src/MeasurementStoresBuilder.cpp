#include "BusinessLogic/Inc/MeasurementStoresBuilder.hpp"
#include "Device/Interfaces/IMeasurementRecorder.hpp"
namespace BusinessLogic
{

    MeasurementStoresBuilder::MeasurementStoresBuilder(Driver::IUartDriver &uartForWiFi,
                                                       Driver::ISdCardDriver &sdCard)
        : wifiRecorder(uartForWiFi),
          sdCardRecorder(sdCard)
    {
    }

    bool MeasurementStoresBuilder::initialize()
    {
        wifiRecorder.initialize();
        sdCardRecorder.initialize();

        return true;
    }

    bool MeasurementStoresBuilder::start()
    {
        wifiRecorder.start();
        sdCardRecorder.start();

        // for debug
        wifiRecorder.notify();

        return true;
    }

    bool MeasurementStoresBuilder::stop()
    {
        return true;
    }

    bool MeasurementStoresBuilder::tick()
    {

        return true;
    }

    bool MeasurementStoresBuilder::registerStores(MeasurementDataStore &coordinator)
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
