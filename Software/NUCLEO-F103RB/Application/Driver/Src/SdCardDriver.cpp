#include "SdCardDriver.hpp"

#include "fatfs.h"
#include "user_diskio.h"
// #include "robuser_diskio.h"
namespace Driver
{
    FATFS FatFs;  // FatFS handle
    FIL fil;      // File handle
    FRESULT fres; // Result after operations

    // SD card use SPI, it's already configured but pin for CS should be passed as an argument.
    SdCardDriver::SdCardDriver()
    {
    }
    // clk
    bool SdCardDriver::onInitialize()
    {
        bool status = true;
        return status;
    }
    bool SdCardDriver::onStart()
    {

        HAL_Delay(1000);
        //// #define _VOLUME_STRS            "RAM","NAND","CF","SD1","SD2","USB1","USB2","USB3"
        // Mount the filesystem
        fres = f_mount(&FatFs, "0:/", 1); // 1=mount now
        if (fres != FR_OK)
        {
            // Handle the mount error
            return false;
        }

        // Open or create the file for writing
        fres = f_open(&fil, "write.txt", FA_WRITE | FA_CREATE_ALWAYS);
        if (fres != FR_OK)
        {
            // Handle file open error
            f_mount(0, "", 0); // Unmount in case of failure
            return false;
        }

        // Prepare data to write
        char readBuf[100] = ":)"; // Example data
        UINT bytesWrote;

        // Write data to the file
        fres = f_write(&fil, readBuf, 19, &bytesWrote);
        if (fres != FR_OK)
        {
            // Handle write error
            f_close(&fil);
            f_mount(0, "", 0); // Unmount after error
            return false;
        }

        // Ensure all data is physically written to the SD card
        f_sync(&fil);

        // Close the file
        f_close(&fil);

        // Unmount the filesystem
        f_mount(0, "", 0);
        bool status = true;
        return status;
    }
    bool SdCardDriver::onStop()
    {
        bool status = true;
        return status;
    }
    bool SdCardDriver::onReset()
    {
        bool status = true;
        return status;
    }

    void SdCardDriver::mountFileSystem()
    {
    }

    void SdCardDriver::unmountFileSystem()
    {
    }

    void SdCardDriver::openFile()
    {
    }

    void SdCardDriver::closeFile()
    {
    }

    void SdCardDriver::sync()
    {
    }

    void SdCardDriver::writeToFile()
    {
    }

}
