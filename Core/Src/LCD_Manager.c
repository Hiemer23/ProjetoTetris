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

EstadoMenu MenuLCD = MENU_TELA1;
uint8_t PecasLCD[7] = {CUSTOMT, CUSTOMZ, CUSTOMI, CUSTOML, CUSTOMJ, CUSTOMS, CUSTOMO};

char linha[16];
char linha2[16];
char nomeRecorde[4];
uint16_t recordeAtual;

char letrasLinha1[17] = "ABCDEFGHIJKLMNOP";
char letrasLinha2[17] = "QRSTUVWXYZ 0 ___";
char nomeDigitado[4] = {'_', '_', '_', '\0'};
uint8_t positionYSubMenu3 = 0;
uint8_t positionXSubMenu3 = 0;

void lcd_Task(void)
{
    // 4 estados na máquina de estados

    switch (MenuLCD)
    {
    default:
        MenuLCD = MENU_TELA1;
    case MENU_TELA1:
        change_Message(0, ">>Start Game");
        change_Message(1, "Recorde Atual");
        break;
    case MENU_TELA2:
        change_Message(0, ">>Recorde Atual");
        change_Message(1, "Gravar Nome");
        break;
    case MENU_TELA3:
        change_Message(0, ">>Gravar Nome");
        change_Message(1, "Limpar Recorde");
        break;
    case MENU_TELA4:
        change_Message(0, ">>Limpar Recorde");
        change_Message(1, "Start Game");
        break;
    case TELA_TESTE:
        // char linhaTeste[16], linhaTestes2[16];                    // 16 caracteres + terminador '\0'
        //  sprintf(linhaTeste, "AD1: %4u", AD1);   // %4u → valor sem sinal com 4 dígitos (ajustável)
        //  change_Message(0, linhaTeste);

        // sprintf(linhaTestes2, "AD2:%4u Bot:%1u", AD2, BotaoStatus);   // %4u → valor sem sinal com 4 dígitos (ajustável)
        // change_Message(1, linhaTestes2);
        //        sprintf(linhaTeste, "Y:%4u        ", AD2);   // %4u → valor sem sinal com 4 dígitos (ajustável)
        //        change_Message(0, linhaTeste);
        //        snprintf(linhaTestes2, sizeof(linhaTestes2), "Cima:%u Baixo:%u ", getCima(), getBaixo());   // %4u → valor sem sinal com 4 dígitos (ajustável)
        //        change_Message(1, linhaTestes2);
        break;
    case SUB_MENU1:
        snprintf(linha, sizeof(linha), "Proxima Peca:  ");
        linha[15] = PecasLCD[get_next_piece()];
        change_Message(0, linha);
        sprintf(linha2, "Pont:%5u ", get_pontuacao()); // %4u → valor sem sinal com 4 dígitos (ajustável)
        change_Message(1, linha2);
        break;

    case SUB_MENU2:
        change_Message(0, linha);
        change_Message(1, linha2);
        break;
    case SUB_MENU3:
        change_Message(0, linha);
        change_Message(1, linha2);
        break;
    case SUB_MENU4:
        change_Message(0, linha);
        change_Message(1, linha2);
        break;
    }
}

void changeLCDScreen(EstadoMenu novaTela)
{
    // valide que novaTela é um estado valido antes de mudar
    if (novaTela >= MENU_TELA1 && novaTela < MENU_MAX)
    {
        MenuLCD = novaTela;
        estadoMenu = novaTela;
    }
    else
    {
        MenuLCD = MENU_TELA1; // Reset to default state if invalid
        estadoMenu = MENU_TELA1;
    }
}

void initLCD(void)
{
    initialize_LCD(); // Initialize the LCD
    lcd_create_char(1, pieceO);
    lcd_create_char(2, pieceL);
    lcd_create_char(3, pieceS);
    lcd_create_char(4, pieceZ);
    lcd_create_char(5, pieceT);
    lcd_create_char(6, pieceJ);
}

void updateDataEEPROMLCDMenu2(void)
{
    get_nome_recorde(nomeRecorde);              // Get the record name from EEPROM
    recordeAtual = get_pontuacao_EEPROM();      // Get the current record score
    sprintf(linha, "Nome: %s", nomeRecorde);    // %3s → string com 3 caracteres
    sprintf(linha2, "Pont:%5u ", recordeAtual); // %4u → valor sem sinal com 4 dígitos (ajustável)
}

void updateDataEEPROMLCDMenu3(void)
{
    // char nomeTeste[4] = "ARH";
    // memcpy(dados.nomeAtual, nomeTeste, 3);
    // salvar_na_flash(&dados);

    nomeDigitado[0] = '_';
    nomeDigitado[1] = '_';
    nomeDigitado[2] = '_';

    strcpy(linha, letrasLinha1);
    strcpy(linha2, letrasLinha2);
    lcd_cursor_on();
}

void updateDataEEPROMLCDMenu4(void)
{
    strcpy(dados.nomeRecorde, "___");
    dados.pontuacaoRecorde = 0;
    salvar_na_flash(&dados);
    sprintf(linha, "Nome: %s", dados.nomeRecorde);        // %3s → string com 3 caracteres
    sprintf(linha2, "Pont:%5u ", dados.pontuacaoRecorde); // %4u → valor sem sinal com 4 dígitos (ajustável)
}

void changeName(void)
{
    if (getCima() && positionYSubMenu3 > 0)
    {
        positionYSubMenu3--;
        resetCimaBaixo();
    }
    if (getBaixo() && positionYSubMenu3 < 1)
    {
        positionYSubMenu3++;
        resetCimaBaixo();
    }
    if (getEsquerda() && positionXSubMenu3 > 0)
    {
        positionXSubMenu3--;
    }
    if (getDireita() && positionXSubMenu3 < 15)
    {
        positionXSubMenu3++;
    }

    lcd_cursor_on();
}

void inserir_letra_nome(char nova_letra)
{
    // Desloca os caracteres à esquerda
    nomeDigitado[0] = nomeDigitado[1];
    nomeDigitado[1] = nomeDigitado[2];
    nomeDigitado[2] = nova_letra; // Insere na última posição
}

void atualizar_nome_em_letrasLinha2(void)
{
    linha2[13] = nomeDigitado[0];
    linha2[14] = nomeDigitado[1];
    linha2[15] = nomeDigitado[2];
}
