
#ifndef LOGGER_UART_STORAGE_H_
#define LOGGER_UART_STORAGE_H_

#include "logger_uart_storage_driver.h"

typedef struct LoggerUartStorage_t
{
    LoggerUartDriver_t driver;
} LoggerUartStorage_t;

void LoggerUartStorage_Init(LoggerUartStorage_t self);

#endif
