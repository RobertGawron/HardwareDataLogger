#include "logger_sd_card_storage.h"
#include "logger_sd_card_storage_driver.h"

static void Init_Impl(LoggerSDCardStorage_t* self);
static void Store_Impl(LoggerSDCardStorage_t* self, LoggerMeasurement_Value_t data);

void LoggerSDCardStorage_Create(LoggerSDCardStorage_t* self)
{
    self->init = &Init_Impl;
    self->storeMeasurement = &Store_Impl;

    LoggerSDCardDriver_Create(&self->base.driver);
}

void Init_Impl(LoggerSDCardStorage_t* self)
{
    // todo flags to select what loggers are used
    self->base.driver.init( &self->base.driver);
}

void Store_Impl(LoggerSDCardStorage_t* self, LoggerMeasurement_Value_t data)
{

}
