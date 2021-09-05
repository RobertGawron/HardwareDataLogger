#ifndef LOGGER_SD_CARD_STORAGE_DRIVER_H_
#define LOGGER_SD_CARD_STORAGE_DRIVER_H_

#include "logger_istorage.h"
#include "fatfs.h"

typedef struct LoggerSDCardDriver_t LoggerSDCardDriver_t;

struct LoggerSDCardDriver_t
{
    void (*init)(LoggerSDCardDriver_t* self);
    LoggerIStorage_t base;

    FATFS g_sFatFs;
    FIL file;
};

void LoggerSDCardDriver_Create(LoggerSDCardDriver_t* self);

#endif
