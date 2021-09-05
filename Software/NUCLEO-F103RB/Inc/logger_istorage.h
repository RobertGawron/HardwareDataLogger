#ifndef LOGGER_ISTORAGE_H_
#define LOGGER_ISTORAGE_H_

#include "logger_istorage_driver.h"
#include "logger_measurement.h"

typedef struct LoggerIStorage_t
{
    void (*init)();

    LoggerIStorageDriver_t driver;
} LoggerIStorage_t;

#endif
