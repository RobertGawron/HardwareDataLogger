#include "logger_storages_container.h"

static void Init_Impl(LoggerStorageContainer_t* self, uint8_t config);
static void Store_Impl(LoggerMeasurement_Value_t data);

void LoggerStorageContainer_Create(LoggerStorageContainer_t* self)
{
    self->init = &Init_Impl;
    self->storeMeasurement = &Store_Impl;


    LoggerSDCardStorage_Create(&self->sdcard);

}


void Init_Impl(LoggerStorageContainer_t* self, uint8_t config)
{
    // todo flags to select wchich loggers are used
    self->sdcard.init(&self->sdcard);
}


void Store_Impl(LoggerMeasurement_Value_t data)
{

}
