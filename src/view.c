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
}

PRODUTO cria_novo_produto(){
    PRODUTO p;
    printf("Insira os dados do Produto:\n");
    printf("Codigo: ");
    scanf("%d%*c", &p.cod);
    printf("Nome: ");
    fgets(p.nome, 50, stdin);
    p.nome[strcspn(p.nome,"\n")] = '\0';
    printf("Marca: ");
    fgets(p.marca, 30, stdin);
    p.marca[strcspn(p.marca,"\n")] = '\0';
    printf("Categoria: ");
    fgets(p.categoria, 50, stdin);
    p.categoria[strcspn(p.categoria,"\n")] = '\0';
    printf("Estoque: ");
    scanf("%d%*c", &p.estoque);
    printf("Preco: ");
    fgets(p.preco, 10, stdin);
    p.preco[strcspn(p.preco,"\n")] = '\0';
    return p;
}

void insere_produto(PRODUTO *p, ARQ_BIN* arq_indices, ARQ_BIN* arq_dados){

    int pos_inserir = aloca_bloco(arq_dados);
    if(insere(arq_indices, p->cod, pos_inserir)){
        grava_bloco(arq_dados, p, arq_dados->cab.topo);
        if(pos_inserir == arq_dados->cab.topo){
            arq_dados->cab.topo++;
        }
        printf("Produto inserido com sucesso\n");
    }else{
        if(arq_dados->cab.livre != -1){
            arq_dados->cab.livre = pos_inserir;
        }
        printf("Codigo [%d] ja cadastrado\n");
    }
    grava_cabecalho(arq_dados);
}

//Realiza inclusoes em lote
//Pre-condicao: Arquivo txt com comandos e informacoes aberto
//Pos-condicao: Inclusoes, alteracoes e remocoes do arquivo efetuadas
void incluiLote(FILE *fr) {
    char text[300], *aux = NULL, *pt = NULL;
    PRODUTO *p = (PRODUTO *) malloc(sizeof(PRODUTO));
    while (fscanf(fr, "%[^\n]%*c", text) != EOF) {
        //FILE *f = openBin();
        char *token = strtok(text, ";"); // pega o tipo
        if (strcmp(token, "I") == 0) {
            p->cod = atoi(strtok(NULL, ";"));
            strcpy(p->nome, strtok(NULL, ";"));
            strcpy(p->marca, strtok(NULL, ";"));
            strcpy(p->categoria, strtok(NULL, ";"));
            p->estoque = atoi(strtok(NULL, ";"));
            strcpy(p->preco, strtok(NULL, ";"));
            /*PRODUTO *aux = buscaProduto(f, p->id);
            if (aux == NULL) {
                //insereProduto(p);
                printf("Produto com ID [%d] cadastrado!\n", p->cod);
            } else
                printf("ID [%d] ja existente! \n", p->cod);
            free(aux);*/
        }

        else if (strcmp(token, "R") == 0) {
            /*int info;
            info = atoi(strtok(NULL, ";"));
            removeProduto(info);*/
        }

        else if (strcmp(token, "A") == 0) {
            int info;
            char aux1[16] = "", aux2[16] = "", *ptr = text;
            ptr += 2;
            sscanf(ptr, "%d", &p->cod);
            ptr = &ptr[strcspn(ptr, ";") + 1];
            sscanf(ptr, "%[^;]", aux1);
            ptr = &ptr[strcspn(ptr, ";") + 1];
            sscanf(ptr, "%[^\n]", aux2);
            if (strcmp(aux1, "")) {
                //atualizaEstoque(p->id, atoi(aux1));
            }
            if (strcmp(aux2, "")) {
                for (ptr = aux2; *ptr != 0; ptr++)
                    if (*ptr == ',')
                        *ptr = '.';
                //atualizaPreco(p->id, atof(aux2));
            }
        }
        else {
            printf("Entrada não reconhecida! \n");
        }
    }
    free(p);
    fclose(fr);
}

//Le o caminho do arquivo passado por input, e cadastra os itens nele
//Pre-condicao: Um caminho para um arquivo existente
//Pos-condicao: Registro dos itens nos arquivos binarios
void loadPath(){
    FILE *fr;
    char path[50];
    do{
        printf("Nome do arquivo:");
        scanf("%s%*c", path);
        fr = fopen(path, "r");
    }
    while(fr == NULL);
    incluiLote(fr);
    printf("\n");
    fclose(fr);
}

#endif