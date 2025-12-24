#ifndef AmbientLightSensorDriverStub_H_
#define AmbientLightSensorDriverStub_H_

#include "Driver/Interfaces/IAmbientLightSensorDriver.hpp"

#include <stdint.h>

namespace Driver
{

    class AmbientLightSensorDriverStub : public IAmbientLightSensorDriver
    {
    public:
        /**
         * @brief Default constructor.
         *
         */
        AmbientLightSensorDriverStub() = default;

        /**
         * @brief Destructor for AmbientLightSensorDriverStub.
         */
        ~AmbientLightSensorDriverStub() override = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        AmbientLightSensorDriverStub(const AmbientLightSensorDriverStub &) = delete;

        /**
         * @brief Deleted copy assignment operator to prevent assignment.
         */
        AmbientLightSensorDriverStub &operator=(const AmbientLightSensorDriverStub &) = delete;

        /**
         * @brief Retrieves the current ambient light level.
         *
         * This method returns the current ambient light level measured by the sensor.
         * The range of the returned value is dependent on the hardware configuration and sensor characteristics.
         *
         * @return std::uint32_t The current ambient light level.
         */
        [[nodiscard]] std::uint32_t getAmbientLightLevel() const override;

    protected:
        /**
         * @brief Initializes the Ambient Light Sensor Driver.
         *
         * This method is called during the initialization phase of the driver. It ensures that the ADC
         * and DMA are properly configured and ready for use, but it does not start the ADC conversion itself.
         *
         * @return true if the initialization is successful, false otherwise.
         */
        bool onInitialize() override;

        /**
         * @brief Starts the ADC and DMA transfer.
         *
         * This method begins the ADC conversion process and sets up the DMA to transfer the ADC data to
         * the buffer. It ensures that the system is ready to acquire ambient light sensor readings continuously.
         *
         * @return true if the ADC and DMA start successfully, false otherwise.
         */
        bool onStart() override;

        /**
         * @brief Stops the ADC and DMA transfer.
         *
         * This method halts the ADC conversion process and stops the DMA from transferring data. It is used
         * when the system no longer needs to acquire data from the ambient light sensor.
         *
         * @return true if the ADC and DMA stop successfully, false otherwise.
         */
        bool onStop() override;

        /**
         * @brief Resets the Ambient Light Sensor Driver.
         *
         * This method resets the driver, stopping any ongoing ADC and DMA operations and returning the
         * system to its initial state. It can be used to reinitialize the system or handle error conditions.
         *
         * @return true if the reset is successful, false otherwise.
         */
        bool onReset() override;

        /**
         * @brief Starts the ADC conversion using DMA for data transfer.
         *
         * This method configures and starts the ADC in combination with DMA to handle data transfer
         * efficiently without burdening the CPU. The DMA continuously transfers the ADC conversion results
         * into a buffer, allowing the system to read the latest ambient light levels.
         *
         * @return true if ADC and DMA setup is successful, false otherwise.
         */
        bool startAdcWithDma();

        /**
         * @brief Stops the ADC conversion and DMA transfer.
         *
         * This method stops the ongoing ADC conversions and halts the DMA transfer process. It is typically
         * used when the ambient light measurements are no longer needed, or before resetting or shutting down
         * the system.
         *
         * @return true if the ADC and DMA stop successfully, false otherwise.
         */
        bool stopAdcWithDma();
    };

}

#endif // AmbientLightSensorDriverStub_H_
