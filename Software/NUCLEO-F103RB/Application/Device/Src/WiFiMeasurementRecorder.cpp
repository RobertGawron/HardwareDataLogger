#include "Device/Inc/WiFiMeasurementRecorder.hpp"

namespace Device
{

    WiFiMeasurementRecorder::WiFiMeasurementRecorder(Driver::IUartDriver &_driver) : driver(_driver)
    {
    }

    bool WiFiMeasurementRecorder::onInitialize()
    {
        bool status = driver.initialize();
        return status;
    }

    bool WiFiMeasurementRecorder::onStart()
    {
        bool status = driver.start();
        return status;
    }

    bool WiFiMeasurementRecorder::onStop()
    {
        bool status = driver.stop();
        return status;
    }

    bool WiFiMeasurementRecorder::onReset()
    {
        bool status = driver.reset();
        return status;
    }

    void WiFiMeasurementRecorder::write()
    {
        Driver::UartExchangeStatus status1, status2;
        {
            // #define HAL_MAX_DELAY      0xFFFFFFFFU
            // uint8_t data[] = {0xc, 0xa, 0xf, 0xe, '\r', '\n'};
            uint8_t data[] = {'z', 'r', '\r', '\n'};
            // char message[] = "r\r\n";
            auto len = sizeof(data) / sizeof(data[0]);
            status1 = driver.transmit(data, len, Driver::IUartDriver::MaxDelay); //
        }
        {
            uint8_t data_rx[30] = {0};
            auto len = 3;
            status2 = driver.receive(data_rx, len, 0xFFFFU);

            volatile int a;
        }
    }

    void WiFiMeasurementRecorder::flush()
    {
    }

    void WiFiMeasurementRecorder::notify()
    {
        // dummy for debug
        write();
    }
}
