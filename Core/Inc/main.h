/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32g0xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define SMG_POWER_Pin GPIO_PIN_1
#define SMG_POWER_GPIO_Port GPIOA
#define TM1639_STB_Pin GPIO_PIN_4
#define TM1639_STB_GPIO_Port GPIOA
#define TM1639_DIO_Pin GPIO_PIN_5
#define TM1639_DIO_GPIO_Port GPIOA
#define TM1639_SCLK_Pin GPIO_PIN_6
#define TM1639_SCLK_GPIO_Port GPIOA
#define KEY_D7_Pin GPIO_PIN_0
#define KEY_D7_GPIO_Port GPIOB
#define KEY_D6_Pin GPIO_PIN_1
#define KEY_D6_GPIO_Port GPIOB
#define KEY_D5_Pin GPIO_PIN_2
#define KEY_D5_GPIO_Port GPIOB
#define KEY_D4_Pin GPIO_PIN_10
#define KEY_D4_GPIO_Port GPIOB
#define LED_POWER_Pin GPIO_PIN_12
#define LED_POWER_GPIO_Port GPIOB
#define LED_TIME_Pin GPIO_PIN_14
#define LED_TIME_GPIO_Port GPIOB
#define LED_FAN_Pin GPIO_PIN_15
#define LED_FAN_GPIO_Port GPIOB
#define LED_KILL_Pin GPIO_PIN_8
#define LED_KILL_GPIO_Port GPIOA
#define LED_DRY_Pin GPIO_PIN_9
#define LED_DRY_GPIO_Port GPIOA
#define LED_AI_Pin GPIO_PIN_6
#define LED_AI_GPIO_Port GPIOC
#define LED_D3_Pin GPIO_PIN_7
#define LED_D3_GPIO_Port GPIOC
#define KEY_D2_Pin GPIO_PIN_10
#define KEY_D2_GPIO_Port GPIOA
#define KEY_D1_Pin GPIO_PIN_11
#define KEY_D1_GPIO_Port GPIOA
#define KEY_D0_Pin GPIO_PIN_12
#define KEY_D0_GPIO_Port GPIOA
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
