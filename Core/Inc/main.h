/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EEPROM.h"
#include "input.h"
#include "LCD_Manager.h"
#include "lcdDisplay.h"
#include "ManagerTetris.h"
#include "MatrizLed.h"
#include "tetris.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern EstadoMenu estadoMenu;
extern ModoMenu modoMenu;
/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void DWT_Delay_us(uint32_t us);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_RS_Pin GPIO_PIN_13
#define LCD_RS_GPIO_Port GPIOC
#define LCD_E_Pin GPIO_PIN_14
#define LCD_E_GPIO_Port GPIOC
#define LCD_D4_Pin GPIO_PIN_3
#define LCD_D4_GPIO_Port GPIOA
#define LCD_D5_Pin GPIO_PIN_4
#define LCD_D5_GPIO_Port GPIOA
#define LCD_D6_Pin GPIO_PIN_5
#define LCD_D6_GPIO_Port GPIOA
#define LCD_D7_Pin GPIO_PIN_6
#define LCD_D7_GPIO_Port GPIOA
#define BOTAO_Pin GPIO_PIN_11
#define BOTAO_GPIO_Port GPIOB
#define D_Pin GPIO_PIN_12
#define D_GPIO_Port GPIOB
#define CLK1_Pin GPIO_PIN_13
#define CLK1_GPIO_Port GPIOB
#define CLK2_Pin GPIO_PIN_14
#define CLK2_GPIO_Port GPIOB
#define TestePin_Pin GPIO_PIN_4
#define TestePin_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define TRUE 1
#define FALSE 0
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
