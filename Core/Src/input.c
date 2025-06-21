/*
 * input.c
 *
 *  Created on: Jun 21, 2025
 *      Author: andrey
 */

#include "input.h"

uint16_t AD1, AD2, BotaoStatus;
static ADC_HandleTypeDef hadc1;
uint8_t upAndDown_locked,
    rightAndLeft_locked = 0,
    cima,
    direita,
    baixo,
    esquerda,
    botaoEvento = 0;

// Prototipos
void atualizaNavegacaoUpandDown(void);
void resetCimaBaixo(void);

void initInput(ADC_HandleTypeDef *hadc)
{
    hadc1 = *hadc; // Copia o handle do ADC
}

uint16_t ler_ADC_canal(uint8_t canal)
{
    ADC_ChannelConfTypeDef sConfig = {0};

    sConfig.Channel = (canal == 0 ? (uint32_t)0 : (uint32_t)1);
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;

    HAL_ADC_ConfigChannel(&hadc1, &sConfig); // Aponta o canal

    HAL_ADC_Start(&hadc1);                            // Inicia conversão
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY); // Espera terminar
    uint16_t valor = HAL_ADC_GetValue(&hadc1);        // Lê resultado

    return valor;
}

void taskLeituraAD(void)
{
    AD1 = ler_ADC_canal(0); // Lê ADC canal 0
    AD2 = ler_ADC_canal(1); // Lê ADC canal 1

    BotaoStatus = HAL_GPIO_ReadPin(BOTAO_GPIO_Port, BOTAO_Pin); // Lê estado do botão

    atualizaNavegacaoUpandDown();
    atualizaBotao();
    atualizaNavegacaoEsquerdaDireita();
}

void atualizaNavegacaoUpandDown(void)
{
    if (!upAndDown_locked)
    {
        if (AD2 < AD2_THRESHOLD_LOW)
        {
            // Desce no menu
            baixo = TRUE;
            upAndDown_locked = 1;
        }
        else if (AD2 > AD2_THRESHOLD_HIGH)
        {
            // Sobe no menu
            cima = TRUE;
            upAndDown_locked = 1;
        }
    }
    else
    {
        // Desbloqueia se estiver na zona morta
        if (AD2 > AD2_DEADZONE_MIN && AD2 < AD2_DEADZONE_MAX)
        {
            upAndDown_locked = 0;
            resetCimaBaixo();
        }
    }
}
void atualizaNavegacaoEsquerdaDireita(void)
{
    if (!rightAndLeft_locked)
    {
        if (AD1 < AD2_THRESHOLD_LOW)
        {
            esquerda = TRUE; // Movimento para a esquerda
            rightAndLeft_locked = 1;
        }
        else if (AD1 > AD2_THRESHOLD_HIGH)
        {
            direita = TRUE; // Movimento para a direita
            rightAndLeft_locked = 1;
        }
    }
    else
    {
        // Desbloqueia se estiver na zona morta
        if (AD1 > AD2_DEADZONE_MIN && AD1 < AD2_DEADZONE_MAX)
        {
            rightAndLeft_locked = 0;
            resetDireitaEsquerda();
        }
    }
}

void atualizaBotao(void)
{
    static uint8_t uinflagBotaoApertado = 0;
    if (BotaoStatus == GPIO_PIN_RESET && botaoEvento == 0)
    {
        uinflagBotaoApertado = 1; // Marca que o evento já ocorreu
    }
    if(uinflagBotaoApertado && BotaoStatus == GPIO_PIN_SET)
    {
        botaoEvento = 1; // Marca o evento do botão
        uinflagBotaoApertado = 0; // Reseta a flag
    }
}

uint8_t getCima(void)
{
    return cima;
}
uint8_t getBaixo(void)
{
    return baixo;
}
void resetCimaBaixo(void)
{
    cima = 0;
    baixo = 0;
}
uint8_t getDireita(void)
{
    return direita;
}
uint8_t getEsquerda(void)
{
    return esquerda;
}
uint8_t getBotaoEvento(void)
{
    return botaoEvento;
}

void resetDireitaEsquerda(void)
{
    direita = 0;
    esquerda = 0;
}

void resetBotaoEvento(void)
{
    botaoEvento = 0; // Reseta o evento do botão
}