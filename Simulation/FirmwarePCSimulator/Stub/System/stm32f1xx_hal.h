#ifndef stm32f1xx_hal
#define stm32f1xx_hal

#include <stdint.h>

typedef struct
{
    uint8_t dummy;
} GPIO_TypeDef;

typedef struct SPI_HandleTypeDef
{
    uint8_t dummy;
} SPI_HandleTypeDef;

typedef enum
{
  GPIO_PIN_RESET = 0u,
  GPIO_PIN_SET
} GPIO_PinState;




#define GPIOB_BASE 0
#define GPIOB               ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOA               ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *)GPIOB_BASE)

#define GPIO_PIN_1                 ((uint16_t)0x0002) 
#define GPIO_PIN_7                 ((uint16_t)0x0002) 
#define GPIO_PIN_8                 ((uint16_t)0x0002) 

#define HAL_MAX_DELAY      0xFFFFFFFFU

typedef  void HAL_StatusTypeDef;

void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);

HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size, uint32_t Timeout);

void HAL_Delay(uint32_t Delay);

#endif