/*
 * tetris.h
 *
 *  Created on: Jun 19, 2025
 *      Author: andrey
 */

#ifndef INC_TETRIS_H_
#define INC_TETRIS_H_


// Definições de tamanhos do tabuleiro e tempo de jogo
#define ROWS 16          // Número de linhas do tabuleiro
#define COLS 8           // Número de colunas do tabuleiro
#define DEBUG 1          // Ativa/Desativa mensagens de debug
#define TEMPO_BASE 750   // Tempo base (em milissegundos) para movimentação das peças

// Definição da estrutura para as peças
typedef struct
{
    int shape[4][4]; // Matriz 4x4 representando a forma da peça
} PecaTetris;

// Declaração das peças do jogo (7 peças principais)
extern PecaTetris pecas[7];

/* ---------------------------------- Funções do Jogo ---------------------------------- */

/**
 * @brief Inicializa o jogo.
 *
 * Função responsável por inicializar o estado do tabuleiro e das variáveis do jogo.
 */
void init_game();

/**
 * @brief Desenha o tabuleiro na tela.
 *
 * Função responsável por desenhar o estado atual do tabuleiro, exibindo as peças no local correto.
 */
void draw_board();

/**
 * @brief Coloca a peça no tabuleiro.
 *
 * Coloca uma peça em uma posição específica do tabuleiro.
 *
 * @param linha Linha onde a peça será colocada.
 * @param coluna Coluna onde a peça será colocada.
 * @param peca Peça a ser colocada no tabuleiro.
 */
void place_piece(int linha, int coluna, PecaTetris peca);

/**
 * @brief Gera um número aleatório para a peça.
 *
 * Gera um número aleatório entre 0 e 6 para escolher uma peça aleatória.
 *
 * @return Índice da peça gerada.
 */
int number_aleatory_peace();

/**
 * @brief Verifica se a peça atingiu o fundo ou colidiu com outra peça.
 *
 * Verifica se a peça chegou ao fundo do tabuleiro ou se há uma peça fixa embaixo dela.
 *
 * @param linha Linha atual da peça.
 * @param coluna Coluna atual da peça.
 * @param peca Peça em movimento.
 * @return 1 se atingiu o fundo, 0 caso contrário.
 */
int check_piece_at_bottom(int *linha, int *coluna, PecaTetris peca);

/**
 * @brief Fixação da peça no tabuleiro.
 *
 * Quando a peça não pode mais se mover, ela é fixada no tabuleiro.
 *
 * @param linha Linha onde a peça deve ser fixada.
 * @param coluna Coluna onde a peça deve ser fixada.
 * @param peca Peça a ser fixada.
 */
void fix_piece(int *linha, int *coluna, PecaTetris peca);

/**
 * @brief Gera a próxima peça a ser utilizada no jogo.
 *
 * Gera uma nova peça aleatória e define sua posição inicial no topo do tabuleiro.
 *
 * @param linha Linha onde a próxima peça será colocada (inicialmente 0).
 * @param coluna Coluna onde a próxima peça será colocada (inicialmente 3).
 * @param peca A próxima peça gerada.
 * @param peca_atual Índice da próxima peça gerada.
 */
void generate_next_piece(int *linha, int *coluna, PecaTetris *peca, int *peca_atual);

/**
 * @brief Remove as linhas completas do tabuleiro.
 *
 * Verifica e remove as linhas completas, deslocando as linhas acima.
 */
void remove_full_lines();

/**
 * @brief Função que verifica se o jogo acabou.
 *
 * Retorna 1 caso o jogo tenha acabado, caso contrário 0.
 *
 * @return 1 se o jogo acabou, 0 caso contrário.
 */
int game_over();

/* ----------------------------- Funções de Movimentação ----------------------------- */

/**
 * @brief Move a peça para a direita, se possível.
 *
 * Move a peça para a direita se o movimento for válido.
 *
 * @param linha Ponteiro para a posição vertical da peça.
 * @param coluna Ponteiro para a posição horizontal da peça.
 * @param peca A peça a ser movida.
 */
void move_piece_right(int *linha, int *coluna, PecaTetris peca);

/**
 * @brief Move a peça para a esquerda, se possível.
 *
 * Move a peça para a esquerda se o movimento for válido.
 *
 * @param linha Ponteiro para a posição vertical da peça.
 * @param coluna Ponteiro para a posição horizontal da peça.
 * @param peca A peça a ser movida.
 */
void move_piece_left(int *linha, int *coluna, PecaTetris peca);

/**
 * @brief Verifica se a peça pode se mover para uma posição específica.
 *
 * Verifica se a peça pode se mover para a posição desejada, considerando colisões e limites do tabuleiro.
 *
 * @param new_linha Posição vertical desejada.
 * @param new_coluna Posição horizontal desejada.
 * @param peca A peça a ser movida.
 * @return 1 se o movimento for válido, 0 caso contrário.
 */
int can_move(int new_linha, int new_coluna, PecaTetris peca);

/* ----------------------------- Funções de Rotação ----------------------------- */

/**
 * @brief Rotaciona a peça para a direita.
 *
 * Rotaciona a peça no sentido horário, se possível.
 *
 * @param linha Linha atual da peça.
 * @param coluna Coluna atual da peça.
 * @param peca A peça a ser rotacionada.
 */
void rotate_piece_right(int linha, int coluna, PecaTetris *peca);

/**
 * @brief Rotaciona a peça para a esquerda.
 *
 * Rotaciona a peça no sentido anti-horário, se possível.
 *
 * @param linha Linha atual da peça.
 * @param coluna Coluna atual da peça.
 * @param peca A peça a ser rotacionada.
 */
void rotate_piece_left(int linha, int coluna, PecaTetris *peca);

/**
 * @brief Função genérica de rotação de peça.
 *
 * Realiza a rotação de uma peça para uma nova posição com base na matriz fornecida.
 *
 * @param linha Linha atual da peça.
 * @param coluna Coluna atual da peça.
 * @param new_matriz Matriz de rotação.
 * @param peca A peça a ser rotacionada.
 */
void rotate_piece(int linha, int coluna, int new_matriz[4][4], PecaTetris *peca);

/* ----------------------------- Funções de Movimentação Vertical ----------------------------- */

/**
 * @brief Move a peça para baixo, se possível.
 *
 * Move a peça para baixo se o movimento for válido.
 *
 * @param linha Ponteiro para a posição vertical da peça.
 * @param coluna Ponteiro para a posição horizontal da peça.
 * @param peca A peça a ser movida.
 * @param peca_atual Índice da próxima peça.
 * @return 1 se a peça atingiu o fundo, 0 caso contrário.
 */
int move_piece_down(int *linha, int *coluna, PecaTetris *peca, int *peca_atual);

/* ----------------------------- Função de Atualização do Jogo ----------------------------- */

/**
 * @brief Atualiza o jogo, movendo a peça para baixo com base no tempo.
 *
 * Atualiza o estado do jogo verificando se o tempo acumulado atingiu o limiar para mover a peça para baixo.
 *
 * @param linha Ponteiro para a posição vertical da peça.
 * @param coluna Ponteiro para a posição horizontal da peça.
 * @param peca A peça atual.
 * @param peca_atual Índice da próxima peça.
 */
void update_game(int *linha, int *coluna, PecaTetris *peca, int *peca_atual);

/**
 * @brief Get the next piece object
 * 
 * @return int 
 */
int get_next_piece();

/**
 * @brief Get a pontuacao Atual
 * 
 * Retorna a pontuação atual do jogo.
 * 
 * @return uint16_t A pontuação atual.
 */
uint16_t get_pontuacao(void);

/**
 * @brief limpa a pontuação do jogo.
 * 
 */
void clear_pontuacao(void);
extern uint8_t board[ROWS][COLS];

#endif /* INC_TETRIS_H_ */
