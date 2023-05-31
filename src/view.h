#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include <string.h>
#include "arvore.h"

void imprime_menu();

void imprime_produto(PRODUTO* produto);

PRODUTO cria_novo_produto();

void insere_produto(PRODUTO *p, ARQ_BIN* arq_indices, ARQ_BIN* arq_dados);

void busca_produto(ARQ_BIN* arq_index, ARQ_BIN* arq_dados);

void incluiLote(FILE *fr, ARQ_BIN* arq_indices, ARQ_BIN* arq_dados);

void loadPath(ARQ_BIN* arq_indices, ARQ_BIN* arq_dados);

void atualizar_produto(ARQ_BIN* arq_index, ARQ_BIN* arq_dados, int op);

void in_ordem(ARQ_BIN* arq_index, ARQ_BIN* arq_dados, int pos);

void listar_produtos(ARQ_BIN* arq_index, ARQ_BIN* arq_dados);

#endif