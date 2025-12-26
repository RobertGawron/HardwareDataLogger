#ifndef HmiEventHandlers_hpp
#define HmiEventHandlers_hpp

#include <functional>
#include <cstdint>
#include <queue>

// from stm32f1xx_hal_def.h
enum class HAL_StatusTypeDef : std::uint8_t
{
    HAL_OK = 0x00U,
    HAL_ERROR = 0x01U,
    HAL_BUSY = 0x02U,
    HAL_TIMEOUT = 0x03U
};

// Define the callback type
using SerialTxCallback = int (*)(const std::uint8_t *pData, std::uint16_t size, std::uint32_t timeout);

extern SerialTxCallback serialTxCallback;

void registerSerialTxCallback(SerialTxCallback callback);

HAL_StatusTypeDef serialTx(const std::uint8_t *pData, std::uint16_t size, std::uint32_t timeout);

#endif
