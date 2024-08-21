#ifndef stm32f1xx_hal_uart_mock_h
#define stm32f1xx_hal_uart_mock_h

#include <gmock/gmock.h>
#include <stdint.h>
#include "main.h"

typedef struct __UART_HandleTypeDef
{
    uint32_t dummy;
} UART_HandleTypeDef;

// Mock class for HAL UART functions
class MockHAL_UART
{
public:
    // Mock method for HAL_UART_Transmit
    MOCK_METHOD(HAL_StatusTypeDef, HAL_UART_Transmit, (UART_HandleTypeDef * huart, uint8_t *pData, uint16_t Size, uint32_t Timeout), ());

    // Mock method for HAL_UART_Receive
    MOCK_METHOD(HAL_StatusTypeDef, HAL_UART_Receive, (UART_HandleTypeDef * huart, uint8_t *pData, uint16_t Size, uint32_t Timeout), ());
};

// Global pointer to the MockHAL_UART instance, which will be set in the tests
extern MockHAL_UART *mockHAL_UART;

// Wrapper functions for the HAL functions that redirect to the mock
inline HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    return mockHAL_UART->HAL_UART_Transmit(huart, pData, Size, Timeout);
}

inline HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
    return mockHAL_UART->HAL_UART_Receive(huart, pData, Size, Timeout);
}

#endif // stm32f1xx_hal_uart_mock_h