#ifndef LOGGER_STORAGES_CONTAINER_H_
#define LOGGER_STORAGES_CONTAINER_H_

#include "logger_storages_container.h"
#include "logger_sd_card_storage.h"
#include "logger_wifi_storage.h"
#include "logger_uart_storage.h"

#include "logger_measurement.h"

#define STORAGE_WIFI_ENABLE 1
#define STORAGE_SDCARD_ENABLE (1 << 1)
#define STORAGE_UART_ENABLE (1 << 2)

typedef struct LoggerStorageContainer_t LoggerStorageContainer_t;

struct LoggerStorageContainer_t
{
    LoggerSDCardStorage_t sdcard;
    LoggerWifiStorage_t wifi;
    LoggerUartStorage_t uart;

    void (*init)(LoggerStorageContainer_t* self, uint8_t config);
    void (*storeMeasurement)(LoggerMeasurement_Value_t);
};



void LoggerStorageContainer_Create(LoggerStorageContainer_t* self);
//void LoggerStorageContainer_Init(LoggerStorageContainer_t* self, uint8_t config);


#endif
