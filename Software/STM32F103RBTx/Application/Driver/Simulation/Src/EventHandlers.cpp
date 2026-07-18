module;

#include <cstdint>
#include <utility>
#include <print>

import EventHandlers;

import Driver.UartId;
import Driver.SdCardStatus;
import Driver.FileOpenMode;

SerialTxCallback serialTxCallback = nullptr;
SdCardOpenCallback sdCardOpenCallback = nullptr;
SdCardWriteCallback sdCardWriteCallback = nullptr;
SdCardCloseCallback sdCardCloseCallback = nullptr;
SdCardInitializeCallback sdCardInitializeCallback = nullptr;
SdCardStartCallback sdCardStartCallback = nullptr;
SdCardStopCallback sdCardStopCallback = nullptr;
SdCardResetCallback sdCardResetCallback = nullptr;

void LibWrapper_RegisterSerialTxCallback(SerialTxCallback callback) noexcept
{
    serialTxCallback = callback;
}

void LibWrapper_RegisterSdCardOpenCallback(SdCardOpenCallback callback) noexcept
{
    sdCardOpenCallback = callback;
}

void LibWrapper_RegisterSdCardWriteCallback(SdCardWriteCallback callback) noexcept
{
    sdCardWriteCallback = callback;
}

void LibWrapper_RegisterSdCardCloseCallback(SdCardCloseCallback callback) noexcept
{
    sdCardCloseCallback = callback;
}

void LibWrapper_RegisterSdCardInitializeCallback(SdCardInitializeCallback callback) noexcept
{
    sdCardInitializeCallback = callback;
}

void LibWrapper_RegisterSdCardStartCallback(SdCardStartCallback callback) noexcept
{
    sdCardStartCallback = callback;
}

void LibWrapper_RegisterSdCardStopCallback(SdCardStopCallback callback) noexcept
{
    sdCardStopCallback = callback;
}

void LibWrapper_RegisterSdCardResetCallback(SdCardResetCallback callback) noexcept
{
    sdCardResetCallback = callback;
}

HAL_StatusTypeDef serialTx(UartId_t uartId, const std::uint8_t *data, std::uint16_t size, std::uint32_t timeout) noexcept
{
    HAL_StatusTypeDef result = HAL_StatusTypeDef::HAL_ERROR;

    if (serialTxCallback != nullptr)
    {
        result = static_cast<HAL_StatusTypeDef>(
            serialTxCallback(static_cast<std::uint8_t>(uartId), data, size, timeout));
    }
    else
    {
        std::println("Error: No UART callback registered.");
    }

    return result;
}

SdCardStatus_t sdCardOpen(const char *filename, FileOpenMode_t mode) noexcept
{
    SdCardStatus_t result = std::to_underlying(Driver::SdCardStatus::INVALID_PARAMETER);

    if (sdCardOpenCallback != nullptr)
    {
        result = sdCardOpenCallback(filename, static_cast<std::uint8_t>(mode));
    }
    else
    {
        std::println(stderr, "Error: No SD card open callback registered.");
    }

    return result;
}

SdCardStatus_t sdCardWrite(const std::uint8_t *data, std::uint16_t size) noexcept
{
    SdCardStatus_t result = std::to_underlying(Driver::SdCardStatus::INVALID_PARAMETER);

    if (sdCardWriteCallback != nullptr)
    {
        result = sdCardWriteCallback(data, size);
    }
    else
    {
        std::println(stderr, "Error: No SD card write callback registered.");
    }

    return result;
}

SdCardStatus_t sdCardClose() noexcept
{
    SdCardStatus_t result = std::to_underlying(Driver::SdCardStatus::INVALID_PARAMETER);

    if (sdCardCloseCallback != nullptr)
    {
        result = sdCardCloseCallback();
    }
    else
    {
        std::println(stderr, "Error: No SD card close callback registered.");
    }

    return result;
}

bool sdCardInitialize() noexcept
{
    bool result = true;

    if (sdCardInitializeCallback != nullptr)
    {
        result = sdCardInitializeCallback();
    }
    else
    {
        std::println(stderr, "Error: No SD card initialize callback registered.");
    }

    return result;
}

bool sdCardStart() noexcept
{
    bool result = true;

    if (sdCardStartCallback != nullptr)
    {
        result = sdCardStartCallback();
    }
    else
    {
        std::println(stderr, "Error: No SD card start callback registered.");
    }

    return result;
}

bool sdCardStop() noexcept
{
    bool result = true;

    if (sdCardStopCallback != nullptr)
    {
        result = sdCardStopCallback();
    }
    else
    {
        std::println(stderr, "Error: No SD card stop callback registered.");
    }

    return result;
}

bool sdCardReset() noexcept
{
    bool result = true;

    if (sdCardResetCallback != nullptr)
    {
        result = sdCardResetCallback();
    }
    else
    {
        std::println(stderr, "Error: No SD card reset callback registered.");
    }

    return result;
}