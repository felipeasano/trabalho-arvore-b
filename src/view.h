#ifndef VIEW_H
#define VIEW_H

#include <stdio.h>
#include <string.h>
#include "arvore.h"

// Realiza a impressão do menu na tela
// Pré-condição: nenhuma
// Pós-condição: menu impresso na tela
void imprime_menu();

// Imprime os dados de um produto na tela
// Pré-condição: Ponteiro válido para a estrutura de produto
// Pós-condição: Dados do produto impressos na tela
void imprime_produto(PRODUTO* produto);

// Cria um novo produto com base nas informações fornecidas pelo usuário
// Pré-condição: nenhuma
// Pós-condição: Retorna uma estrutura de produto preenchida com os dados fornecidos
PRODUTO cria_novo_produto();

// Insere um novo produto nos arquivos de índices e dados
// Pré-condição: Ponteiro válido para a estrutura de produto, ponteiros válidos para os arquivos de índices e dados
// Pós-condição: O produto é inserido nos arquivos de índices e dados
void insere_produto(PRODUTO *p, ARQ_BIN* arq_indices, ARQ_BIN* arq_dados);

// Realiza a busca por um produto nos arquivos de índices e dados
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados
// Pós-condição: Os dados do produto são exibidos na tela, se encontrado
void busca_produto(ARQ_BIN* arq_index, ARQ_BIN* arq_dados);

// Inclui um lote de produtos a partir de um arquivo
// Pré-condição: Ponteiro válido para o arquivo, ponteiros válidos para os arquivos de índices e dados
// Pós-condição: Os produtos do lote são inseridos nos arquivos de índices e dados
void incluiLote(FILE* fr, ARQ_BIN* arq_indices, ARQ_BIN* arq_dados);

// Carrega o caminho dos arquivos de índices e dados
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados
// Pós-condição: O caminho dos arquivos é carregado
void loadPath(ARQ_BIN* arq_indices, ARQ_BIN* arq_dados);

// Atualiza os dados de um produto nos arquivos de índices e dados
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados, opção de atualização
// Pós-condição: Os dados do produto são atualizados nos arquivos de índices e dados
void atualizar_produto(ARQ_BIN* arq_index, ARQ_BIN* arq_dados, int op);

// Atualiza os dados de um produto em lote nos arquivos de índices e dados
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados, código do produto, valores auxiliares e opção de atualização
// Pós-condição: Os dados do produto são atualizados nos arquivos de índices e dados
void atualizar_produto_lote(ARQ_BIN* arq_index, ARQ_BIN* arq_dados, int cod, int aux1, char* aux2, int op);

// Realiza a impressão dos produtos em ordem crescente de código
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados, posição inicial
// Pós-condição: Os produtos são impressos na tela em ordem crescente de código
void in_ordem(ARQ_BIN* arq_index, ARQ_BIN* arq_dados, int pos);

// Lista todos os produtos presentes nos arquivos de índices e dados
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados
// Pós-condição: Os produtos são listados na tela
void listar_produtos(ARQ_BIN* arq_index, ARQ_BIN* arq_dados);

// Imprime as posições livres no arquivo de índices
// Pré-condição: Ponteiro válido para o arquivo de índices
// Pós-condição: As posições livres são impressas na tela
void imprime_livre_index(ARQ_BIN* arq);

// Imprime as posições livres no arquivo de dados
// Pré-condição: Ponteiro válido para o arquivo de dados
// Pós-condição: As posições livres são impressas na tela
void imprime_livre_dados(ARQ_BIN* arq);

// Função para gerenciar a remoção de um produto
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados, código do produto
// Pós-condição: O produto é removido dos arquivos de índices e dados
void GerenciaRemocao(ARQ_BIN *arq_index, ARQ_BIN *arq_dados, int codigo);

#endif