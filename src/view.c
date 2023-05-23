#ifndef VIEW_C
#define VIEW_C

#include "view.h"

void imprime_menu(){
    printf("\n\tMenu de Opcoes:\n\n");
    printf("1.  Cadastrar produto\n");
    printf("2.  Remover produto\n");
    printf("3.  Atualizar preco\n");
    printf("4.  Atualizar estoque\n");
    printf("5.  Imprimir informacoes de um produto\n");
    printf("6.  Imprimir lista de todos os produtos\n");
    printf("7.  Imprimir arvore\n");
    printf("8.  Imprimir lista de livres do arquivo de indices\n");
    printf("9.  Imprimir lista de livres do arquivo de dados\n");
    printf("10. Realizar operacoes em lote\n");
    printf("0.  Sair\n\n");

    printf("Digite a opcao desejada: ");
}

void imprime_produto(PRODUTO* produto) {
    printf("\ncodigo: %d\n",produto->cod );
    printf("Nome: %s\n", produto->nome);
    printf("Marca: %s\n", produto->marca);
    printf("Categoria: %s\n", produto->categoria);
    printf("Estoque: %d\n", produto->estoque);
    printf("Preco: %s\n", produto->preco);
    printf("Livre: %d\n", produto->livre);
}

void imprime_no(NO* no){
    printf("[ ");
    for (int i = 0; i < no->numChaves; i++) {
        printf("%d ", no->chaves[i]);
    }
    printf("] ");
}

#endif