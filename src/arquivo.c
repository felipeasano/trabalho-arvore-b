#ifndef ARQUIVO_C
#define ARQUIVO_C

#include "arquivo.h"


// grava o cabecalho no arquivo
// Pré-condição: arquivo bin aberto
// Pós-condição: cabecalho gravado no arquivo bin
void grava_cabecalho(ARQ_BIN* arq){
    fseek(arq->f, 0, SEEK_SET);
    fwrite(&arq->cab, sizeof(CABECALHO), 1, arq->f);
}

// pre-condicao: nenhuma
// pos-condicao: arquivo aberto
// Entrada: Entra com nome do arquivo e a estrutura para arquivo .bin
// Retorno: devolve a estrutura com o arquivo aberto e o cabecalho lido, ou settado
void abre_arq_bin(char nome_arquivo[], ARQ_BIN *b, int tam_bloco){
    b->f = fopen(nome_arquivo, "r+b");
    b->tam_bloco = tam_bloco;
    if(b->f == NULL){
        //printf("Novo banco aberto!\n");
        b->f = fopen(nome_arquivo, "w+b");
        b->cab.livre = -1;
        b->cab.raiz = -1;
        b->cab.topo = 0;
        grava_cabecalho(b);
    }else{
        //printf("Banco aberto!\n");
        fseek(b->f, 0, SEEK_SET);
        fread(&b->cab, sizeof(b->cab), 1, b->f);
    }
}

// Atualiza o cabecalho e retorna a posicao do bloco
// Pré-condição: Arquivo binario aberto e cabecalho existente
// Pós-condição: cabecalho atualizado e bloco alocado (pos)
void fecha_arq_bin(ARQ_BIN *b){
    fclose(b->f);
}

// Atualiza o cabecalho e retorna a posicao do bloco
// Pré-condição: Arquivo binario aberto e cabecalho existente
// Pós-condição: cabecalho atualizado e bloco alocado (pos)
void set_pos(ARQ_BIN* arq, int pos){
    fseek(arq->f, sizeof(CABECALHO) + pos * arq->tam_bloco, SEEK_SET);
}

// Lê o produto do arquivo de dados na posição fornecida
// Pré-condição: Ponteiro para manipulador de dados valido
// Pós-condição: Retorna produto lido na posição
void ler_bloco(ARQ_BIN* arq, int pos, void *p) {
    set_pos(arq, pos);
    fread(p, arq->tam_bloco, 1, arq->f);
}

// Escreve o produto fornecido no arquivo de dados na posição fornecida
// Pré-condição: Ponteiro para manipulador de dados, produto valida
// Pós-condição: produto salvo no arquivo de dados
void grava_bloco(ARQ_BIN* arq, void *p, int pos) {
    set_pos(arq, pos);
    fwrite(p, arq->tam_bloco, 1, arq->f);
}

// Atualiza o cabecalho e retorna a posicao do bloco
// Pré-condição: Arquivo binario aberto e cabecalho existente
// Pós-condição: cabecalho atualizado e bloco alocado (pos)
int aloca_bloco(ARQ_BIN* arq){
    int pos;
    if(arq->cab.livre == -1){
        pos = arq->cab.topo;
        arq->cab.topo++;
        grava_cabecalho(arq);
        return pos;
    }
    pos = arq->cab.livre;
    set_pos(arq, pos);
    fread(&arq->cab.livre, sizeof(int), 1, arq->f);
    grava_cabecalho(arq);
    return pos;
}

// Atualiza pos livre do cabecalho
// Pré-condição: Arquivo binario aberto, cabecalho existente e posicao existente
// Pós-condição: cabecalho (pos livre) atualizado
void libera_bloco(ARQ_BIN* arq, int pos){

    set_pos(arq, pos);
    fwrite(&arq->cab.livre, sizeof(int), 1, arq->f);
    arq->cab.livre = pos;
    grava_cabecalho(arq);
}

#endif