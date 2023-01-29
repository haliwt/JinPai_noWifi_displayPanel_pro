/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.h
  * @brief   This file contains all the function prototypes for
  *          the gpio.c file
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
#ifndef __GPIO_H__
#define __GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

/* USER CODE BEGIN Prototypes */

//AI Function GPIO 
/* USER CODE BEGIN Private defines */
#define PA0_INT_Pin 					GPIO_PIN_0
#define PA0_INT_GPIO_Port 				GPIOA



#define POWER_KEY_Pin                   GPIO_PIN_7
#define POWER_KEY_GPIO_Port             GPIOC


#define MODE_KEY_Pin                    GPIO_PIN_10
#define MODE_KEY_GPIO_Port              GPIOA

#define DEC_KEY_Pin 					GPIO_PIN_11
#define DEC_KEY_GPIO_Port 				GPIOA

#define ADD_KEY_Pin 					GPIO_PIN_12
#define ADD_KEY_GPIO_Port 				GPIOA



#define FAN_KEY_Pin                             GPIO_PIN_0
#define FAN_KEY_GPIO_Port                       GPIOB

#define STER_KEY_Pin                            GPIO_PIN_1
#define STER_KEY_GPIO_Port                      GPIOB

#define DRY_KEY_Pin                             GPIO_PIN_2
#define DRY_KEY_GPIO_Port                       GPIOB

#define AI_KEY_Pin                              GPIO_PIN_10
#define AI_KEY_GPIO_Port                        GPIOB



#define INT_KEY_VALUE()              HAL_GPIO_ReadPin(GPIOA,PA0_INT_Pin)//
#define POWER_KEY_VALUE()            HAL_GPIO_ReadPin(POWER_KEY_GPIO_Port ,POWER_KEY_Pin)
#define MODE_KEY_VALUE()             HAL_GPIO_ReadPin(GPIOA,MODE_KEY_Pin)
#define DEC_KEY_VALUE()              HAL_GPIO_ReadPin(GPIOA,DEC_KEY_Pin)
#define ADD_KEY_VALUE()              HAL_GPIO_ReadPin(GPIOA,ADD_KEY_Pin)


#define FAN_KEY_VALUE()              HAL_GPIO_ReadPin(GPIOB,FAN_KEY_Pin)
#define STER_KEY_VALUE()              HAL_GPIO_ReadPin(GPIOB,STER_KEY_Pin)
#define DRY_KEY_VALUE()              HAL_GPIO_ReadPin(GPIOB,DRY_KEY_Pin)
#define AI_KEY_VALUE()              HAL_GPIO_ReadPin(GPIOB,AI_KEY_Pin)
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ GPIO_H__ */

