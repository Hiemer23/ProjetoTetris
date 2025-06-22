/*
 * ManagerTetris.c
 *
 *  Created on: Jun 19, 2025
 *      Author: andrey
 */

#include "main.h"

static int linha = 0, coluna = 0, peca_atual = 0, running = FALSE; // Posição inicial da peça
PecaTetris peca;

// Funções

void initGame(void)
{
	srand(HAL_GetTick());
    peca_atual = number_aleatory_peace(); // Gera a primeira peça aleatória
    peca = pecas[peca_atual];
    linha = 0;
    coluna = 3;
    init_game();
    running = TRUE; // Inicia o jogo
    place_piece(linha, coluna, peca);
    clear_pontuacao();
    // limpaTela();
    // draw_board();
}

void taskTetris(void)
{
    if (game_over()) // Verifica se o jogo acabou
    {
        running = FALSE; // Para o jogo
        resetBotaoEvento();
        return;
    }
    if(getDireita())
    {
        resetDireitaEsquerda();
        move_piece_right(&linha, &coluna, peca);
        draw_board();
    }
    if (getEsquerda())
    {
        resetDireitaEsquerda();
        move_piece_left(&linha, &coluna, peca);
        draw_board();
    }
    // if (getCima())
    // {
    //     resetCimaBaixo();
    //     rotate_piece_right(linha, coluna, &peca);
    //     draw_board();
    // }

    if (getBaixo())
    {
        resetCimaBaixo();
        move_piece_down(&linha, &coluna, &peca, &peca_atual);
        draw_board();
    }
    if (getBotaoEvento())
    {
        resetBotaoEvento();
        rotate_piece_right(linha, coluna, &peca);
        draw_board();
    }

    update_game(&linha, &coluna, &peca, &peca_atual);
}

int gameRunning(void)
{
    return running; // Retorna o estado do jogo
}
