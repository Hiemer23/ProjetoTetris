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

typedef enum {
    MENU_TELA1,
    MENU_TELA2,
    MENU_TELA3,
    MENU_TELA4,
    TELA_TESTE,
    SUB_MENU1,
    SUB_MENU2,
    SUB_MENU3,
    SUB_MENU4,
    MENU_MAX
} EstadoMenu;

typedef enum {
    MODO_NAVEGANDO,   // apenas se move pelo menu
    MODO_EXECUTANDO   // entrou em uma tela ou função
} ModoMenu;

// Prototipos
void lcd_Task(void);
void changeLCDScreen(EstadoMenu novaTela);
void initLCD(void);
void updateDataEEPROMLCDMenu2(void);
void updateDataEEPROMLCDMenu3(void);
void updateDataEEPROMLCDMenu4(void);
void inserir_letra_nome(char nova_letra);
void atualizar_nome_em_letrasLinha2(void);
void changeName(void);

extern uint8_t positionYSubMenu3;
extern uint8_t positionXSubMenu3;
extern char letrasLinha1[17];
extern char letrasLinha2[17];
extern char nomeDigitado[4];
#endif /* INC_LCD_MANAGER_H_ */
