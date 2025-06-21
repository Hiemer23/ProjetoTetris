/*
 * File:   LCD_16x2.h
 * Author: andrey.hiemer
 *
 * Created on 22 de Março de 2023, 09:51
 */

#ifndef LCD_16X2_H
#define	LCD_16X2_H

#include "main.h"

#define LCD_delay_ms HAL_Delay
#define LCD_delay_us DWT_Delay_us

#define RS_HIGH HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET)
#define RS_LOW  HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET)

#define EN_HIGH HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_SET)
#define EN_LOW  HAL_GPIO_WritePin(LCD_E_GPIO_Port, LCD_E_Pin, GPIO_PIN_RESET)

#define DB4_HIGH HAL_GPIO_WritePin(GPIOA, LCD_D4_Pin, GPIO_PIN_SET)
#define DB4_LOW  HAL_GPIO_WritePin(GPIOA, LCD_D4_Pin, GPIO_PIN_RESET)
#define DB5_HIGH HAL_GPIO_WritePin(GPIOA, LCD_D5_Pin, GPIO_PIN_SET)
#define DB5_LOW  HAL_GPIO_WritePin(GPIOA, LCD_D5_Pin, GPIO_PIN_RESET)
#define DB6_HIGH HAL_GPIO_WritePin(GPIOA, LCD_D6_Pin, GPIO_PIN_SET)
#define DB6_LOW  HAL_GPIO_WritePin(GPIOA, LCD_D6_Pin, GPIO_PIN_RESET)
#define DB7_HIGH HAL_GPIO_WritePin(GPIOA, LCD_D7_Pin, GPIO_PIN_SET)
#define DB7_LOW  HAL_GPIO_WritePin(GPIOA, LCD_D7_Pin, GPIO_PIN_RESET)

//Prototypes:

void Write_Display(void);
void initialize_LCD(void);
void change_Message(uint8_t line, char *new_Text);

#endif	/* LCD_16X2_H */

