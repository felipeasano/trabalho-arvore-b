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

NO* cria_no();

// Função recursiva para encontrar a referencia da chave passada
// Pré-condição: Ponteiro para manipulador de arvore
// Pós-condição: Retorna o numero da referencia da chave caso seja encontrada,
// caso contrario, -1 é retornado
static int busca_aux(ARQ_BIN* arq_index, int filePos, int key, int *pos);

// Procura a referencia da chave fornecida na arvore B
// Pré-condição: Ponteiro para manipulador de arvore válido
// Pós-condição: Retorna a referencia da chave, caso não seja encontrada,
// -1 é retornado
int busca(ARQ_BIN* arq_index, int key);

// Busca a posicao em que a chave esta ou estaria no nó
// Pré-condição: Ponteiro para nó valido
// Pós-condição: Retorna 1 caso chave esteja no nó e 0 caso contrario
int busca_pos_chave(NO *no, int chave, int *pos);

// Adiciona a chave e referencia posição fornecida no nó fornecido, adicionando
// o filho fornecio a direita
// Pré-condição: Ponteiro para nó valido
// Pós-condição: Nó modificado
void addToRight(NO *no, int pos, int chave, int registro, int rightChild);

// Adiciona a chave e referencia posição fornecida no nó fornecido, adicionando
// o filho fornecio a esquerda
// Pré-condição: Ponteiro para nó valido
// Pós-condição: Nó modificado
void addToLeft(NO *no, int pos, int chave, int registro, int leftChild);

// Adiciona novo nó ao arquivo de indices, caso nenhuma posiçao livre exista
// o nó é adicionado no topo do arquivo, caso contrario a posicao livre é utilizada
// Pré-condição: Ponteiro para manipulador de indices valido e ponteiro para nó
// Pós-condição: Retorna a posição do nó no arquivo de indices
int add_no(ARQ_BIN* arq_index, NO *no);

NO* split(NO* over_no, int *chave_med, int *registro_med);

// Função recursiva para inserir chave na arvore B, busca a posicao de insercao e
// corrige nós em overflow
// Pré-condição: Ponteiro para manipulador de arvore válido
// Pós-condição: Retorna o nó da posição fornecida com as modificações necessárias
NO* insere_aux(ARQ_BIN* arq_index, int pos_no, int chave, int registro);

// Insere uma chave e uma referencia na arvore B realizando as devidas
// correçoes caso o nó fiquem em overflow
// Pré-condição: Ponteiro para manipulador de arvore válido
// Pós-condição: Chave e referencia adicionadas
void insere(ARQ_BIN* arq_index, int cod, int registro);


#endif