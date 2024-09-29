#ifndef stm32f1xx_hal_uart_h
#define stm32f1xx_hal_uart_h

#include <stdint.h>

typedef struct __UART_HandleTypeDef
{
    uint8_t dummy;
} UART_HandleTypeDef;

extern UART_HandleTypeDef huart3;

#endif