#include "Driver/Inc/UartDriver.hpp"
#include "Driver/Inc/UartExchangeStatus.hpp"
#include "Driver/Inc/DriverState.hpp"

#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_hal_def.h"

#include <cstdint>

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

    UartExchangeStatus UartDriver::transmit(std::uint8_t *data, std::uint16_t size, std::uint32_t timeout)
    {

        UartExchangeStatus status = UartExchangeStatus::DriverInIncorrectMode;

        if (getState() == DriverState::State::Running)
        {
            /*
                // dummy for debug

                std::uint8_t xdata[] = {'z', 'r', '\r', '\n'};
                // char message[] = "r\r\n";
                auto len = sizeof(xdata) / sizeof(xdata[0]);
                timeout = 3000;

                HAL_StatusTypeDef halStatus = HAL_UART_Transmit(&uartHandler, xdata, len, timeout);
            */

            const HAL_StatusTypeDef halStatus = HAL_UART_Transmit(&uartHandler, data, size, timeout);
            status = getExchangeStatus(halStatus);
        }

        return status;
    }

    UartExchangeStatus UartDriver::receive(std::uint8_t *data, std::uint16_t size, std::uint32_t timeout)
    {
        UartExchangeStatus status = UartExchangeStatus::DriverInIncorrectMode;

        if (getState() == DriverState::State::Running)
        {
            /*
            // dummy for debug only

            static std::uint8_t data_rx[30];
            std::uint16_t len = 3;
            timeout = timeout;

            HAL_StatusTypeDef halStatus = HAL_UART_Receive(&uartHandler, data_rx, len, timeout);
            */

            const HAL_StatusTypeDef halStatus = HAL_UART_Receive(&uartHandler, data, size, timeout);
            status = getExchangeStatus(halStatus);
        }

        return status;
    }

    UartExchangeStatus UartDriver::getExchangeStatus(HAL_StatusTypeDef _halStatus)
    {
        using HalStatusToDriverStatus = struct
        {
            HAL_StatusTypeDef halStatus;
            UartExchangeStatus driverStatus;
        };

        const HalStatusToDriverStatus translation[] = {
            {HAL_OK, UartExchangeStatus::Ok},
            {HAL_ERROR, UartExchangeStatus::ErrorFromHal},
            {HAL_BUSY, UartExchangeStatus::Busy},
            {HAL_TIMEOUT, UartExchangeStatus::Timeout}};

        constexpr std::uint8_t len = sizeof(translation) / sizeof(translation[0]);

        UartExchangeStatus status = UartExchangeStatus::ErrorUnknown;
        bool isFound = false;
        for (std::uint8_t i = 0u; (i < len) && (!isFound); i++)
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
