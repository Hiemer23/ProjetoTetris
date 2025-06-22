/*
 * LCD_Manager.c
 *
 *  Created on: Jun 17, 2025
 *      Author: 2021000267
 */

#include "main.h"
// Novos cararcteres para o jogo

// L
uint8_t pieceL[8] = {
    0B11000,
    0B11000,
    0B11000,
    0B11000,
    0B11000,
    0B11000,
    0B11111,
    0B11111};
// J
uint8_t pieceJ[8] = {
    0B00011,
    0B00011,
    0B00011,
    0B00011,
    0B00011,
    0B00011,
    0B11111,
    0B11111};
// Z
uint8_t pieceZ[8] = {
    0B00000,
    0B00000,
    0B11100,
    0B00100,
    0B00100,
    0B00111,
    0B00000,
    0B00000};
// S
uint8_t pieceS[8] = {
    0B00000,
    0B00000,
    0B00111,
    0B00100,
    0B00100,
    0B11100,
    0B00000,
    0B00000};
// T
uint8_t pieceT[8] = {
    0B00000,
    0B00000,
    0B11111,
    0B11111,
    0B00100,
    0B00100,
    0B00000,
    0B00000};
// O
uint8_t pieceO[8] = {
    0B00000,
    0B00000,
    0B01110,
    0B01110,
    0B01110,
    0B01110,
    0B00000,
    0B00000};
// I
uint8_t pieceI[8] = {
    0B01110,
    0B01110,
    0B01110,
    0B01110,
    0B01110,
    0B01110,
    0B01110,
    0B00000};

estados_LCD estadoLCD = TELA1;
uint8_t PecasLCD[7] = {CUSTOMT,CUSTOMZ,CUSTOMI,CUSTOML,CUSTOMJ,CUSTOMS,CUSTOMO};

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
    case TELATESTE:
        //char linhaTeste[16], linhaTestes2[16];                    // 16 caracteres + terminador '\0'
        // sprintf(linhaTeste, "AD1: %4u", AD1);   // %4u → valor sem sinal com 4 dígitos (ajustável)
        // change_Message(0, linhaTeste);
        
        // sprintf(linhaTestes2, "AD2:%4u Bot:%1u", AD2, BotaoStatus);   // %4u → valor sem sinal com 4 dígitos (ajustável)
        // change_Message(1, linhaTestes2);
//        sprintf(linhaTeste, "Y:%4u        ", AD2);   // %4u → valor sem sinal com 4 dígitos (ajustável)
//        change_Message(0, linhaTeste);
//        snprintf(linhaTestes2, sizeof(linhaTestes2), "Cima:%u Baixo:%u ", getCima(), getBaixo());   // %4u → valor sem sinal com 4 dígitos (ajustável)
//        change_Message(1, linhaTestes2);
        break;
    case TELANEXTPIECE:
    	char linha[16] = "Proxima Peca:   ";
        char linha2[16];
    	linha[15] = PecasLCD[get_next_piece()];
    	change_Message(0, linha);
        sprintf(linha2, "Pont:%5u ", get_pontuacao());   // %4u → valor sem sinal com 4 dígitos (ajustável)
        change_Message(1, linha2);
    	break;
	}
}

void changeLCDScreen(estados_LCD novaTela) {
	//valide que novaTela é um estado valido antes de mudar
	if (novaTela >= TELA1 && novaTela < FIM) {
		estadoLCD = novaTela;
	} else {
		estadoLCD = TELA1; // Reset to default state if invalid
	}
}

void initLCD(void) {
    initialize_LCD(); // Initialize the LCD
    lcd_create_char(1, pieceO);
    lcd_create_char(2, pieceL);
    lcd_create_char(3, pieceS);
    lcd_create_char(4, pieceZ);
    lcd_create_char(5, pieceT);
    lcd_create_char(6, pieceJ);
}
