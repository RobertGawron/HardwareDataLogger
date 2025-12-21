#include "Driver/Inc/SdCardDriver.hpp"

// #include "fatfs.h"
#include "ff.h"
// dont use main, also remove from ut
#include "main.h"
extern SPI_HandleTypeDef hspi1;
FATFS FatFs;  // File system object
FIL fil;      // File object
FRESULT fres; // Result code

namespace Driver
{
    /*
    FATFS FatFs;  // FatFS handle
    FIL fil;      // File handle
    FRESULT fres; // Result after operations
*/
    // SD card use SPI, it's already configured but pin for CS should be passed as an argument.

    // clk
    bool SdCardDriver::onInitialize()
    {
        const bool status = true;

        int i = 0;
        onStart();

        return status;
    }
    bool SdCardDriver::onStart()
    {
        GPIO_InitTypeDef GPIO_InitStruct = {0};

        /* 1. Enable GPIO Clocks */
        __HAL_RCC_GPIOA_CLK_ENABLE(); // For SCK, MISO, MOSI
        __HAL_RCC_GPIOB_CLK_ENABLE(); // For CS

        /* 2. Free PB4 from JTAG (CRITICAL!) */
        __HAL_AFIO_REMAP_SWJ_NOJTAG(); // Disable JTAG, keep SWD

        /* 3. Configure SPI Pins */
        // SCK (PA5) - Alternate Function Push-Pull
        GPIO_InitStruct.Pin = GPIO_PIN_5;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        // MOSI (PA7) - Alternate Function Push-Pull
        GPIO_InitStruct.Pin = GPIO_PIN_7;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        // MISO (PA6) - Input with Pull-up
        GPIO_InitStruct.Pin = GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        // CS (PB4) - Output Push-Pull (High = Inactive)
        GPIO_InitStruct.Pin = GPIO_PIN_4;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET); // Set CS high

        /*
          HAL_SPI_StateTypeDef dupa = HAL_SPI_GetState(&hspi1);
          if (dupa == HAL_SPI_STATE_READY) {
            // SPI is initialized and enabled
        volatile int isOK;
          }


        auto x =  SPI1->CR1;
        auto y = SPI1->CR2;
        auto z =  SPI1->SR;
        */
        /*
                    while(1) {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
                HAL_Delay(100);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
                HAL_Delay(100);
            }
        */

        HAL_Delay(1000);
        //// #define _VOLUME_STRS            "RAM","NAND","CF","SD1","SD2","USB1","USB2","USB3"
        // Mount the filesystem
        fres = f_mount(&FatFs, "0:", 1); // 1=mount now
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
        char readBuf[100] = " wow hello :)"; // Example data
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

        const bool status = true;
        return status;
    }
    bool SdCardDriver::onStop()
    {
        const bool status = true;
        return status;
    }
    bool SdCardDriver::onReset()
    {
        const bool status = true;
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
