/*
 * MatrizLed.h
 *
 *  Created on: Jun 19, 2025
 *      Author: andrey
 */

#ifndef INC_MATRIZLED_H_
#define INC_MATRIZLED_H_

#include <stdint.h>
#include <main.h>

#define ColunasMatriz 8
#define LinhasMatriz 16

typedef uint8_t MatrizLED_t[LinhasMatriz][ColunasMatriz];

void taskMatrizLed(void);
void changeMatriz(MatrizLED_t newMatriz);

#endif /* INC_MATRIZLED_H_ */
