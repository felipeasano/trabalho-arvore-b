#ifndef VIEW_C
#define VIEW_C

#include "view.h"

// Realiza a impressão do menu na tela
// Pré-condição: nenhuma
// Pós-condição: menu impresso na tela
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


// Imprime os dados de um produto na tela
// Pré-condição: Ponteiro válido para a estrutura de produto
// Pós-condição: Dados do produto impressos na tela
void imprime_produto(PRODUTO* produto) {
    printf("\ncodigo: %d\n",produto->cod );
    printf("Nome: %s\n", produto->nome);
    printf("Marca: %s\n", produto->marca);
    printf("Categoria: %s\n", produto->categoria);
    printf("Estoque: %d\n", produto->estoque);
    printf("Preco: %s\n", produto->preco);
}


// Cria um novo produto com base nas informações fornecidas pelo usuário
// Pré-condição: nenhuma
// Pós-condição: Retorna uma estrutura de produto preenchida com os dados fornecidos
PRODUTO cria_novo_produto(){
    PRODUTO p;
    printf("Insira os dados do Produto:\n");
    printf("Codigo: ");
    scanf("%d%*c", &p.cod);
    printf("Nome: ");
    fgets(p.nome, 51, stdin);
    p.nome[strcspn(p.nome,"\n")] = '\0';
    printf("Marca: ");
    fgets(p.marca, 31, stdin);
    p.marca[strcspn(p.marca,"\n")] = '\0';
    printf("Categoria: ");
    fgets(p.categoria, 51, stdin);
    p.categoria[strcspn(p.categoria,"\n")] = '\0';
    printf("Estoque: ");
    scanf("%d%*c", &p.estoque);
    printf("Preco: ");
    fgets(p.preco, 10, stdin);
    p.preco[strcspn(p.preco,"\n")] = '\0';
    return p;
}


// Insere um novo produto nos arquivos de índices e dados
// Pré-condição: Ponteiro válido para a estrutura de produto, ponteiros válidos para os arquivos de índices e dados
// Pós-condição: O produto é inserido nos arquivos de índices e dados
void insere_produto(PRODUTO *p, ARQ_BIN* arq_indices, ARQ_BIN* arq_dados){

    int pos_inserir = aloca_bloco(arq_dados);
    if(insere(arq_indices, p->cod, pos_inserir)){
        grava_bloco(arq_dados, p, pos_inserir);
        if(pos_inserir == arq_dados->cab.topo){
            arq_dados->cab.topo++;
        }
        printf("Produto com ID [%d] inserido com sucesso\n", p->cod);
    }else{
        if(arq_dados->cab.livre != -1){
            arq_dados->cab.livre = pos_inserir;
        }
        printf("Codigo [%d] ja cadastrado\n", p->cod);
    }
    grava_cabecalho(arq_dados);
}

// Realiza a busca por um produto nos arquivos de índices e dados
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados
// Pós-condição: Os dados do produto são exibidos na tela, se encontrado
void busca_produto(ARQ_BIN* arq_index, ARQ_BIN* arq_dados){
    if(arq_index->cab.raiz == -1){
        printf("Nenhum produto cadastrado ainda...\n");
        return;
    }

    int pos, codigo;

    printf("Entre com o codigo do produto: ");
    scanf("%d%*c", &codigo);
    //printf("codigo: %d\n", codigo);
    int posicao_arvore = busca(arq_index, arq_index->cab.raiz, codigo, &pos);
    //printf("posicao arvore = %d\n", posicao_arvore);
    //printf("pos = %d\n", pos);
    if(posicao_arvore == -1){
        printf("Codigo nao cadastrado!\n");
        return;
    }
    NO no;
    ler_bloco(arq_index, posicao_arvore, &no);
    PRODUTO p;
    ler_bloco(arq_dados, no.registro[pos], &p);

    imprime_produto(&p);
}

//Realiza inclusoes em lote
//Pre-condicao: Arquivo txt com comandos e informacoes aberto
//Pos-condicao: Inclusoes, alteracoes e remocoes do arquivo efetuadas
void incluiLote(FILE *fr, ARQ_BIN* arq_indices, ARQ_BIN* arq_dados) {
    char text[300], *pt = NULL;
    PRODUTO p;
    while (fscanf(fr, "%[^\n]%*c", text) != EOF) {
        char *token = strtok(text, ";"); // pega o tipo
        if (strcmp(token, "I") == 0) {
            //printf("Insercao\n");
            p.cod = atoi(strtok(NULL, ";"));
            strcpy(p.nome, strtok(NULL, ";"));
            strcpy(p.marca, strtok(NULL, ";"));
            strcpy(p.categoria, strtok(NULL, ";"));
            p.estoque = atoi(strtok(NULL, ";"));
            strcpy(p.preco, strtok(NULL, ";"));
            //Funcao de insercao ja verifica produtos repetidos
            insere_produto(&p, arq_indices, arq_dados);
        }

        else if (strcmp(token, "R") == 0) {
            /*int info;
            info = atoi(strtok(NULL, ";"));
            removeProduto(info);*/
        }

        else if (strcmp(token, "A") == 0) {
            //printf("Alteracao\n");
            int info;
            char aux1[16] = "", aux2[16] = "", *ptr = text;
            ptr += 2;
            sscanf(ptr, "%d", &p.cod);
            ptr = &ptr[strcspn(ptr, ";") + 1];
            sscanf(ptr, "%[^;]", aux1);
            ptr = &ptr[strcspn(ptr, ";") + 1];
            sscanf(ptr, "%[^\n]", aux2);
            if (strcmp(aux1, "")) {
                //atualizaEstoque(p->id, atoi(aux1));
                atualizar_produto_lote(arq_indices, arq_dados, p.cod, atoi(aux1), aux2, 1);
            }
            if (strcmp(aux2, "")) {
                //atualizaPreco(p->id, atof(aux2));
                atualizar_produto_lote(arq_indices, arq_dados, p.cod, atoi(aux1), aux2, 0);
            }
        }
        else {
            printf("Entrada não reconhecida! \n");
        }
    }
    fclose(fr);
}

//Le o caminho do arquivo passado por input, e cadastra os itens nele
//Pre-condicao: Um caminho para um arquivo existente
//Pos-condicao: Registro dos itens nos arquivos binarios
void loadPath(ARQ_BIN* arq_indices, ARQ_BIN* arq_dados){
    FILE *fr;
    char path[50];
    do{
        printf("Nome do arquivo:");
        scanf("%s%*c", path);
        fr = fopen(path, "r");
    }
    while(fr == NULL);
    incluiLote(fr, arq_indices, arq_dados);
    printf("\n");
    fclose(fr);
}

// Atualiza o preco de um produto
// Pré-condição: produto existente
// Pós-condição: preco do produto alterado
PRODUTO atualiza_preco(PRODUTO p){
    printf("Entre com o novo preco: ");
    scanf("%*c%s", p.preco);
    //fgets(p.preco, 10, stdin);
    //p.preco[strcspn(p.preco,"\n")] = '\0';
    return p;
}

// Atualiza o estoque de um produto
// Pré-condição: produto existente
// Pós-condição: estoque do produto alterado
PRODUTO atualiza_estoque(PRODUTO p){
    printf("Entre com o novo estoque: ");
    scanf("%d%*c", &p.estoque);
    return p;
}

// Atualiza os dados de um produto nos arquivos de índices e dados
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados, opção de atualização
// Pós-condição: Os dados do produto são atualizados nos arquivos de índices e dados
void atualizar_produto(ARQ_BIN* arq_index, ARQ_BIN* arq_dados, int op){
    int cod;
    printf("Entre com o codigo: ");
    scanf("%d", &cod);
    int pos_dados;
    int pos_arvore = busca(arq_index, arq_index->cab.raiz, cod, &pos_dados);
    if(pos_arvore == -1){
        printf("Codigo [%d] nao encontrado!\n", cod);
        return;
    }
    NO r;
    ler_bloco(arq_index, pos_arvore, &r);
    PRODUTO p;
    ler_bloco(arq_dados, r.registro[pos_dados], &p);

    imprime_produto(&p);

    if(op == 0){
        p = atualiza_preco(p);
    }else{
        p = atualiza_estoque(p);
    }

    grava_bloco(arq_dados, &p, r.registro[pos_dados]);
    printf("Produto [%d] atualizado com sucesso!\n", cod);
}

// Atualiza o preco de um produto
// Pré-condição: produto existente
// Pós-condição: preco do produto alterado
PRODUTO atualiza_preco_lote(PRODUTO p, char* str){
    //printf("Entre com o novo preco: ");
    //scanf("%*c%s", p.preco);
    //fgets(p.preco, 10, stdin);
    //p.preco[strcspn(p.preco,"\n")] = '\0';
    strcpy(p.preco, str);
    return p;
}

// Atualiza o estoque de um produto
// Pré-condição: produto existente
// Pós-condição: estoque do produto alterado
PRODUTO atualiza_estoque_lote(PRODUTO p, int estoque){
    //printf("Entre com o novo estoque: ");
    //scanf("%d%*c", &p.estoque);
    p.estoque = estoque;
    return p;
}

// Atualiza os dados de um produto em lote nos arquivos de índices e dados
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados, código do produto, valores auxiliares e opção de atualização
// Pós-condição: Os dados do produto são atualizados nos arquivos de índices e dados
void atualizar_produto_lote(ARQ_BIN* arq_index, ARQ_BIN* arq_dados, int cod, int aux1, char* aux2, int op){
    int pos_dados;
    int pos_arvore = busca(arq_index, arq_index->cab.raiz, cod, &pos_dados);
    if(pos_arvore == -1){
        printf("Codigo [%d] nao encontrado!\n", cod);
        return;
    }
    NO r;
    ler_bloco(arq_index, pos_arvore, &r);
    PRODUTO p;
    ler_bloco(arq_dados, r.registro[pos_dados], &p);

    //imprime_produto(&p);

    if(op == 0){
        p = atualiza_preco_lote(p, aux2);
    }else{
        p = atualiza_estoque_lote(p, aux1);
    }

    grava_bloco(arq_dados, &p, r.registro[pos_dados]);
    printf("Produto com ID [%d] alterado!\n", cod);
}

//pré-requisitos: Recebe um ponteiro para um arquivo aberto de uma árvoreB que contém ao menos o
//                cabeçalho de indices gravado, a posição que um nó de árvore b se encontra e
//                um ponteiro para um arquivo aberto de indices
//pós-requisitos: Imprime na tela os dados do arquivo de dados em ordem crescente de código
void in_ordem(ARQ_BIN* arq_index, ARQ_BIN* arq_dados, int pos){
    if(pos == -1 ) {
        //printf("Sem produtos cadastrados ainda...\n");
        return;
    }
    int i;
    PRODUTO p;
    NO r;
    ler_bloco(arq_index, pos, &r);
    for(i = 0; i < r.numChaves; i++){
        in_ordem(arq_index, arq_dados, r.filhos[i]);
        //printf("[%d - %d]", r->chave[i], r->ptDados[i]);
        ler_bloco(arq_dados, r.registro[i], &p);
        imprime_produto(&p);
        printf("\n");
    }
    in_ordem(arq_index, arq_dados, r.filhos[i]);
}


// Lista todos os produtos presentes nos arquivos de índices e dados
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados
// Pós-condição: Os produtos são listados na tela
void listar_produtos(ARQ_BIN* arq_index, ARQ_BIN* arq_dados){
    if(arq_index->cab.raiz == -1){
        printf("Nenhum produto cadastrado ainda...\n");
        return;
    }
    in_ordem(arq_index, arq_dados, arq_index->cab.raiz);
}

// Imprime as posições livres no arquivo de índices
// Pré-condição: Ponteiro válido para o arquivo de índices
// Pós-condição: As posições livres são impressas na tela
void imprime_livre_index(ARQ_BIN* arq){
    if(arq->cab.livre == -1){
        printf("Lista de livres vazia!\n");
        return;
    }

    NO no;
    int livre = arq->cab.livre;
    while(livre != -1){
        printf("%d -> ", livre);
        ler_bloco(arq, livre, &no);
        livre = no.filhos[0];
    }
    printf("\n");
}

// Imprime as posições livres no arquivo de dados
// Pré-condição: Ponteiro válido para o arquivo de dados
// Pós-condição: As posições livres são impressas na tela
void imprime_livre_dados(ARQ_BIN* arq){
    if(arq->cab.livre == -1){
        printf("Lista de livres vazia!\n");
        return;
    }

    PRODUTO p;
    int livre = arq->cab.livre;
    while(livre != -1){
        printf("%d -> ", livre);
        ler_bloco(arq, livre, &p);
        livre = p.cod;
    }
    printf("\n");
}

// Função para gerenciar a remoção de um produto
// Pré-condição: Ponteiros válidos para os arquivos de índices e dados, código do produto
// Pós-condição: O produto é removido dos arquivos de índices e dados
void GerenciaRemocao(ARQ_BIN *arq_index, ARQ_BIN *arq_dados, int codigo){
    int pos, posArquivo;
    
    posArquivo = busca(arq_index, arq_index->cab.raiz, codigo, &pos);
    if(posArquivo == -1){
        printf("Codigo [%d] não encontrado\n", codigo);
        return;
    }
    NO r;
    ler_bloco(arq_index, posArquivo, &r);
    remover(arq_index, codigo);
    PRODUTO p;
    ler_bloco(arq_dados, r.registro[pos], &p);
    p.cod = arq_dados->cab.livre;
    arq_dados->cab.livre = r.registro[pos];
    grava_cabecalho(arq_dados);
    grava_bloco(arq_dados, &p, r.registro[pos]);
    printf("Codigo [%d] excluido com sucesso\n", codigo);
}


#endif