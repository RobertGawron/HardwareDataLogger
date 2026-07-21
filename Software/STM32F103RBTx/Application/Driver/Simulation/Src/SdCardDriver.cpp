module;

#include <cstring>
#include <string_view>
#include <span>
#include <cstdint>
#include <algorithm>
#include <utility>

module Driver.SdCardDriver;

import EventHandlers;

namespace Driver
{
    auto SdCardDriver::onInit() noexcept -> bool
    {

        return sdCardInitialize();
    }

    auto SdCardDriver::onStart() noexcept -> bool
    {
        return sdCardStart();
    }

    auto SdCardDriver::onStop() noexcept -> bool
    {
        return sdCardStop();
    }

    bool SdCardDriver::onReset() noexcept
    {
        return sdCardReset();
    }

    auto SdCardDriver::openFile(std::string_view filename, FileOpenMode mode) noexcept -> SdCardStatus
    {
        char filenameBuffer[256];
        std::size_t len = std::min(filename.size(), sizeof(filenameBuffer) - 1);
        std::memcpy(filenameBuffer, filename.data(), len);
        filenameBuffer[len] = '\0';

        return static_cast<SdCardStatus>(sdCardOpen(filenameBuffer, std::to_underlying(mode)));
    }

    auto SdCardDriver::closeFile() noexcept -> SdCardStatus
    {
        return static_cast<SdCardStatus>(sdCardClose());
    }

    auto SdCardDriver::write(std::string_view data) noexcept -> SdCardStatus
    {
        const auto size = static_cast<std::uint16_t>(data.size());

        return static_cast<SdCardStatus>(
            sdCardWrite(reinterpret_cast<const std::uint8_t *>(data.data()), size));
    }
}