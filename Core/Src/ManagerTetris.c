/*
 * ManagerTetris.c
 *
 *  Created on: Jun 19, 2025
 *      Author: andrey
 */

#include "ManagerTetris.h"

static int linha = 0, coluna = 0, peca_atual = 0; // Posição inicial da peça
PecaTetris peca;

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

// Funções

void initGame(void)
{
    peca_atual = number_aleatory_peace(); // Gera a primeira peça aleatória
    peca = pecas[peca_atual];
    linha = 0;
    coluna = 3;
    init_game();

    place_piece(linha, coluna, peca);
    // limpaTela();
    // draw_board();

    lcd_create_char(1, pieceO);
    lcd_create_char(2, pieceL);
    lcd_create_char(3, pieceS);
    lcd_create_char(4, pieceZ);
    lcd_create_char(5, pieceT);
    lcd_create_char(6, pieceJ);
}

void taskTetris(void)
{
    if (game_over()) // Verifica se o jogo acabou
    {
        return;
    }

    update_game(&linha, &coluna, &peca, &peca_atual);
}
