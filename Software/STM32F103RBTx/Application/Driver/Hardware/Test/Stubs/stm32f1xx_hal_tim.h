#ifndef stm32f1xx_hal_tim_h
#define stm32f1xx_hal_tim_h

#if 0
// Code can't be fix, we need compatibility with stm32f1xx_hal_tim.h naming conventions.
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreserved-identifier"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdint.h>

#include "stm32f1xx_hal_def.h"

// Can't fix, HAL related implementation.

// codechecker_suppress [modernize-macro-to-enum]
#define TIM_CHANNEL_2 0x00000004U

// codechecker_suppress [modernize-macro-to-enum]
#define TIM_COUNTERMODE_UP 0x00000000U

// codechecker_suppress [modernize-macro-to-enum]
#define TIM_CLOCKDIVISION_DIV1 0x00000000U

// codechecker_suppress [modernize-macro-to-enum]
#define TIM_AUTORELOAD_PRELOAD_ENABLE 0xcafe

// codechecker_suppress [modernize-macro-to-enum]
#define TIM_OCMODE_PWM1 0xcafe

// codechecker_suppress [modernize-macro-to-enum]
#define TIM_OCPOLARITY_HIGH 0xcafe

// codechecker_suppress [modernize-macro-to-enum]
#define TIM_OCFAST_DISABLE 0xcafe

// dummy way, but I dont need better for now.
using TIM_TypeDef = std::uint8_t;

// Can't fix, HAL related implementation.
// codechecker_suppress [modernize-macro-to-enum]
#define TIM3 (static_cast<TIM_TypeDef *>(nullptr))

struct TIM_Base_InitTypeDef
{
    std::uint32_t Prescaler;
    std::uint32_t CounterMode;
    std::uint32_t Period;
    std::uint32_t ClockDivision;
    std::uint32_t RepetitionCounter;
    std::uint32_t AutoReloadPreload;
};

struct TIM_HandleTypeDef
{
    TIM_TypeDef *Instance;
    TIM_Base_InitTypeDef Init;
};

struct TIM_OC_InitTypeDef
{
    std::uint32_t OCMode;
    std::uint32_t Pulse;
    std::uint32_t OCPolarity;
    std::uint32_t OCNPolarity;
    std::uint32_t OCFastMode;
    std::uint32_t OCIdleState;
    std::uint32_t OCNIdleState;
};

// Mock for STM32 HAL timer functions
class MockTimer
{
public:
    MOCK_METHOD(HAL_StatusTypeDef, HAL_TIM_PWM_Init, (TIM_HandleTypeDef * htim), ());
    MOCK_METHOD(HAL_StatusTypeDef, HAL_TIM_PWM_ConfigChannel, (TIM_HandleTypeDef * htim, TIM_OC_InitTypeDef *sConfig, std::uint32_t channel), ());
    MOCK_METHOD(HAL_StatusTypeDef, HAL_TIM_PWM_Start, (TIM_HandleTypeDef * htim, std::uint32_t channel), ());
    MOCK_METHOD(HAL_StatusTypeDef, HAL_TIM_PWM_Stop, (TIM_HandleTypeDef * htim, std::uint32_t channel), ());

    // two bellow are macros in real code, it doesn't mater if in tests they will be functions

    // Can't fix, HAL related implementation.
    // codechecker_suppress [bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp]
    MOCK_METHOD(void, __HAL_TIM_SET_COMPARE, (TIM_HandleTypeDef * htim, std::uint32_t Channel, std::uint32_t Compare), ());

    // Can't fix, HAL related implementation.
    // codechecker_suppress [bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp]
    MOCK_METHOD(void, __HAL_RCC_TIM3_CLK_ENABLE, (), ());
};

extern MockTimer *mockTimer; // Global pointer to access the mock in production code

// Wrapper function for HAL_TIM_PWM_Init
inline HAL_StatusTypeDef HAL_TIM_PWM_Init(TIM_HandleTypeDef *htim)
{
    return mockTimer->HAL_TIM_PWM_Init(htim);
}

// Wrapper function for HAL_TIM_PWM_ConfigChannel
inline HAL_StatusTypeDef HAL_TIM_PWM_ConfigChannel(TIM_HandleTypeDef *htim, TIM_OC_InitTypeDef *sConfig, std::uint32_t channel)
{
    return mockTimer->HAL_TIM_PWM_ConfigChannel(htim, sConfig, channel);
}

// Wrapper function for HAL_TIM_PWM_Start
inline HAL_StatusTypeDef HAL_TIM_PWM_Start(TIM_HandleTypeDef *htim, std::uint32_t channel)
{
    return mockTimer->HAL_TIM_PWM_Start(htim, channel);
}

// Wrapper function for HAL_TIM_PWM_Stop
inline HAL_StatusTypeDef HAL_TIM_PWM_Stop(TIM_HandleTypeDef *htim, std::uint32_t channel)
{
    return mockTimer->HAL_TIM_PWM_Stop(htim, channel);
}

// Since these were originally macros, redefine them as inline functions for testing purposes.

// Wrapper function for HAL_TIM_SET_COMPARE
// Can't fix, HAL related implementation.
// codechecker_suppress [bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp]
inline void __HAL_TIM_SET_COMPARE(TIM_HandleTypeDef *htim, std::uint32_t Channel, std::uint32_t Compare)
{
    mockTimer->__HAL_TIM_SET_COMPARE(htim, Channel, Compare);
}

// Wrapper function for __HAL_RCC_TIM3_CLK_ENABLE
// Can't fix, HAL related implementation.
// codechecker_suppress [bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp]
inline void __HAL_RCC_TIM3_CLK_ENABLE()
{
    mockTimer->__HAL_RCC_TIM3_CLK_ENABLE();
}

#pragma clang diagnostic pop

#endif

#endif
