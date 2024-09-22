#ifndef stm32f1xx_hal_tim_h
#define stm32f1xx_hal_tim_h

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdint.h>
#include "main.h"

using namespace testing;

#define TIM_CHANNEL_2 0x00000004U
#define TIM_COUNTERMODE_UP 0x00000000U
#define TIM_CLOCKDIVISION_DIV1 0x00000000U
#define TIM_AUTORELOAD_PRELOAD_ENABLE 0xcafe
#define TIM_OCMODE_PWM1 0xcafe
#define TIM_OCPOLARITY_HIGH 0xcafe
#define TIM_OCFAST_DISABLE 0xcafe

typedef struct
{
    uint32_t Prescaler;
    uint32_t CounterMode;
    uint32_t Period;
    uint32_t ClockDivision;
    uint32_t RepetitionCounter;
    uint32_t AutoReloadPreload;
} TIM_Base_InitTypeDef;

// dummy way, but I dont need better for now.
using TIM_TypeDef = uint8_t;
#define TIM3 0x0

typedef struct
{
    TIM_TypeDef Instance;
    TIM_Base_InitTypeDef Init;
} TIM_HandleTypeDef;

typedef struct
{
    uint32_t OCMode;
    uint32_t Pulse;
    uint32_t OCPolarity;
    uint32_t OCNPolarity;
    uint32_t OCFastMode;
    uint32_t OCIdleState;
    uint32_t OCNIdleState;
} TIM_OC_InitTypeDef;

// Mock for STM32 HAL timer functions
class MockTimer
{
public:
    MOCK_METHOD(HAL_StatusTypeDef, HAL_TIM_PWM_Init, (TIM_HandleTypeDef * htim), ());
    MOCK_METHOD(HAL_StatusTypeDef, HAL_TIM_PWM_ConfigChannel, (TIM_HandleTypeDef * htim, TIM_OC_InitTypeDef *sConfig, uint32_t channel), ());
    MOCK_METHOD(HAL_StatusTypeDef, HAL_TIM_PWM_Start, (TIM_HandleTypeDef * htim, uint32_t channel), ());
    MOCK_METHOD(HAL_StatusTypeDef, HAL_TIM_PWM_Stop, (TIM_HandleTypeDef * htim, uint32_t channel), ());
    // two bellow are macros in real code, it doesn't mater if in tests they will be functions
    MOCK_METHOD(void, __HAL_TIM_SET_COMPARE, (TIM_HandleTypeDef * htim, uint32_t Channel, uint32_t Compare), ());
    MOCK_METHOD(void, __HAL_RCC_TIM3_CLK_ENABLE, (), ());
};

extern MockTimer *mockTimer; // Global pointer to access the mock in production code

// Wrapper function for HAL_TIM_PWM_Init
inline HAL_StatusTypeDef HAL_TIM_PWM_Init(TIM_HandleTypeDef *htim)
{
    return mockTimer->HAL_TIM_PWM_Init(htim);
}

// Wrapper function for HAL_TIM_PWM_ConfigChannel
inline HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *sConfig, uint32_t channel)
{
    return mockTimer->HAL_TIM_PWM_ConfigChannel(htim, sConfig, channel);
}

// Wrapper function for HAL_TIM_PWM_Start
inline HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, uint32_t channel)
{
    return mockTimer->HAL_TIM_PWM_Start(htim, channel);
}

// Wrapper function for HAL_TIM_PWM_Stop
inline HAL_StatusTypeDef HAL_TIM_PWM_Stop(TIM_HandleTypeDef *htim, uint32_t channel)
{
    return mockTimer->HAL_TIM_PWM_Stop(htim, channel);
}

// Since these were originally macros, redefine them as inline functions for testing purposes.

// Wrapper function for HAL_TIM_SET_COMPARE
inline void __HAL_TIM_SET_COMPARE(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t Compare)
{
    mockTimer->__HAL_TIM_SET_COMPARE(htim, Channel, Compare);
}

// Wrapper function for __HAL_RCC_TIM3_CLK_ENABLE
inline void __HAL_RCC_TIM3_CLK_ENABLE()
{
    mockTimer->__HAL_RCC_TIM3_CLK_ENABLE();
}

#endif
