// SdCardDriver.cpp
module;

#include "EventHandlers.h"

#include <iostream>
#include <cstring>
#include <string_view>
#include <span>
#include <cstdint>
#include <algorithm>
#include <utility>

module Driver.SdCardDriver;

namespace Driver
{
    bool SdCardDriver::onInit() noexcept
    {
        return sdCardInitialize();
    }

    bool SdCardDriver::onStart() noexcept
    {
        return sdCardStart();
    }

    bool SdCardDriver::onStop() noexcept
    {
        return sdCardStop();
    }

    bool SdCardDriver::onReset() noexcept
    {
        return sdCardReset();
    }

    SdCardStatus SdCardDriver::openFile(std::string_view filename, FileOpenMode mode) noexcept
    {
        char filenameBuffer[256];
        std::size_t len = std::min(filename.size(), sizeof(filenameBuffer) - 1);
        std::memcpy(filenameBuffer, filename.data(), len);
        filenameBuffer[len] = '\0';

        return static_cast<SdCardStatus>(sdCardOpen(filenameBuffer, std::to_underlying(mode)));
    }

    SdCardStatus SdCardDriver::closeFile() noexcept
    {
        return static_cast<SdCardStatus>(sdCardClose());
    }

    SdCardStatus SdCardDriver::write(std::span<const std::uint8_t> data) noexcept
    {
        const auto size = static_cast<std::uint16_t>(data.size());
        return static_cast<SdCardStatus>(sdCardWrite(data.data(), size));
    }
}