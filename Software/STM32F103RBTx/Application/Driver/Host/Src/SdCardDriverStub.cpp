#include "SdCardDriverStub.hpp"
#include "EventHandlers.hpp"

#include <iostream>
#include <cstring>

namespace Driver
{

    bool SdCardDriverStub::onInitialize()
    {
        return sdCardInitialize();
    }

    bool SdCardDriverStub::onStart()
    {
        return sdCardStart();
    }

    bool SdCardDriverStub::onStop()
    {
        return sdCardStop();
    }

    bool SdCardDriverStub::onReset()
    {
        return sdCardReset();
    }

    SdCardStatus SdCardDriverStub::openFile(std::string_view filename, FileOpenMode mode)
    {
        char filenameBuffer[256];
        std::size_t len = std::min(filename.size(), sizeof(filenameBuffer) - 1);
        std::memcpy(filenameBuffer, filename.data(), len);
        filenameBuffer[len] = '\0';

        return sdCardOpen(filenameBuffer, mode);
    }

    SdCardStatus SdCardDriverStub::closeFile()
    {
        return sdCardClose();
    }

    SdCardStatus SdCardDriverStub::write(std::span<const std::uint8_t> data)
    {
        const auto size = static_cast<std::uint16_t>(data.size());
        return sdCardWrite(data.data(), size);
    }

}