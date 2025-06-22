/*
 * LCD_Manager.h
 *
 *  Created on: Jun 17, 2025
 *      Author: 2021000267
 */

#ifndef INC_LCD_MANAGER_H_
#define INC_LCD_MANAGER_H_

// Enum
typedef enum
{
    TELA1,
    TELA2,
    TELA3,
    TELA4,
    TELANEXTPIECE,
    FIM,
    TELATESTE
} estados_LCD;

// Prototipos
void lcd_Task(void);
void changeLCDScreen(estados_LCD novaTela);
void initLCD(void);

#endif /* INC_LCD_MANAGER_H_ */
