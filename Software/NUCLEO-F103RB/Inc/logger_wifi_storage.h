
#ifndef LOGGER_WIFI_STORAGE_H_
#define LOGGER_WIFI_STORAGE_H_

#include "logger_wifi_storage_driver.h"

typedef struct LoggerWifiStorage_t
{
    LoggerWifiDriver_t driver;
} LoggerWifiStorage_t;

void LoggerWifiStorage_Init(LoggerWifiStorage_t self);

#endif
