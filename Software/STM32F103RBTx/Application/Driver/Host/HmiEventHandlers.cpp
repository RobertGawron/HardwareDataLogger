#include "HmiEventHandlers.hpp"

#include <iostream>
#include <cstdint>

SerialTxCallback serialTxCallback = nullptr;

void registerSerialTxCallback(SerialTxCallback callback)
{
    serialTxCallback = callback;
}

HAL_StatusTypeDef serialTx(const std::uint8_t *pData, std::uint16_t size, std::uint32_t timeout)
{
    HAL_StatusTypeDef result = HAL_StatusTypeDef::HAL_ERROR;

    if (serialTxCallback != nullptr)
    {
        result = static_cast<HAL_StatusTypeDef>(serialTxCallback(pData, size, timeout));
    }
    else
    {
        std::cerr << "Error: No callback registered." << "\n";
    }

    return result;
}
