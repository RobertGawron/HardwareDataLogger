#include "stm32f1xx_hal.h"

#include <stdio.h>

SPI_HandleTypeDef hspi1;

void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
}

// 0 as first clean screen, then color
HAL_StatusTypeDef HAL_SPI_Transmit(SPI_HandleTypeDef *hspi, const uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  for (int i = 0; i< Size; i++)
  {
    printf("%2X ", pData[i]);
  } 
  printf("\n");
} 
 
void HAL_Delay(uint32_t Delay)
{
}
