#ifndef stm32f1xx_hal_adc_h
#define stm32f1xx_hal_adc_h

#include <gmock/gmock.h>
#include <stdint.h>
#include "main.h"

typedef struct __ADC_HandleTypeDef
{
    uint32_t dummy;
} ADC_HandleTypeDef;

// Mock class for HAL functions
class MockHAL
{
public:
    MOCK_METHOD(HAL_StatusTypeDef, HAL_ADC_Start_DMA, (ADC_HandleTypeDef * hadc, uint32_t *pData, uint32_t Length), ());
    MOCK_METHOD(HAL_StatusTypeDef, HAL_ADC_Stop_DMA, (ADC_HandleTypeDef * hadc), ());

private:
};

// Global pointer to the MockHAL instance, which will be set in the tests
extern MockHAL *mockHAL;

// Wrapper functions for the HAL functions that redirect to the mock
inline HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length)
{
    return mockHAL->HAL_ADC_Start_DMA(hadc, pData, Length);
}

inline HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef *hadc)
{
    return mockHAL->HAL_ADC_Stop_DMA(hadc);
}

#endif