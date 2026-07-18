module;

#include <cstdint>

export module EventHandlers;

// Export types normally (they don't need C linkage)
export enum class HAL_StatusTypeDef : std::uint8_t {
    HAL_OK = 0x00U,
    HAL_ERROR = 0x01U,
    HAL_BUSY = 0x02U,
    HAL_TIMEOUT = 0x03U
};

export using SdCardStatus_t = std::uint8_t;
export using FileOpenMode_t = std::uint8_t;
export using UartId_t = std::uint8_t;

export using SerialTxCallback = int (*)(std::uint8_t, const std::uint8_t *, std::uint16_t, std::uint32_t);
export using SdCardOpenCallback = std::uint8_t (*)(const char *, std::uint8_t);
export using SdCardWriteCallback = std::uint8_t (*)(const std::uint8_t *, std::uint16_t);
export using SdCardCloseCallback = std::uint8_t (*)(void);

export using SdCardInitializeCallback = bool (*)(void);
export using SdCardStartCallback = bool (*)(void);
export using SdCardStopCallback = bool (*)(void);
export using SdCardResetCallback = bool (*)(void);

// Only functions need C linkage
export extern "C"
{
    auto LibWrapper_RegisterSerialTxCallback(SerialTxCallback) noexcept -> void;
    auto LibWrapper_RegisterSdCardOpenCallback(SdCardOpenCallback) noexcept -> void;
    auto LibWrapper_RegisterSdCardWriteCallback(SdCardWriteCallback) noexcept -> void;
    auto LibWrapper_RegisterSdCardCloseCallback(SdCardCloseCallback) noexcept -> void;
    auto LibWrapper_RegisterSdCardInitializeCallback(SdCardInitializeCallback) noexcept -> void;
    auto LibWrapper_RegisterSdCardStartCallback(SdCardStartCallback) noexcept -> void;
    auto LibWrapper_RegisterSdCardStopCallback(SdCardStopCallback) noexcept -> void;
    auto LibWrapper_RegisterSdCardResetCallback(SdCardResetCallback) noexcept -> void;

    auto serialTx(UartId_t, const std::uint8_t *, std::uint16_t, std::uint32_t) noexcept -> HAL_StatusTypeDef;

    auto sdCardOpen(const char *, FileOpenMode_t) noexcept -> SdCardStatus_t;
    auto sdCardInitialize(void) noexcept -> bool;
    auto sdCardStart(void) noexcept -> bool;
    auto sdCardWrite(const std::uint8_t *, std::uint16_t) noexcept -> SdCardStatus_t;
    auto sdCardStop(void) noexcept -> bool;
    auto sdCardReset(void) noexcept -> bool;
    auto sdCardClose(void) noexcept -> SdCardStatus_t;
}