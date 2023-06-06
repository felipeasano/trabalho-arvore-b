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

// Verifica se o nó fornecido é folha
// Pré-condição: Ponteiro para manipulador de índices válido
// Pós-condição: Retorna 1 se o nó é folha, caso contrário retorna 0
int eh_folha(NO* no);

// Verifica se o nó fornecido está em overflow
// Pré-condição: Ponteiro para nó válido
// Pós-condição: Retorna 1 se o nó está em overflow, caso contrário retorna 0
int eh_overflow(NO* no);

// Verifica se o nó fornecido está em underflow
// Pré-condição: Ponteiro para nó válido
// Pós-condição: Retorna 1 se o nó está em underflow, caso contrário retorna 0
int eh_underflow(NO* no);

// Imprime um nó da árvore
// Pré-condição: Ponteiro para nó válido
// Pós-condição: Nenhuma
void imprime_noB(NO* no);

// Imprime a árvore por níveis
// Pré-condição: Arquivo de índices aberto e contendo pelo menos o cabeçalho gravado
// Pós-condição: Impressão da árvore por níveis
void imprime_por_niveis(ARQ_BIN* arq_index);

// Retorna a posição livre onde o novo dado deve ser inserido na árvore
// Pré-condição: Ponteiro para arquivo de índices válido
// Pós-condição: Retorna a posição livre onde o novo dado deve ser inserido
int retorna_livre(ARQ_BIN* arq_index);

// Realiza o split do nó na posição posX e salva o novo nó na posição posY
// Pré-condição: Ponteiro para arquivo de índices válido, posição do nó a ser splitado,
// ponteiros para as variáveis que armazenarão o elemento do meio e seu ponteiro de dado
// Pós-condição: Retorna a posição do novo nó criado (posY), além do elemento do meio do nó onde ocorreu o split (m e m_ptDado)
int split(ARQ_BIN* arq_index, int posX, int *m, int *m_ptDado);

// Realiza uma busca na árvore para encontrar a posição de um dado específico
// Pré-condição: Ponteiro para nó válido, informação a ser buscada, ponteiro para a variável que armazenará a posição encontrada
// Pós-condição: Retorna 1 se a informação foi encontrada, caso contrário retorna 0 e atualiza a posição
int buscaPos(NO* r, int info, int * pos);

// Adiciona um novo elemento à direita do nó na posição pos_inserido
// Pré-condição: Ponteiro para nó válido, posição de inserção, chave, ponteiro de dado e posição do novo nó
// Pós-condição: Nenhuma
void adiciona_direita(NO* r, int pos_inserido, int chave, int ptdado, int pos_novo_no);

// Função auxiliar para inserção na árvore
// Pré-condição: Ponteiro para arquivo de índices válido, posição do arquivo onde ocorrerá a inserção,
// chave e ponteiro de dado a serem inseridos
// Pós-condição: Retorna a posição onde a inserção foi realizada
int insere_aux(ARQ_BIN* arq_index, int pos_arquivo, int chave, int ptdado);

// Insere um novo elemento na árvore
// Pré-condição: Ponteiro para arquivo de índices válido, chave e ponteiro de dado a serem inseridos
// Pós-condição: Retorna a posição onde a inserção foi realizada
int insere(ARQ_BIN* arq_index, int chave, int ptdado);

// Realiza uma busca na árvore para encontrar a posição de um dado específico
// Pré-condição: Ponteiro para arquivo de índices válido, posição do arquivo onde inicia a busca,
// código a ser buscado, ponteiro para a variável que armazenará a posição encontrada
// Pós-condição: Retorna 1 se o código foi encontrado, caso contrário retorna 0 e atualiza a posição
int busca(ARQ_BIN* arq_index, int pos_arq, int cod, int *pos);

//pré-requisitos: Recebe um ponteiro para um arquivo aberto de uma árvoreB que contém ao menos o
//cabeçalho de indices gravado
//pós-requisitos: Info será removido da arvoreB
void remover(ARQ_BIN* arq_index, int info);


#endif