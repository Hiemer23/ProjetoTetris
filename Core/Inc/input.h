/*
 * input.h
 *
 *  Created on: Jun 21, 2025
 *      Author: andrey
 */

#ifndef INC_INPUT_H_
#define INC_INPUT_H_

#include <stdint.h>
#include "main.h"

#define AD2_THRESHOLD_LOW   200
#define AD2_THRESHOLD_HIGH  3900
#define AD2_DEADZONE_MIN    800
#define AD2_DEADZONE_MAX    3200

void initInput(ADC_HandleTypeDef *hadc);
uint16_t ler_ADC_canal(uint8_t canal);
void taskLeituraAD(void);
uint8_t getCima(void);
uint8_t getDireita(void);
uint8_t getBaixo(void);
uint8_t getEsquerda(void);
uint8_t getBotaoEvento(void);


extern uint16_t AD1, AD2, BotaoStatus;
//AD1 é o X, AD2 é o Y
#endif /* INC_INPUT_H_ */
