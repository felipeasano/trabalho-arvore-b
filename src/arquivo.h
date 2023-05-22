#ifndef ARQUIVO_H
#define ARQUIVO_H

#include <stdio.h>

typedef struct cab{
    int raiz;
    int livre;
    int topo;
}CABECALHO;

typedef struct arq{
    FILE *f;
    CABECALHO cab;
    int tam_bloco;
}ARQ_BIN;

// pre-condicao: nenhuma
// pos-condicao: nenhuma
// Entrada: Entra com nome do arquivo e a estrutura para arquivo .bin
// Retorno: devolve a estrutura com o arquivo aberto e o cabecalho lido, ou settado
void abre_arq_bin(char nome_arquivo[], ARQ_BIN *b, int tam_bloco);

void fecha_arq_bin(ARQ_BIN *b);

// Lê o produto do arquivo de dados na posição fornecida
// Pré-condição: Ponteiro para manipulador de dados valido
// Pós-condição: Retorna produto lido na posição
void ler_bloco(ARQ_BIN* arq, int pos, void *p) ;

// Escreve o produto fornecido no arquivo de dados na posição fornecida
// Pré-condição: Ponteiro para manipulador de dados, produto valida
// Pós-condição: produto salvo no arquivo de dados
void grava_bloco(ARQ_BIN* arq, void *p, int pos) ;

int aloca_bloco(ARQ_BIN* arq);

void libera_bloco(ARQ_BIN* arq, int pos);
#endif