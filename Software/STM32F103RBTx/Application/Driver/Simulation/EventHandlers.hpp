#ifndef EventHandlers_hpp
#define EventHandlers_hpp

// #include "Driver/Interface/UartStatus.hpp"
// #include "Driver/Interface/UartId.hpp"

// #include "Driver/Interface/SdCardStatus.hpp"
// #include "SdCardDriver.hpp"

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

// UART callback
using SerialTxCallback = int (*)(std::uint8_t, const std::uint8_t *, std::uint16_t, std::uint32_t);

// SD Card operation callbacks - use uint8_t for enum return types (ABI compatibility)
using SdCardOpenCallback = std::uint8_t (*)(const char *, std::uint8_t);
using SdCardWriteCallback = std::uint8_t (*)(const std::uint8_t *, std::uint16_t);
using SdCardCloseCallback = std::uint8_t (*)();

// SD Card lifecycle callbacks
using SdCardInitializeCallback = bool (*)();
using SdCardStartCallback = bool (*)();
using SdCardStopCallback = bool (*)();
using SdCardResetCallback = bool (*)();

extern SerialTxCallback serialTxCallback;
extern SdCardOpenCallback sdCardOpenCallback;
extern SdCardWriteCallback sdCardWriteCallback;
extern SdCardCloseCallback sdCardCloseCallback;
extern SdCardInitializeCallback sdCardInitializeCallback;
extern SdCardStartCallback sdCardStartCallback;
extern SdCardStopCallback sdCardStopCallback;
extern SdCardResetCallback sdCardResetCallback;

void registerSerialTxCallback(SerialTxCallback callback);
void registerSdCardOpenCallback(SdCardOpenCallback callback);
void registerSdCardWriteCallback(SdCardWriteCallback callback);
void registerSdCardCloseCallback(SdCardCloseCallback callback);
void registerSdCardInitializeCallback(SdCardInitializeCallback callback);
void registerSdCardStartCallback(SdCardStartCallback callback);
void registerSdCardStopCallback(SdCardStopCallback callback);
void registerSdCardResetCallback(SdCardResetCallback callback);

HAL_StatusTypeDef serialTx(Driver::UartId uartId, const std::uint8_t *data, std::uint16_t size, std::uint32_t timeout);
Driver::SdCardStatus sdCardOpen(const char *filename, Driver::FileOpenMode mode);
Driver::SdCardStatus sdCardWrite(const std::uint8_t *data, std::uint16_t size);
Driver::SdCardStatus sdCardClose();
bool sdCardInitialize();
bool sdCardStart();
bool sdCardStop();
bool sdCardReset();

#endif
