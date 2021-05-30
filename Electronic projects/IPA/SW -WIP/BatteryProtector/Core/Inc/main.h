/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32l0xx_hal.h"

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
#define NMOS_LBO_Pin GPIO_PIN_14
#define NMOS_LBO_GPIO_Port GPIOC
#define NMOS_OFF_Pin GPIO_PIN_15
#define NMOS_OFF_GPIO_Port GPIOC
#define NMOS_ON_Pin GPIO_PIN_0
#define NMOS_ON_GPIO_Port GPIOA
#define Current_Pin GPIO_PIN_3
#define Current_GPIO_Port GPIOA
#define CELL_1_Pin GPIO_PIN_6
#define CELL_1_GPIO_Port GPIOA
#define CELL_2_Pin GPIO_PIN_7
#define CELL_2_GPIO_Port GPIOA
#define CELL_3_Pin GPIO_PIN_0
#define CELL_3_GPIO_Port GPIOB
#define Temp_Pin GPIO_PIN_1
#define Temp_GPIO_Port GPIOB
#define LED_RED_Pin GPIO_PIN_15
#define LED_RED_GPIO_Port GPIOA
#define LED_ORANGE_Pin GPIO_PIN_3
#define LED_ORANGE_GPIO_Port GPIOB
#define LED_GREEN_Pin GPIO_PIN_4
#define LED_GREEN_GPIO_Port GPIOB
#define LED_BUTTON_Pin GPIO_PIN_5
#define LED_BUTTON_GPIO_Port GPIOB
#define LED_BUTTON_EXTI_IRQn EXTI4_15_IRQn
#define FORCE_Button_Pin GPIO_PIN_6
#define FORCE_Button_GPIO_Port GPIOB
#define FORCE_Button_EXTI_IRQn EXTI4_15_IRQn
#define FORCE_LED_Pin GPIO_PIN_7
#define FORCE_LED_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
