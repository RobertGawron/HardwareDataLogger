#include "HmiEventHandlers.hpp"

#include <iostream>

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
        std::cout << "Callback not set" << std::endl;
    }
}

void setPinState(GPIO_ID gpioId, bool state)
{
    // std::cout << "Setting pin state for GPIO_ID " << static_cast<int>(gpioId) << " to " << (state ? "HIGH" : "LOW") << std::endl;

    if (onGpioChange)
    {
        onGpioChange(gpioId, state); // Invoke the callback
    }
    else
    {
        std::cerr << "Error: No callback registered." << std::endl;
    }
}

void registerOnGpioChange(OnGpioChangeCallback callback)
{
    if (!callback)
    {
        std::cerr << "Error: Callback is null." << std::endl;
        return;
    }

    onGpioChange = callback;
}

void registerOnSerialTx(void (*callback)(char *))
{
    std::cout << "RegisterCallback" << std::endl;
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