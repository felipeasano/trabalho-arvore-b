#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include <string.h>
#include "arvore.h"

void imprime_menu();

void imprime_produto(PRODUTO* produto);

void imprime_no(NO* no);

PRODUTO cria_novo_produto();

void insere_produto(PRODUTO *p, ARQ_BIN* arq_indices, ARQ_BIN* arq_dados);

void incluiLote(FILE *fr);

void loadPath();

#endif