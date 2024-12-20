/**
 * @file MeasurementStoresFactory.hpp
 * @brief Declares the MeasurementStoresFactory class responsible for constructing and managing measurement data stores.
 */

#ifndef MeasurementStoresFactory_h
#define MeasurementStoresFactory_h

#include "BusinessLogic/Interfaces/IApplicationComponentFactory.hpp"
#include "BusinessLogic/Inc/MeasurementDataStore.hpp"
#include "BusinessLogic/Inc/HmiFactory.hpp"
#include "BusinessLogic/Inc/MeasurementCoordinator.hpp"
#include "Device/Inc/WiFiMeasurementRecorder.hpp"
#include "Device/Inc/SdCardMeasurementRecorder.hpp"
#include "Device/Inc/CacheMeasurementRecorder.hpp"
#include "Driver/Interfaces/IUartDriver.hpp"
#include "Driver/Interfaces/ISdCardDriver.hpp"

#include <cstdint>

namespace BusinessLogic
{
    /**
     * @class MeasurementStoresFactory
     * @brief Responsible for building and managing measurement data stores.
     *
     * The MeasurementStoresFactory class constructs and manages components related to storing measurement data.
     * It requires drivers for the UART and SD card interfaces and constructs other components by itself.
     * This class is configurable based on the platform, whether it's running on firmware or in a simulation.
     */
    class MeasurementStoresFactory : public IApplicationComponentFactory
    {
    public:
        /**
         * @brief Constructs the MeasurementStoresFactory with platform-specific drivers.
         *
         * This constructor requires a UART driver for WiFi communication and an SD card driver to handle data storage.
         * The class constructs the measurement recorders and other components by itself.
         *
         * @param uartForWiFi Reference to the UART driver used for WiFi communication.
         * @param sdCard Reference to the SD card driver used for data storage.
         */
        explicit MeasurementStoresFactory(
            Device::CacheMeasurementRecorder &cacheRecorder,
            Driver::IUartDriver &uartForWiFi,
            Driver::ISdCardDriver &sdCard);

        /**
         * @brief Default destructor.
         */
        ~MeasurementStoresFactory() override = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        MeasurementStoresFactory(const MeasurementStoresFactory &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         * @return MeasurementStoresFactory& The assigned object.
         */
        MeasurementStoresFactory &operator=(const MeasurementStoresFactory &) = delete;

        /**
         * @brief Initializes the measurement data stores.
         * @return true if initialization was successful, false otherwise.
         */
        bool initialize() override;

        //  virtual bool registerStoresToHmi(IHmiFactory &hmiFactory);

        virtual bool registerStores(MeasurementDataStore &coordinator);
        //  bool registerStoresToHmi(IHmiFactory &coordinator);

    private:
        Device::CacheMeasurementRecorder &cacheRecorder;

        /** @brief WiFi measurement recorder used for storing measurements via WiFi. */
        Device::WiFiMeasurementRecorder wifiRecorder;

        /** @brief SD card measurement recorder used for storing measurements on an SD card. */
        Device::SdCardMeasurementRecorder sdCardRecorder;
    };
}

#endif // MeasurementStoresFactory_h
