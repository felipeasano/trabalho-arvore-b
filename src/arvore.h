#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"

#define ORDEM 7

typedef struct no{
    int numChaves;
    int chaves[ORDEM];
    int filhos[ORDEM+1];
    int registro[ORDEM];
}NO;

typedef struct produto{
    int cod;
    char nome[50];
    char marca[30];
    char categoria[50];
    int estoque;
    char preco[10];
}PRODUTO;

typedef struct no_fila{
    int pos;
    struct no_fila* prox;
}NO_FILA;

typedef struct fila{
    NO_FILA* inicio;
    NO_FILA* fim;
}FILA;

// Veritica se o nó fornecido é folha
// Pré-condição: Ponteiro para manipulador de indices válido
// Pós-condição: Nenhuma
int eh_folha(NO* no);

// Verifica se o nó fornecido esta em overflow
// Pré-condição: Ponteiro para nó válido
// Pós-condição: Nenhuma
int eh_overflow(NO* no);

// Verifica se o nó fornecido esta em underflow
// Pré-condição: Ponteiro para nó válido
// Pós-condição: Nenhuma
int eh_underflow(NO* no);

void imprime_por_niveis(ARQ_BIN* arq_index);

NO* cria_no();

int retorna_livre(ARQ_BIN* arq_index);

int split(ARQ_BIN* arq_index, int posX, int *m, int *m_ptDado);

int buscaPos(NO* r, int info, int * pos);

void adiciona_direita(NO* r, int pos_inserido, int chave, int ptdado, int pos_novo_no);

int insere_aux(ARQ_BIN* arq_index, int pos_arquivo, int chave, int ptdado);

int insere(ARQ_BIN* arq_index, int chave, int ptdado);

int busca(ARQ_BIN* arq_index, int pos_arq, int cod, int *pos);

//void remover(ARQ_BIN* arq_index, int info);

#endif