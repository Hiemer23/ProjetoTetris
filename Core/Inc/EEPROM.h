/*
 * EEPROM.h
 *
 *  Created on: Jun 22, 2025
 *      Author: andrey
 */

#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_

#define FLASH_SAVE_ADDR ((uint32_t)0x0800FC00)

typedef struct
{
    char nomeAtual[3];
    char nomeRecorde[3];
    uint16_t pontuacaoRecorde;
} SaveData;

// Funções
void inicializarEEPROM(void);
void atualizarNomeAtual(const char *novoNome);
void tentarSalvarRecorde(uint16_t novaPontuacao);
uint16_t get_pontuacao_EEPROM(void);
void get_nome_recorde(char *nome);

// Apenas para teste externalizar o SaveData dados
extern SaveData dados;
void salvar_na_flash(const SaveData *data);

#endif /* INC_EEPROM_H_ */
