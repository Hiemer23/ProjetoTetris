/*
 * tetris.c
 *
 *  Created on: Jun 19, 2025
 *      Author: andrey
 */


#include "main.h"

// ----------------------------------------
// VARIAVEIS UTILIZADAS NO JOGO
// ----------------------------------------

uint8_t board[ROWS][COLS]; // x eh coluna(direita e esquerda), y eh linha(cima e baixo)

PecaTetris pecas[7] = {
    {// Peça "T"
     {
         {1, 1, 1, 0},
         {0, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}}},
    {// Peça "Z"
     {
         {1, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}}},
    {// Peça "I"
     {
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 0, 0}}},
    {// Peça "L"
     {
         {0, 1, 0, 0},
         {0, 1, 0, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0}}},
    {// Peça "J"
     {
         {0, 0, 1, 0},
         {0, 0, 1, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0}}},
    {// Peça "S"
     {
         {0, 1, 1, 0},
         {1, 1, 0, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}}},
    {// Peça "O"
     {
         {0, 1, 1, 0},
         {0, 1, 1, 0},
         {0, 0, 0, 0},
         {0, 0, 0, 0}}}};

//#define TEMPO_BASE 750 // Tempo base em ms para o movimento para baixo

static int multiplicador_tempo = 1;     // Multiplicador para acelerar o jogo
static unsigned long timer_counter = 0; // Contador de milissegundos
static int pontuacao = 0;
static int nivel = 0;
static int linhas_totais = 0;
static int next_number; // Índice da próxima peça
static PecaTetris next_peace;

#define LINHAS_POR_NIVEL 10

// ----------------------------------------
// PROTIPOS PRIVADOS
// ----------------------------------------

void incrementTime();
void atualizar_pontuacao(int linhas_removidas);
void show_next_peace();

// ----------------------------------------
// FUNCOES DO JOGO
// ----------------------------------------

/**
 * @date 2025-03-09
 * @author Andrey Hiemer
 * @brief Inicializa o jogo Tetris, limpando o tabuleiro.
 * Esta função preenche o tabuleiro com zeros, garantindo que todas as
 * posições estejam vazias no início do jogo. Também inicializa a próxima peça
 * a partir de um número aleatório.
 */
void init_game()
{
    //printf("Iniciando Tetris...\n");

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            board[i][j] = 0;
        }
    }
    next_number = number_aleatory_peace();
    next_peace = pecas[next_number];
}

/**
 * @date        2025-03-08
 * @author      Andrey Hiemer
 * @brief       Exibe o tabuleiro do Tetris no console.
 *
 * Esta função imprime o estado atual do tabuleiro, representando os blocos
 * ativos, espaços vazios e blocos fixos de maneira visual para o jogador.
 * Também exibe a próxima peça a ser enviada.
 */

void draw_board()
{
    //printf("Tabuleiro:\n    0 1 2 3 4 5 6 7   Pontuacao: %d \n", pontuacao);
    for (int i = 0; i < ROWS; i++)
    {
        if (i < 10)
        {
            printf("%d - ", i);
        }
        else
        {
            printf("%d -", i);
        }

        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] == 1)
            {
                printf("█ "); // Bloco preenchido
            }
            else if (board[i][j] == 0)
            {
                printf(". "); // Espaço vazio
            }
            else if (board[i][j] == 2)
            {
                printf("[]"); // Espaço Ja preenchido e fixo
            }
        }
        printf("\n");
    }
    show_next_peace();
}

/**
 * @date        2025-03-09
 * @author      Andrey Hiemer
 * @brief       Posiciona a peça no tabuleiro.
 *
 * Esta função insere a peça na posição especificada no tabuleiro, garantindo
 * que os blocos da peça sejam corretamente representados sem ultrapassar os
 * limites do tabuleiro.
 *
 * @param linha   Posição inicial da peça no eixo vertical.
 * @param coluna  Posição inicial da peça no eixo horizontal.
 * @param peca    Estrutura contendo o formato da peça.
 */

void place_piece(int linha, int coluna, PecaTetris peca)
{

    for (int i = 0; i < 4; i++) // responsavel pela peca sentido linha
    {
        for (int j = 0; j < 4; j++) // responsavel pela peca sentido coluna
        {
            if (peca.shape[i][j] == 1)
            {
                int board_linha = linha + i;
                int board_coluna = coluna + j;

                // Verifica se está dentro dos limites do tabuleiro
                if (board_linha >= 0 && board_linha < ROWS && board_coluna >= 0 && board_coluna < COLS)
                {
                    board[board_linha][board_coluna] = 1;
                }
            }
        }
    }
}

/**
 * @date        2025-03-09
 * @author      Andrey Hiemer
 * @brief       Remove a peça do tabuleiro.
 *
 * Esta função apaga a peça da posição especificada no tabuleiro,
 * substituindo os blocos ocupados por espaços vazios.
 *
 * @param linha   Posição inicial da peça no eixo vertical.
 * @param coluna  Posição inicial da peça no eixo horizontal.
 * @param peca    Estrutura contendo o formato da peça.
 */

void remove_piece(int linha, int coluna, PecaTetris peca)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (peca.shape[i][j] == 1)
            {
                int board_linha = linha + i;
                int board_coluna = coluna + j;

                // Verifica se está dentro dos limites do tabuleiro
                if (board_linha >= 0 && board_linha < ROWS && board_coluna >= 0 && board_coluna < COLS)
                {
                    board[board_linha][board_coluna] = 0;
                }
            }
        }
    }
}

/**
 * @date        2025-03-09
 * @author      Andrey Hiemer
 * @brief       Verifica se a peça pode se mover para uma posição específica.
 *
 * Esta função verifica se a peça pode ser movida para a posição desejada
 * no tabuleiro, considerando os limites do jogo e colisões com peças fixas.
 *
 * @param linha   Posição vertical para onde a peça será movida.
 * @param coluna  Posição horizontal para onde a peça será movida.
 * @param peca    Estrutura contendo o formato da peça.
 * @return        1 se o movimento for válido, 0 caso contrário.
 */

int can_move(int linha, int coluna, PecaTetris peca)
{

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (peca.shape[i][j] == 1)
            {
                int board_linha = linha + i;
                int board_coluna = coluna + j;

                // Verifica se está dentro dos limites do tabuleiro
                if (board_linha < 0 || board_linha >= ROWS || board_coluna < 0 || board_coluna >= COLS)
                {
#ifdef DEBUG
                    printf("\nMovimento Invalido\n");
#endif
                    return 0; // Movimento inválido
                }

                // Verifica se a posição está ocupada
                if (board[board_linha][board_coluna] == 2)
                {
#ifdef DEBUG
                    printf("\nMovimento Invalido\n");
#endif
                    return 0; // Movimento inválido
                }
            }
        }
    }

    return 1; // Movimento válido
}

/**
 * @date        2025-03-09
 * @author      Andrey Hiemer
 * @brief       Move a peça uma posição para a direita, se possível.
 *
 * Esta função verifica se a peça pode ser movida para a direita.
 * Se o movimento for válido, a peça é removida da posição atual
 * e colocada na nova posição no tabuleiro.
 *
 * @param linha   Ponteiro para a posição vertical da peça.
 * @param coluna  Ponteiro para a posição horizontal da peça.
 * @param peca    Estrutura contendo o formato da peça.
 */

void move_piece_right(int *linha, int *coluna, PecaTetris peca)
{
    int new_linha = *linha + 0;
    int new_coluna = *coluna + 1;

    if (can_move(new_linha, new_coluna, peca))
    {
        // Apaga a peça da posição atual
        remove_piece(*linha, *coluna, peca);

        // Atualiza posição
        *linha = new_linha;
        *coluna = new_coluna;

        // Coloca a peça na nova posição
        place_piece(*linha, *coluna, peca);
    }
}

/**
 * @date        2025-03-09
 * @author      Andrey Hiemer
 * @brief       Move a peça uma posição para a esquerda, se possível.
 *
 * Esta função verifica se a peça pode ser movida para a esquerda.
 * Se o movimento for válido, a peça é removida da posição atual
 * e colocada na nova posição no tabuleiro.
 *
 * @param linha   Ponteiro para a posição vertical da peça.
 * @param coluna  Ponteiro para a posição horizontal da peça.
 * @param peca    Estrutura contendo o formato da peça.
 */

void move_piece_left(int *linha, int *coluna, PecaTetris peca)
{
    int new_linha = *linha + 0;
    int new_coluna = *coluna - 1;

    if (can_move(new_linha, new_coluna, peca))
    {
        // Apaga a peça da posição atual
        remove_piece(*linha, *coluna, peca);

        // Atualiza posição
        *linha = new_linha;
        *coluna = new_coluna;

        // Coloca a peça na nova posição
        place_piece(*linha, *coluna, peca);
    }
}

/**
 * @date        2025-03-08
 * @author      Andrey Hiemer
 * @brief       Rotaciona a peça 90 graus para a direita.
 *
 * Esta função cria uma matriz temporária para armazenar a peça rotacionada
 * e chama a função de rotação principal para aplicar a nova orientação.
 *
 * @param linha   Posição vertical da peça no tabuleiro.
 * @param coluna  Posição horizontal da peça no tabuleiro.
 * @param peca    Ponteiro para a estrutura da peça a ser rotacionada.
 */

void rotate_piece_right(int linha, int coluna, PecaTetris *peca)
{
    int nova_peca[4][4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            nova_peca[j][3 - i] = peca->shape[i][j];
        }
    }
    rotate_piece(linha, coluna, nova_peca, peca);
}

/**
 * @date        2025-03-08
 * @author      Andrey Hiemer
 * @brief       Rotaciona a peça 90 graus para a esquerda.
 *
 * Esta função cria uma matriz temporária para armazenar a peça rotacionada
 * e chama a função de rotação principal para aplicar a nova orientação.
 *
 * @param linha   Posição vertical da peça no tabuleiro.
 * @param coluna  Posição horizontal da peça no tabuleiro.
 * @param peca    Ponteiro para a estrutura da peça a ser rotacionada.
 */

void rotate_piece_left(int linha, int coluna, PecaTetris *peca)
{
    int nova_peca[4][4];

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            nova_peca[3 - j][i] = peca->shape[i][j];
        }
    }
    rotate_piece(linha, coluna, nova_peca, peca);
}

/**
 * @date        2025-03-08
 * @author      Andrey Hiemer
 * @brief       Rotaciona a peça para uma nova orientação, se possível.
 *
 * Esta função cria uma cópia temporária da peça rotacionada, verifica se a nova
 * posição da peça é válida, e se for, apaga a peça da posição atual, atualiza sua
 * orientação e a coloca na nova posição no tabuleiro.
 *
 * @param linha      Posição vertical da peça no tabuleiro.
 * @param coluna     Posição horizontal da peça no tabuleiro.
 * @param new_matriz Matriz 4x4 representando a peça rotacionada.
 * @param peca       Ponteiro para a estrutura da peça a ser rotacionada.
 */

void rotate_piece(int linha, int coluna, int new_matriz[4][4], PecaTetris *peca)
{

    PecaTetris pecaAux;
    // Cria uma cópia temporária para verificação
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            pecaAux.shape[i][j] = new_matriz[i][j];
        }
    }

    if (can_move(linha, coluna, pecaAux))
    {
        // Apaga a peça da posição atual
        remove_piece(linha, coluna, *peca);

        // Copia a matriz rotacionada para a peça original
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                peca->shape[i][j] = new_matriz[i][j];
            }
        }

        // Coloca a peça na nova posição
        place_piece(linha, coluna, *peca);
    }
}

/**
 * @date        2025-03-09
 * @author      Andrey Hiemer
 * @brief       Move a peça para baixo no tabuleiro, se possível.
 *
 * Esta função verifica se a peça pode ser movida para baixo. Se for possível,
 * ela é removida da posição atual e colocada na nova posição. Caso contrário,
 * a peça é fixada no tabuleiro, as linhas completas são removidas e uma nova
 * peça é gerada para continuar o jogo.
 *
 * @param linha       Ponteiro para a posição vertical da peça no tabuleiro.
 * @param coluna      Ponteiro para a posição horizontal da peça no tabuleiro.
 * @param peca        Ponteiro para a estrutura da peça que está em jogo.
 * @param peca_atual  Ponteiro para o índice da peça atual.
 * @return            Retorna 0 se a peça continuar descendo e 1 se ela foi fixada.
 */
int move_piece_down(int *linha, int *coluna, PecaTetris *peca, int *peca_atual)
{
    int nova_linha = *linha + 1;

    // Verifica se a peça pode se mover para baixo (se a linha não está fora do tabuleiro e não há outra peça no caminho)
    if (can_move(nova_linha, *coluna, *peca)) // A função can_move agora verifica se a nova posição é válida
    {
        // Apaga a peça da posição atual
        remove_piece(*linha, *coluna, *peca);

        // Atualiza a posição da peça
        *linha = nova_linha;

        // Coloca a peça na nova posição
        place_piece(*linha, *coluna, *peca);
        return 0;
    }
    else
    {
        fix_piece(linha, coluna, *peca);
        remove_full_lines();
        generate_next_piece(linha, coluna, peca, peca_atual);
        return 1;
    }
}

/**
 * @date        2025-03-08
 * @author      Andrey Hiemer
 * @brief       Gera uma peça aleatória para o jogo Tetris.
 *
 * Esta função retorna um valor aleatório entre 0 e 6, representando uma das sete peças possíveis
 * no Tetris. Cada número corresponde a um tipo de peça diferente.
 *
 * @return       Um número entre 0 e 6, representando o tipo da peça aleatória.
 */

int number_aleatory_peace()
{
    return rand() % 7; // Gera um número entre 0 e 6
}

/**
 * @date        2025-03-09
 * @author      Andrey Hiemer
 * @brief       Verifica se a peça atingiu o fundo ou colidiu com outra peça no Tetris.
 *
 * Esta função verifica se a peça atingiu o fundo do tabuleiro ou se há outra peça fixa abaixo dela.
 * Caso a peça não possa mais descer, a função retorna 1, indicando que ela deve ser fixada.
 *
 * @param linha   Ponteiro para a posição vertical da peça no tabuleiro.
 * @param coluna  Ponteiro para a posição horizontal da peça no tabuleiro.
 * @param peca    Estrutura contendo o formato da peça.
 *
 * @return 1 se a peça atingiu o fundo ou colidiu com outra peça; 0 caso contrário.
 */

int check_piece_at_bottom(int *linha, int *coluna, PecaTetris peca)
{

    // Verifique se há outra peça abaixo dela (posição da peça no tabuleiro)
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (peca.shape[i][j] == 1)
            {
                if (board[*linha + i + 1][*coluna + j] == 2 || (*linha + i) >= 15) // Se houver uma peça fixa abaixo
                {
                    return 1;
                }
            }
        }
    }

    return 0; // A peça não atingiu o fundo
}

/**
 * @date        2025-03-09
 * @author      Andrey Hiemer
 * @brief       Gera a próxima peça aleatória e define sua posição inicial no tabuleiro.
 *
 * Esta função atribui a próxima peça previamente gerada ao jogo, atualiza a próxima peça
 * para uma nova aleatória e define a posição inicial da peça recém-gerada.
 *
 * @param linha       Ponteiro para a posição vertical inicial da peça (inicialmente 0).
 * @param coluna      Ponteiro para a posição horizontal inicial da peça (inicialmente 3).
 * @param peca        Ponteiro para a estrutura da peça que será colocada no tabuleiro.
 * @param peca_atual  Ponteiro para armazenar o índice da peça atual.
 */

void generate_next_piece(int *linha, int *coluna, PecaTetris *peca, int *peca_atual)
{
    *peca_atual = next_number;
    *peca = pecas[*peca_atual];

    next_number = number_aleatory_peace();
    next_peace = pecas[next_number];

    // Define a posição inicial da nova peça
    *linha = 0;  // Começa do topo
    *coluna = 3; // Começa no meio do tabuleiro
}

/**
 * @date        2025-03-09
 * @author      Andrey Hiemer
 * @brief       Get a Proxima Peca a ser gerada.
 * 
 * Esta função exibe a próxima peça que será gerada no jogo Tetris.
 */

 int get_next_piece(){
    return next_number; // Retorna a próxima peça a ser gerada
 }

/**
 * @date        2025-03-08
 * @author      Andrey Hiemer
 * @brief       Fixa a peça no tabuleiro, tornando suas posições imutáveis.
 *
 * Esta função percorre a matriz da peça e marca as posições correspondentes no
 * tabuleiro com o valor 2, indicando que essas posições estão agora ocupadas
 * de forma permanente (fixas).
 *
 * @param linha  A linha onde a peça está atualmente posicionada no tabuleiro.
 * @param coluna A coluna onde a peça está atualmente posicionada no tabuleiro.
 * @param peca   A peça que deve ser fixada no tabuleiro.
 */

void fix_piece(int *linha, int *coluna, PecaTetris peca)
{
    // Adiciona a peça no tabuleiro, tornando-a fixa
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (peca.shape[i][j] == 1)
            {
                board[*linha + i][*coluna + j] = 2; // Marca a posição com 2, indicando que está fixa
            }
        }
    }
}

/**
 * @date        2025-03-09
 * @author      Andrey Hiemer
 * @brief       Remove as linhas completas do tabuleiro e desloca as linhas acima.
 *
 * Esta função percorre o tabuleiro de baixo para cima, verificando se alguma linha
 * está completamente preenchida. Se estiver, a linha é removida e todas as linhas
 * acima dela são deslocadas para baixo. A primeira linha do tabuleiro é então limpa.
 * Caso uma ou mais linhas sejam removidas, a pontuação e o nível do jogador são atualizados.
 */

void remove_full_lines()
{

    int linhas_removidas = 0;

    for (int i = ROWS - 1; i >= 0; i--) // Começa da última linha e vai subindo
    {
        int complete = 1;

        // Verifica se a linha está completa
        for (int j = 0; j < COLS; j++)
        {
            if (board[i][j] != 2) // Se qualquer célula não for preenchida
            {
                complete = 0;
                break; // Se a linha não estiver completa, sai do loop
            }
        }

        // Se a linha estiver completa, removemos a linha e deslocamos as linhas acima
        if (complete)
        {

            linhas_removidas++;

            // Desloca todas as linhas acima uma posição para baixo
            for (int k = i; k > 0; k--)
            {
                for (int j = 0; j < COLS; j++)
                {
                    board[k][j] = board[k - 1][j];
                }
            }

            // Limpa a primeira linha (agora vazia)
            for (int j = 0; j < COLS; j++)
            {
                board[0][j] = 0;
            }

            // Como movemos as linhas para baixo, não precisamos verificar a linha removida novamente
            i++; // Reanalisa a linha atual, pois ela pode ter se tornado completa após o deslocamento
        }
    }
    if (linhas_removidas > 0)
    {
        atualizar_pontuacao(linhas_removidas);

#ifdef DEBUG
        printf("Pontuação: %d   Nível: %d\n", pontuacao, nivel);
#endif
    }
}

/**
 * @brief Atualiza a gravidade do jogo verificando se o tempo acumulado já atingiu o limite.
 *
 * Esta função incrementa um contador de tempo em milissegundos. Quando o tempo acumulado
 * ultrapassa o intervalo definido (TEMPO_BASE / multiplicador_tempo), a peça é movida para baixo.
 * Se a peça não puder mais descer, ela é fixada no tabuleiro, linhas completas são removidas,
 * e uma nova peça é gerada. O contador de tempo é então reiniciado.
 *
 * @param linha      Ponteiro para a posição vertical da peça no tabuleiro.
 * @param coluna     Ponteiro para a posição horizontal da peça no tabuleiro.
 * @param peca       Ponteiro para a estrutura da peça atual.
 * @param peca_atual Ponteiro para o índice da peça atual.
 */
void update_game(int *linha, int *coluna, PecaTetris *peca, int *peca_atual)
{

    incrementTime();

    // Se o tempo acumulado atingir o limiar, move a peça para baixo
    if (timer_counter >= TEMPO_BASE / multiplicador_tempo)
    {

        if (check_piece_at_bottom(linha, coluna, *peca) == 1)
        {
            fix_piece(linha, coluna, *peca);
            remove_full_lines();
            generate_next_piece(linha, coluna, peca, peca_atual);
        }
        else
        {
            move_piece_down(linha, coluna, peca, peca_atual);
        }

        timer_counter = 0; // Reinicia o contador
    }

    //draw_board();
}

/**
 * @brief Incrementa o contador de tempo do jogo.
 *
 * Esta função é chamada a cada milissegundo para atualizar o contador
 * responsável por controlar a gravidade do jogo.
 */
void incrementTime()
{
    // Chamada de 1 ms aqui
    timer_counter++;
}

/**
 * @date        2025-03-08
 * @author      Andrey Hiemer
 * @brief       Verifica se o jogo acabou.
 *
 * A função percorre a linha superior do tabuleiro (linha 0) e verifica se há qualquer
 * célula ocupada (valor 2). Se encontrar, significa que não há espaço para uma nova peça,
 * e o jogo deve terminar.
 *
 * @return      Retorna 1 se o jogo acabou (fim de jogo), ou 0 caso contrário.
 */
int game_over()
{
    for (int j = 0; j < COLS; j++)
    {
        if (board[0][j] == 2)
        {
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Atualiza a pontuação com base no número de linhas removidas simultaneamente.
 *
 * Utiliza a fórmula tradicional:
 *   - 1 linha: 40 * (nivel+1)
 *   - 2 linhas: 100 * (nivel+1)
 *   - 3 linhas: 300 * (nivel+1)
 *   - 4 linhas: 1200 * (nivel+1)
 *
 * @param linhas_removidas Número de linhas removidas de uma vez.
 */
void atualizar_pontuacao(int linhas_removidas)
{
    int pontos = 0;
    switch (linhas_removidas)
    {
    case 1:
        pontos = 40 * (nivel + 1);
        break;
    case 2:
        pontos = 100 * (nivel + 1);
        break;
    case 3:
        pontos = 300 * (nivel + 1);
        break;
    case 4:
        pontos = 1200 * (nivel + 1);
        break;
    default:
        break;
    }
    pontuacao += pontos;
    linhas_totais += linhas_removidas;

    // Atualiza o nível se atingir o limite
    if (linhas_totais >= LINHAS_POR_NIVEL)
    {
        nivel++;
        linhas_totais = linhas_totais - LINHAS_POR_NIVEL; // Ou zere e acumule com pontos extras se desejar
        // Ajuste a velocidade do jogo, por exemplo:
        multiplicador_tempo++; // Ou reduza o tempo base
        //printf("\nNível aumentado! Agora é o nível %d\n", nivel);
    }
}

/**
 * @brief Exibe a próxima peça que aparecerá no jogo.
 *
 * Esta função imprime no console a matriz 4x4 da próxima peça
 * que será utilizada no jogo. A peça é representada com '█'
 * para blocos preenchidos e '.' para espaços vazios.
 */
void show_next_peace()
{
    printf("Proxima peca a aparecer\n");
    for (int i = 0; i < 4; i++) // responsavel pela peca sentido linha
    {
        for (int j = 0; j < 4; j++) // responsavel pela peca sentido coluna
        {
            if (next_peace.shape[i][j] == 1)
            {

                printf("█ "); // Bloco preenchido
            }
            else if (board[i][j] == 0)
            {
                printf(". "); // Espaço vazio
            }
        }
        printf("\n");
    }
}


/**
 * @brief Retorna a pontuação atual do jogo.
 *
 * Esta função retorna a pontuação acumulada pelo jogador durante o jogo.
 *
 * @return A pontuação atual como um valor de 16 bits sem sinal.
 */
uint16_t get_pontuacao(void)
{
    return (uint16_t)pontuacao;
}

void clear_pontuacao(void){
    pontuacao = 0;
    nivel = 0;
    linhas_totais = 0;
    multiplicador_tempo = 1; // Reseta o multiplicador de tempo
    timer_counter = 0; // Reseta o contador de tempo
}