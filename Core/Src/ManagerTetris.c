/*
 * ManagerTetris.c
 *
 *  Created on: Jun 19, 2025
 *      Author: andrey
 */

#include "ManagerTetris.h"

static int linha = 0, coluna = 0, peca_atual = 0;                // Posição inicial da peça
PecaTetris peca;


void initGame(void)
{
	peca_atual = number_aleatory_peace(); // Gera a primeira peça aleatória
    peca = pecas[peca_atual];
    linha = 0;
    coluna = 3;
	init_game();

    place_piece(linha, coluna, peca);
    //limpaTela();
    //draw_board();

}

void taskTetris(void)
{
    if (game_over()) // Verifica se o jogo acabou
    {
        return;
    }

    update_game(&linha, &coluna, &peca, &peca_atual);
}
