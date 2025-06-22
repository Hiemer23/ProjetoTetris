/*
 * EEPROM.c
 *
 *  Created on: Jun 22, 2025
 *      Author: andrey
 */

#include "main.h"
SaveData dados;

// Prototipos
void ler_da_flash(SaveData *data);
void salvar_na_flash(const SaveData *data);

void salvar_na_flash(const SaveData *data)
{
    HAL_FLASH_Unlock();

    // Apaga a página onde os dados estão
    FLASH_EraseInitTypeDef erase;
    uint32_t PageError;

    erase.TypeErase = FLASH_TYPEERASE_PAGES;
    erase.PageAddress = FLASH_SAVE_ADDR;
    erase.NbPages = 1;

    HAL_FLASHEx_Erase(&erase, &PageError);

    // Grava os dados (palavra por palavra)
    const uint16_t *p = (const uint16_t *)data;
    for (uint32_t i = 0; i < (sizeof(SaveData) + 1) / 2; i++)
    {
        HAL_FLASH_Program(FLASH_TYPEPROGRAM_HALFWORD, FLASH_SAVE_ADDR + (i * 2), p[i]);
    }

    HAL_FLASH_Lock();
}

void ler_da_flash(SaveData *data)
{
    memcpy(data, (void *)FLASH_SAVE_ADDR, sizeof(SaveData));
}

void inicializarEEPROM(void)
{
    ler_da_flash(&dados);

    // Se memória não inicializada, setar valores padrão
    if (dados.nomeRecorde[0] == 0xFF || dados.pontuacaoRecorde == 0xFFFF)
    {
        strcpy(dados.nomeAtual, "___");
        strcpy(dados.nomeRecorde, "___");
        dados.pontuacaoRecorde = 0;
        salvar_na_flash(&dados);
    }
}

void atualizarNomeAtual(const char *novoNome)
{
    memcpy(dados.nomeAtual, novoNome, 3);
    salvar_na_flash(&dados);
}

void tentarSalvarRecorde(uint16_t novaPontuacao)
{
    ler_da_flash(&dados);
    if (novaPontuacao > dados.pontuacaoRecorde)
    {
        dados.pontuacaoRecorde = novaPontuacao;
        memcpy(dados.nomeRecorde, dados.nomeAtual, 3);
        salvar_na_flash(&dados);
    }
}

uint16_t get_pontuacao_EEPROM(void)
{
    ler_da_flash(&dados);
    return dados.pontuacaoRecorde;
}

void get_nome_recorde(char *nome)
{
    ler_da_flash(&dados);
    memcpy(nome, dados.nomeRecorde, 3);
}