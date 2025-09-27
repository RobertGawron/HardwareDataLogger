#include "HmiEventHandlers.hpp"

#include <iostream>
#include <cstdint>

OnSerialTxCallback onSerialTx = nullptr;
OnGpioChangeCallback onGpioChange = nullptr;

std::deque<uint8_t> uartQueueTx; // Queue for UART transmission

void serialTx(char *data)
{
    if (onSerialTx)
    {
        onSerialTx(data);
    }
    else
    {
        std::cerr << __LINE__ << " " << "Callback not set" << "\n";
    }
}

void setPinState(GPIO_ID gpioId, bool state)
{
    if (onGpioChange)
    {
        onGpioChange(gpioId, state); // Invoke the callback
    }
    else
    {
        std::cerr << __LINE__ << " " << "Callback not set" << "\n";
    }
}

void registerOnGpioChange(OnGpioChangeCallback callback)
{
    if (callback)
    {
        onGpioChange = callback;
    }
    else
    {
        std::cerr << __LINE__ << " " << "Callback not set" << "\n";
    }
}

void registerOnSerialTx(void (*callback)(char *))
{
    std::cout << "RegisterCallback" << "\n";
    onSerialTx = callback;
}

HAL_StatusTypeDef serialRx(
    const std::uint8_t *pData,
    std::uint16_t Size,
    std::uint32_t Timeout)
{

    HAL_StatusTypeDef status = HAL_OK;

    if (!pData || Size == 0)
    {
        status = HAL_StatusTypeDef::HAL_ERROR; // Handle invalid input
    }

    for (uint16_t i = 0; i < Size; ++i)
    {
        uartQueueTx.push_back(pData[i]);
    }

    return status;
}
