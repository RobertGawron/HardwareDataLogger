#include "SdCardDriver.hpp"
#include "EventHandlers.hpp"

#include <iostream>
#include <cstring>

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

        return sdCardOpen(filenameBuffer, mode);
    }

    SdCardStatus SdCardDriver::closeFile() noexcept
    {
        return sdCardClose();
    }

    SdCardStatus SdCardDriver::write(std::span<const std::uint8_t> data) noexcept
    {
        const auto size = static_cast<std::uint16_t>(data.size());
        return sdCardWrite(data.data(), size);
    }

}