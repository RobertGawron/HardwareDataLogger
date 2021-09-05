#include "logger_sd_card_storage_driver.h"

static void Init_Impl(LoggerSDCardDriver_t* self);
static void Store_Impl(LoggerSDCardDriver_t* self, LoggerMeasurement_Value_t data);

void LoggerSDCardDriver_Create(LoggerSDCardDriver_t* self)
{
    self->init = &Init_Impl;
}

static void Init_Impl(LoggerSDCardDriver_t* self)
{

    char buffer[128];
    // FATFS g_sFatFs;
    FRESULT fresult;
    // FIL file;
    int len;
    WORD bytes_written;

    HAL_Delay(1000);       //a short delay is important to let the SD card settle


    //mount SD card
    fresult = f_mount(&self->g_sFatFs, "", 1);
    //while (f_mount(&g_sFatFs, "", 1) != FR_OK)
    if (fresult != FR_OK)
    {
        volatile int x = 0;
        x++;

    }

    //open file on SD card
    fresult = f_open(&self->file, "test.txt", FA_OPEN_ALWAYS | FA_WRITE);

    //go to the end of the file
    fresult = f_lseek(&self->file, self->file.fsize);

    //generate some string
    len = sprintf( buffer, "test before hot glue cables!!!!\r\n");

    //write data to the file
    fresult = f_write(&self->file, buffer, len, &bytes_written);

    //close file
    fresult = f_close (&self->file);
    /////////// Poc of sdCard ////////////////


    // robert: extra sync
    f_sync(&self->file);
}
