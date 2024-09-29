#ifndef AMBIENTLIGHTSENSORDRIVER_H_
#define AMBIENTLIGHTSENSORDRIVER_H_

#include "Driver/Interfaces/IAmbientLightSensorDriver.hpp"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_adc.h"
#include <stdint.h>

// struct ADC_HandleTypeDef;
// enum HAL_StatusTypeDef;

namespace Driver
{
    /**
     * @brief AmbientLightSensorDriver class provides functionality to interact with an ambient light sensor.
     *
     * This class interfaces with an ADC connected to a voltage divider that includes a resistor and a phototransistor.
     * The light level readings are dependent on the type of photoelement sensor used, and the resistor value, which was chosen experimentally.
     * The class also leverages DMA for efficient data acquisition, reducing CPU load.
     */
    class AmbientLightSensorDriver : public IAmbientLightSensorDriver
    {
    public:
        /**
         * @brief Constructor for AmbientLightSensorDriver.
         */
        explicit AmbientLightSensorDriver(ADC_HandleTypeDef &hadc);

        /**
         * @brief Deleted default constructor.
         *
         * Prevents the creation of a AmbientLightSensorDriver instance without specifying a UART handle.
         */
        AmbientLightSensorDriver() = delete;

        /**
         * @brief Destructor for AmbientLightSensorDriver.
         */
        virtual ~AmbientLightSensorDriver() = default;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        AmbientLightSensorDriver(const AmbientLightSensorDriver &) = delete;

        /**
         * @brief Deleted copy assignment operator to prevent assignment.
         */
        AmbientLightSensorDriver &operator=(const AmbientLightSensorDriver &) = delete;

        /**
         * @brief Retrieves the current ambient light level.
         *
         * This method returns the current ambient light level measured by the sensor.
         * The range of the returned value is dependent on the hardware configuration and sensor characteristics.
         *
         * @return uint32_t The current ambient light level.
         */
        virtual uint32_t getAmbientLightLevel() const override;

    protected:
        /**
         * @brief Initializes the Ambient Light Sensor Driver.
         *
         * This method is called during the initialization phase of the driver. It ensures that the ADC
         * and DMA are properly configured and ready for use, but it does not start the ADC conversion itself.
         *
         * @return true if the initialization is successful, false otherwise.
         */
        virtual bool onInitialize() override;

        /**
         * @brief Starts the ADC and DMA transfer.
         *
         * This method begins the ADC conversion process and sets up the DMA to transfer the ADC data to
         * the buffer. It ensures that the system is ready to acquire ambient light sensor readings continuously.
         *
         * @return true if the ADC and DMA start successfully, false otherwise.
         */
        virtual bool onStart() override;

        /**
         * @brief Stops the ADC and DMA transfer.
         *
         * This method halts the ADC conversion process and stops the DMA from transferring data. It is used
         * when the system no longer needs to acquire data from the ambient light sensor.
         *
         * @return true if the ADC and DMA stop successfully, false otherwise.
         */
        virtual bool onStop() override;

        /**
         * @brief Resets the Ambient Light Sensor Driver.
         *
         * This method resets the driver, stopping any ongoing ADC and DMA operations and returning the
         * system to its initial state. It can be used to reinitialize the system or handle error conditions.
         *
         * @return true if the reset is successful, false otherwise.
         */
        virtual bool onReset() override;

        /**
         * @brief Starts the ADC conversion using DMA for data transfer.
         *
         * This method configures and starts the ADC in combination with DMA to handle data transfer
         * efficiently without burdening the CPU. The DMA continuously transfers the ADC conversion results
         * into a buffer, allowing the system to read the latest ambient light levels.
         *
         * @return true if ADC and DMA setup is successful, false otherwise.
         */
        virtual bool startAdcWithDma();

        /**
         * @brief Stops the ADC conversion and DMA transfer.
         *
         * This method stops the ongoing ADC conversions and halts the DMA transfer process. It is typically
         * used when the ambient light measurements are no longer needed, or before resetting or shutting down
         * the system.
         *
         * @return true if the ADC and DMA stop successfully, false otherwise.
         */
        virtual bool stopAdcWithDma();

    private:
        /**
         * @brief ADC handle from STM32 HAL library.
         *
         * This reference is used to interact with the UART peripheral.
         */
        ADC_HandleTypeDef &hadc;
    };

}

#endif // AMBIENTLIGHTSENSORDRIVER_H_