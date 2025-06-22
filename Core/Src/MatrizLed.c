/*
 * MatrizLed.c
 *
 *  Created on: Jun 19, 2025
 *      Author: andrey
 */
#include "main.h"

volatile MatrizLED_t MatrizLed = {0};

void taskMatrizLed(void) //150us de execucao
{
    static volatile uint8_t line = 0;
    static volatile uint16_t line_m = 0b1000000000000000;

    volatile uint16_t aux_line = 0x00;
    volatile uint8_t aux_line2 = 0x00;

    line++;
    if (line == 16)
        line = 0;
    aux_line = (line_m >> line) | (line_m << (15 - line));

    for (int i = 0; i < 8; i++)
    {
        if (MatrizLed[line][7 - i] == 0)
            HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);
        else
            HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);

        HAL_GPIO_TogglePin(CLK1_GPIO_Port, CLK1_Pin);
        DWT_Delay_us(1);
        HAL_GPIO_TogglePin(CLK1_GPIO_Port, CLK1_Pin);
        DWT_Delay_us(1);
    }
    for (int i = 0; i < 16; i++)
    {
        aux_line2 = (aux_line >> i) & 0x0001;
        if (aux_line2 == 0)
            HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_RESET);
        else
            HAL_GPIO_WritePin(D_GPIO_Port, D_Pin, GPIO_PIN_SET);

        HAL_GPIO_TogglePin(CLK1_GPIO_Port, CLK1_Pin);

        DWT_Delay_us(1);
        HAL_GPIO_TogglePin(CLK1_GPIO_Port, CLK1_Pin);

        DWT_Delay_us(1);
    }
    HAL_GPIO_TogglePin(CLK2_GPIO_Port, CLK2_Pin);
    DWT_Delay_us(1);
    HAL_GPIO_TogglePin(CLK2_GPIO_Port, CLK2_Pin);
    DWT_Delay_us(1);
}

void changeMatriz(MatrizLED_t newMatriz)
{
    for (int i = 0; i < LinhasMatriz; i++)
    {
        for (int j = 0; j < ColunasMatriz; j++)
        {
            MatrizLed[i][j] = newMatriz[i][j];
        }
    }
}