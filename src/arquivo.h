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

// grava o cabecalho no arquivo
// Pré-condição: arquivo bin aberto
// Pós-condição: cabecalho gravado no arquivo bin
void grava_cabecalho(ARQ_BIN* arq);

// pre-condicao: nenhuma
// pos-condicao: arquivo aberto
// Entrada: Entra com nome do arquivo e a estrutura para arquivo .bin
// Retorno: devolve a estrutura com o arquivo aberto e o cabecalho lido, ou settado
void abre_arq_bin(char nome_arquivo[], ARQ_BIN *b, int tam_bloco);

// Fecha o arquivo binario
// Pré-condição: arquivo bin aberto
// Pós-condição: arquivo bin fechado
void fecha_arq_bin(ARQ_BIN *b);

// Lê o produto do arquivo de dados na posição fornecida
// Pré-condição: Ponteiro para manipulador de dados valido
// Pós-condição: Retorna produto lido na posição
void ler_bloco(ARQ_BIN* arq, int pos, void *p) ;

// Escreve o produto fornecido no arquivo de dados na posição fornecida
// Pré-condição: Ponteiro para manipulador de dados, produto valida
// Pós-condição: produto salvo no arquivo de dados
void grava_bloco(ARQ_BIN* arq, void *p, int pos) ;

// Atualiza o cabecalho e retorna a posicao do bloco
// Pré-condição: Arquivo binario aberto e cabecalho existente
// Pós-condição: cabecalho atualizado e bloco alocado (pos)
int aloca_bloco(ARQ_BIN* arq);

// Atualiza pos livre do cabecalho
// Pré-condição: Arquivo binario aberto, cabecalho existente e posicao existente
// Pós-condição: cabecalho (pos livre) atualizado
void libera_bloco(ARQ_BIN* arq, int pos);
#endif