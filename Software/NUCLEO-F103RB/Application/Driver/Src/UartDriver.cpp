#include "Driver/Inc/UartDriver.hpp"

namespace Driver
{
    UartDriver::UartDriver(UART_HandleTypeDef &_uartHandler) : uartHandler(_uartHandler)
    {
    }

    bool UartDriver::onInitialize()
    {
        return true;
    }

    bool UartDriver::onStart()
    {
        const bool status = true;

        return status;
    }

    bool UartDriver::onStop()
    {
        const bool status = true;

        return status;
    }

    bool UartDriver::onReset()
    {
        return true;
    }

    UartExchangeStatus UartDriver::transmit(uint8_t *data, uint16_t size, uint32_t timeout)
    {

        UartExchangeStatus status = UartExchangeStatus::DriverInIncorrectMode;

        if (getState() == DriverState::State::Running)
        {
            /*
                // dummy for debug

                uint8_t xdata[] = {'z', 'r', '\r', '\n'};
                // char message[] = "r\r\n";
                auto len = sizeof(xdata) / sizeof(xdata[0]);
                timeout = 3000;

                HAL_StatusTypeDef halStatus = HAL_UART_Transmit(&uartHandler, xdata, len, timeout);
            */

            HAL_StatusTypeDef halStatus = HAL_UART_Transmit(&uartHandler, data, size, timeout);
            status = getExchangeStatus(halStatus);
        }

        return status;
    }

    UartExchangeStatus UartDriver::receive(uint8_t *data, uint16_t size, uint32_t timeout)
    {
        UartExchangeStatus status = UartExchangeStatus::DriverInIncorrectMode;

        if (getState() == DriverState::State::Running)
        {
            /*
            // dummy for debug only

            static uint8_t data_rx[30];
            uint16_t len = 3;
            timeout = timeout;

            HAL_StatusTypeDef halStatus = HAL_UART_Receive(&uartHandler, data_rx, len, timeout);
            */

            HAL_StatusTypeDef halStatus = HAL_UART_Receive(&uartHandler, data, size, timeout);
            status = getExchangeStatus(halStatus);
        }

        return status;
    }

    UartExchangeStatus UartDriver::getExchangeStatus(HAL_StatusTypeDef _halStatus)
    {
        typedef struct HalStatusToDriverStatus
        {
            HAL_StatusTypeDef halStatus;
            UartExchangeStatus driverStatus;
        } HalStatusToDriverStatus;

        const HalStatusToDriverStatus translation[] = {
            {HAL_OK, UartExchangeStatus::Ok},
            {HAL_ERROR, UartExchangeStatus::ErrorFromHal},
            {HAL_BUSY, UartExchangeStatus::Busy},
            {HAL_TIMEOUT, UartExchangeStatus::Timeout}};

        constexpr uint8_t len = sizeof(translation) / sizeof(translation[0]);

        UartExchangeStatus status = UartExchangeStatus::ErrorUnknown;
        bool isFound = false;
        for (uint8_t i = 0u; (i < len) && (!isFound); i++)
        {
            if (translation[i].halStatus == _halStatus)
            {
                status = translation[i].driverStatus;
                isFound = true;
            }
        }

        return status;
    }
}
