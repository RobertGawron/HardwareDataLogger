#include "SdCardDriverStub.hpp"

namespace Driver
{

    SdCardDriverStub::SdCardDriverStub()
    {
    }

    bool SdCardDriverStub::onInitialize()
    {
        return true;
    }

    bool SdCardDriverStub::onStart()
    {
        return true;
    }

    bool SdCardDriverStub::onStop()
    {
        return true;
    }

    bool SdCardDriverStub::onReset()
    {
        return true;
    }

    void SdCardDriverStub::mountFileSystem()
    {
    }

    void SdCardDriverStub::unmountFileSystem()
    {
    }

    void SdCardDriverStub::openFile()
    {
    }

    void SdCardDriverStub::closeFile()
    {
    }

    void SdCardDriverStub::sync()
    {
    }

    void SdCardDriverStub::writeToFile()
    {
    }

}
