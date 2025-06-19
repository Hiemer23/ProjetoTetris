/*
 * LCD_Manager.c
 *
 *  Created on: Jun 17, 2025
 *      Author: 2021000267
 */

#include "LCD_Manager.h"

estados_LCD estadoLCD = TELA1;

void lcd_Task(void) {
	//4 estados na máquina de estados

	switch (estadoLCD) {
	default:
		estadoLCD = TELA1;
	case TELA1:
		change_Message(0, ">>Start Game");
		change_Message(1, "Recorde Atual");
		break;
	case TELA2:
		change_Message(0, ">>Recorde Atual");
		change_Message(1, "Gravar Nome");
		break;
	case TELA3:
		change_Message(0, ">>Gravar Nome");
		change_Message(1, "Limpar Recorde");
		break;
	case TELA4:
		change_Message(0, ">>Limpar Recorde");
		change_Message(1, "Start Game");
		break;
	}
}

void changeLCDScreen(estados_LCD novaTela) {
	//valide que novaTela é um estado valido antes de mudar
	if (novaTela >= TELA1 && novaTela <= TELA4) {
		estadoLCD = novaTela;
	} else {
		estadoLCD = TELA1; // Reset to default state if invalid
	}
}
