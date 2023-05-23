#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include <string.h>
#include "arvore.h"

void imprime_menu();

void imprime_produto(PRODUTO* produto);

void imprime_no(NO* no);

PRODUTO cria_novo_produto();

#endif