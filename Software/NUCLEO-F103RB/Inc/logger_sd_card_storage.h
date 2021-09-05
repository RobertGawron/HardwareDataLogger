#ifndef LOGGER_SD_CARD_STORAGE_H_
#define LOGGER_SD_CARD_STORAGE_H_

#include "logger_istorage.h"

typedef struct LoggerSDCardStorage_t LoggerSDCardStorage_t;

struct LoggerSDCardStorage_t
{
    LoggerIStorage_t base;
    void (*init)(LoggerSDCardStorage_t* self);
    void (*storeMeasurement)(LoggerSDCardStorage_t* self, LoggerMeasurement_Value_t);
};

void LoggerSDCardStorage_Create(LoggerSDCardStorage_t* self);

#endif
