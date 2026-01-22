/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

  /* Private includes ----------------------------------------------------------*/
  /* USER CODE BEGIN Includes */

  /* USER CODE END Includes */

  /* Exported types ------------------------------------------------------------*/
  /* USER CODE BEGIN ET */

  /* USER CODE END ET */

  /* Exported constants --------------------------------------------------------*/
  /* USER CODE BEGIN EC */

  /* USER CODE END EC */

  /* Exported macro ------------------------------------------------------------*/
  /* USER CODE BEGIN EM */

  /* USER CODE END EM */

  void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

  /* Exported functions prototypes ---------------------------------------------*/
  void Error_Handler(void);

  /* USER CODE BEGIN EFP */

#ifdef __cplusplus
  extern "C"
  {
#endif

    extern USART_HandleTypeDef husart1;
    extern USART_HandleTypeDef husart2;
    extern USART_HandleTypeDef husart3;
    extern ADC_HandleTypeDef hadc1;
    extern TIM_HandleTypeDef htim3;

#ifdef __cplusplus
  }
#endif

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USB_ENUM_Pin GPIO_PIN_13
#define USB_ENUM_GPIO_Port GPIOC
#define KEY_LEFT_Pin GPIO_PIN_0
#define KEY_LEFT_GPIO_Port GPIOC
#define KEY_RIGHT_Pin GPIO_PIN_1
#define KEY_RIGHT_GPIO_Port GPIOC
#define KEY_UP_Pin GPIO_PIN_2
#define KEY_UP_GPIO_Port GPIOC
#define KEY_DOWN_Pin GPIO_PIN_3
#define KEY_DOWN_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LCD_RST_Pin GPIO_PIN_2
#define LCD_RST_GPIO_Port GPIOB
#define BNC1_Pin GPIO_PIN_6
#define BNC1_GPIO_Port GPIOC
#define BNC2_Pin GPIO_PIN_7
#define BNC2_GPIO_Port GPIOC
#define BNC3_Pin GPIO_PIN_8
#define BNC3_GPIO_Port GPIOC
#define BNC4_Pin GPIO_PIN_9
#define BNC4_GPIO_Port GPIOC
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define LCD_DC_Pin GPIO_PIN_15
#define LCD_DC_GPIO_Port GPIOA
#define LCD_CS_Pin GPIO_PIN_2
#define LCD_CS_GPIO_Port GPIOD
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define SD_CS_Pin GPIO_PIN_4
#define SD_CS_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define SD_SPI_Handle hspi1
#define LCD_SPI_Handle hspi1
  /* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
