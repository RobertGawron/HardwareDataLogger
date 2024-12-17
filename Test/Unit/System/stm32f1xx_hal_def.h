#ifndef stm32f1xx_hal_def
#define stm32f1xx_hal_def

#include <cstdint>

enum HAL_StatusTypeDef : std::uint8_t
{
    HAL_OK = 0,
    HAL_ERROR = 1,
    HAL_BUSY = 2,
    HAL_TIMEOUT = 3
};

#endif // stm32f1xx_hal_def
