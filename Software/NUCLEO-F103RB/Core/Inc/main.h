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
extern "C" {
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

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
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
#define SD_CS_Pin GPIO_PIN_4
#define SD_CS_GPIO_Port GPIOA
#define BACKGROUND_LIGHT_SENSOR_Pin GPIO_PIN_5
#define BACKGROUND_LIGHT_SENSOR_GPIO_Port GPIOC
#define SPI1_CS_LCD_Pin GPIO_PIN_1
#define SPI1_CS_LCD_GPIO_Port GPIOB
#define ESP32_FLASH_MODE_Pin GPIO_PIN_6
#define ESP32_FLASH_MODE_GPIO_Port GPIOC
#define SPI1_RST_LCD_Pin GPIO_PIN_7
#define SPI1_RST_LCD_GPIO_Port GPIOC
#define ESP32_RST_Pin GPIO_PIN_8
#define ESP32_RST_GPIO_Port GPIOC
#define SPI1_DC_LCD_Pin GPIO_PIN_8
#define SPI1_DC_LCD_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define ESP32_TX_Pin GPIO_PIN_10
#define ESP32_TX_GPIO_Port GPIOC
#define ESP32_RX_Pin GPIO_PIN_11
#define ESP32_RX_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define LCD_BACKLIGHT_PWM_Pin GPIO_PIN_5
#define LCD_BACKLIGHT_PWM_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
