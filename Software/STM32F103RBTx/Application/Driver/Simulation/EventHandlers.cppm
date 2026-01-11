// EventHandlers.cpp
module;

#include "EventHandlers.hpp"

#include <iostream>
#include <cstdint>
#include <utility>

// export module Driver.EventHandlers;

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

void registerSerialTxCallback(SerialTxCallback callback)
{
    serialTxCallback = callback;
}

void registerSdCardOpenCallback(SdCardOpenCallback callback)
{
    sdCardOpenCallback = callback;
}

void registerSdCardWriteCallback(SdCardWriteCallback callback)
{
    sdCardWriteCallback = callback;
}

void registerSdCardCloseCallback(SdCardCloseCallback callback)
{
    sdCardCloseCallback = callback;
}

void registerSdCardInitializeCallback(SdCardInitializeCallback callback)
{
    sdCardInitializeCallback = callback;
}

void registerSdCardStartCallback(SdCardStartCallback callback)
{
    sdCardStartCallback = callback;
}

void registerSdCardStopCallback(SdCardStopCallback callback)
{
    sdCardStopCallback = callback;
}

void registerSdCardResetCallback(SdCardResetCallback callback)
{
    sdCardResetCallback = callback;
}

HAL_StatusTypeDef serialTx(UartId_t uartId, const std::uint8_t *data, std::uint16_t size, std::uint32_t timeout)
{
    HAL_StatusTypeDef result = HAL_StatusTypeDef::HAL_ERROR;

    if (serialTxCallback != nullptr)
    {
        result = static_cast<HAL_StatusTypeDef>(
            serialTxCallback(static_cast<std::uint8_t>(uartId), data, size, timeout));
    }
    else
    {
        std::cerr << "Error: No UART callback registered." << "\n";
    }

    return result;
}

SdCardStatus_t sdCardOpen(const char *filename, FileOpenMode_t mode)
{
    SdCardStatus_t result = std::to_underlying(Driver::SdCardStatus::INVALID_PARAMETER);

    if (sdCardOpenCallback != nullptr)
    {
        result = sdCardOpenCallback(filename, static_cast<std::uint8_t>(mode));
        // result = static_cast<Driver::SdCardStatus>(status);
    }
    else
    {
        std::cerr << "Error: No SD card open callback registered." << "\n";
    }

    return result;
}

SdCardStatus_t sdCardWrite(const std::uint8_t *data, std::uint16_t size)
{
    SdCardStatus_t result = std::to_underlying(Driver::SdCardStatus::INVALID_PARAMETER);

    if (sdCardWriteCallback != nullptr)
    {
        result = sdCardWriteCallback(data, size);
        // result = static_cast<Driver::SdCardStatus>(status);
    }
    else
    {
        std::cerr << "Error: No SD card write callback registered." << "\n";
    }

    return result;
}

SdCardStatus_t sdCardClose()
{
    SdCardStatus_t result = std::to_underlying(Driver::SdCardStatus::INVALID_PARAMETER);

    if (sdCardCloseCallback != nullptr)
    {
        result = sdCardCloseCallback();
        // result = static_cast<Driver::SdCardStatus>(status);
    }
    else
    {
        std::cerr << "Error: No SD card close callback registered." << "\n";
    }

    return result;
}

bool sdCardInitialize()
{
    bool result = true;

    if (sdCardInitializeCallback != nullptr)
    {
        result = sdCardInitializeCallback();
    }
    else
    {
        std::cerr << "Error: No SD card initialize callback registered." << "\n";
    }

    return result;
}

bool sdCardStart()
{
    bool result = true;

    if (sdCardStartCallback != nullptr)
    {
        result = sdCardStartCallback();
    }
    else
    {
        std::cerr << "Error: No SD card start callback registered." << "\n";
    }

    return result;
}

bool sdCardStop()
{
    bool result = true;

    if (sdCardStopCallback != nullptr)
    {
        result = sdCardStopCallback();
    }
    else
    {
        std::cerr << "Error: No SD card stop callback registered." << "\n";
    }

    return result;
}

bool sdCardReset()
{
    bool result = true;

    if (sdCardResetCallback != nullptr)
    {
        result = sdCardResetCallback();
    }
    else
    {
        std::cerr << "Error: No SD card reset callback registered." << "\n";
    }

    return result;
}