#ifndef ARVORE_C
#define ARVORE_C

#include "arvore.h"

// Veritica se o nó fornecido é folha
// Pré-condição: Ponteiro para manipulador de indices válido
// Pós-condição: Nenhuma
int eh_folha(NO* no){
    return (no->filhos[0] == -1);
}

// Verifica se o nó fornecido esta em overflow
// Pré-condição: Ponteiro para nó válido
// Pós-condição: Nenhuma
int eh_overflow(NO* no){
    return no->numChaves == ORDEM;
}

// Verifica se o nó fornecido esta em underflow
// Pré-condição: Ponteiro para nó válido
// Pós-condição: Nenhuma
int eh_underflow(NO* no){
    return no->numChaves < ORDEM/2;
}

FILA* cria_fila(){
    FILA *f = (FILA*)malloc(sizeof(FILA));
    f->inicio = NULL;
    f->fim = NULL;
    return f;
}

//pré-requisitos: Recebe um ponteiro não nulo para fila
//pós-requisitos: Retorna 1 se a fila for vazio e 0 se não
int fila_vazia(FILA *f){
    return f->inicio == NULL;
}

//pré-requisitos: Um ponteiro não nulo para fila
//pós-requisitos: a quantidade de elementos na fila é retornado
int fila_tam(FILA *f){
    NO_FILA* aux = f->inicio;
    int i = 0;
    while(aux){
        i++;
        aux = aux->prox;
    }
    return i;
}

void enqueue(FILA *f, int pos){
    NO_FILA* aux = (NO_FILA*)malloc(sizeof(NO_FILA));
    aux->pos = pos;
    aux->prox = NULL;
    if(fila_vazia(f)){
        f->inicio = aux;
    }else{
        f->fim->prox = aux;
    }
    f->fim = aux;
}

int dequeue(FILA* f){
    NO_FILA* aux = f->inicio;
    int pos = f->inicio->pos;
    if(f->inicio == f->fim){
        f->fim = NULL;
    }
    f->inicio = f->inicio->prox;
    free(aux);
    return pos;
}

void imprime_noB(NO* no){
    printf("- [ ");
    for(int i = 0; i < no->numChaves; i++){
        printf("%d", no->chaves[i]);
        if(i+1 < no->numChaves) printf(" | ");
    }
    printf(" ] - ");
}

void imprime_por_niveis(ARQ_BIN* arq_index){

    if(arq_index->cab.raiz == -1){
        printf("Nenhum produto cadastrado ainda...\n");
        return;
    }

    FILA* fila = cria_fila();
    if (arq_index->cab.raiz == -1) {
        return;
    }
    enqueue(fila, arq_index->cab.raiz);
    enqueue(fila, -1);
    while (!fila_vazia(fila)) {
        int pos = dequeue(fila);
        if (pos == -1) {
            printf("\n");
            if (!fila_vazia(fila)) {
                enqueue(fila, -1);
            }
            continue;
        }
        NO no;
        ler_bloco(arq_index, pos, &no);
        imprime_noB(&no);
        if (!eh_folha(&no)) {
            int n = no.numChaves;
            for (int i=0; i<n+1; ++i) {
                enqueue(fila, no.filhos[i]);
            }
        }
    }
    free(fila);
}

NO* cria_no(){
    NO* no = (NO*)malloc(sizeof(NO));
    no->numChaves = 0;
    for(int i = 0; i < ORDEM; i++){
        no->filhos[i] = -1;
    }
    return no;
}

//pré-requisitos: Recebe um ponteiro para um arquivo aberto de uma árvoreB que contém ao menos o
//                cabeçalho de indices gravado
//pós-requisitos: Retorna a posição onde o novo dado dever ser inserido
int retorna_livre(ARQ_BIN* arq_index){

    NO aux;
    if(arq_index->cab.livre == -1) return arq_index->cab.topo;
    else{
        int retorno = arq_index->cab.livre;
        ler_bloco(arq_index, arq_index->cab.livre, &aux);
        arq_index->cab.livre = aux.filhos[0];
        return retorno;
    }
}

NO cria_no_arvore(){
    NO no;
    no.numChaves = 0;
    for(int i = 0; i < ORDEM; i++){
        no.filhos[i] = -1;
    }
    return no;
}

//pré-requisitos: Recebe um ponteiro para um arquivo aberto de uma árvoreB que contém ao menos 1 nó
//                gravado e o cabeçalho
//pós-requisitos: A partir do no gravado na posição "posX" faz o split do nó e salva esse novo nó
//                na posição "posY". Retorna "posY", além do elemento do meio do nó onde ocorreu o split
int split(ARQ_BIN* arq_index, int posX, int *m, int *m_ptDado) {
    int posY = retorna_livre(arq_index);
    NO y = cria_no_arvore(&y);
    NO x = cria_no_arvore(&x);
    ler_bloco(arq_index, posX, &x);
    int q = x.numChaves/2;
    y.numChaves = x.numChaves - q - 1;
    x.numChaves = q;
    *m = x.chaves[q]; // chave mediana
    *m_ptDado = x.registro[q];
    int i = 0;
    y.filhos[0] = x.filhos[q+1];
    for(i = 0; i < y.numChaves; i++){
        y.chaves[i] = x.chaves[q+i+1];
        y.registro[i] = x.registro[q+i+1];
        y.filhos[i+1] = x.filhos[q+i+2];
    }
    grava_bloco(arq_index, &y, posY);
    grava_bloco(arq_index, &x, posX);
    if(posY == arq_index->cab.topo)
        arq_index->cab.topo++; //A função que chamou a split salva a atualização no arquivo
        //grava_cabecalho(arq_index);
    return posY;
}

int buscaPos(NO* r, int info, int * pos) {
    for((*pos)=0; (*pos) < r->numChaves; (*pos)++)
        if(info == r->chaves[(*pos)])
            return 1;
        else if(info < r->chaves[(*pos)])
            break;
    return 0;
}

void adiciona_direita(NO* r, int pos_inserido, int chave, int ptdado, int pos_novo_no){
    int i;
    for(i = r->numChaves; i>pos_inserido; i--){
        r->chaves[i] = r->chaves[i-1];
        r->registro[i] = r->registro[i-1];
        r->filhos[i+1] = r->filhos[i];
    }
    r->chaves[pos_inserido] = chave;
    r->registro[pos_inserido] = ptdado;
    r->filhos[pos_inserido+1] = pos_novo_no;
    r->numChaves++;
}

int insere_aux(ARQ_BIN* arq_index, int pos_arquivo, int chave, int ptdado){
    int pos;
    int foi_inserido = 0;
    NO r;
    ler_bloco(arq_index, pos_arquivo, &r);
    if(!buscaPos(&r, chave, &pos)){
        if(eh_folha(&r)){
            adiciona_direita(&r, pos, chave, ptdado, -1);
            foi_inserido = 1;
        }else{
            foi_inserido = insere_aux(arq_index, r.filhos[pos], chave, ptdado);
            NO filho_pos;
            ler_bloco(arq_index, r.filhos[pos], &filho_pos);
            if(eh_overflow(&filho_pos)){
                int m, m_ptdado;
                int pos_aux = split(arq_index, r.filhos[pos], &m, &m_ptdado);
                printf("pos_aux = %d\n", pos_aux);
                adiciona_direita(&r, pos, m, m_ptdado, pos_aux);
            }
        }
    }
    grava_bloco(arq_index, &r, pos_arquivo);
    return foi_inserido;
}

int insere(ARQ_BIN* arq_index, int chave, int ptdado){
    int foi_inserido = 0;
    if(arq_index->cab.raiz == -1){
        NO raiz;
        raiz.chaves[0] = chave;
        raiz.registro[0] = ptdado;
        for(int i = 0; i < ORDEM; i++){
            raiz.filhos[i] = -1;
        }
        raiz.numChaves = 1;
        grava_bloco(arq_index, &raiz, arq_index->cab.topo);
        arq_index->cab.raiz = arq_index->cab.topo;
        arq_index->cab.topo++;
        foi_inserido = 1;
    }else{
        foi_inserido = insere_aux(arq_index, arq_index->cab.raiz, chave, ptdado);
        NO raiz;
        ler_bloco(arq_index, arq_index->cab.raiz, &raiz);
        if(eh_overflow(&raiz)){
            int m, m_ptdado, pos_livre;
            int posx = split(arq_index, arq_index->cab.raiz, &m, &m_ptdado);
            printf("split raiz = %d\n", posx);
            NO nova_raiz;
            nova_raiz.chaves[0] = m;
            nova_raiz.registro[0] = m_ptdado;
            nova_raiz.filhos[0] = arq_index->cab.raiz;
            nova_raiz.filhos[1] = posx;
            NO r;
            ler_bloco(arq_index, arq_index->cab.raiz, &r);
            for(int i = (((int)ORDEM/2)+1); i < ORDEM; i++)
                r.filhos[i] = -1;
            nova_raiz.numChaves = 1;

            pos_livre = retorna_livre(arq_index);

            grava_bloco(arq_index, &r, arq_index->cab.raiz);
            grava_bloco(arq_index, &nova_raiz, pos_livre);
            arq_index->cab.raiz = pos_livre;
            if(pos_livre == arq_index->cab.topo){
                arq_index->cab.topo++;
            }
        }
    }
    grava_cabecalho(arq_index);
    return foi_inserido;
}

int busca(ARQ_BIN* arq_index, int pos_arq, int cod, int *pos){
    if(pos_arq == -1){
        return 1;
    }
    NO no;
    ler_bloco(arq_index, pos_arq, &no);

    int i = 0;
    while(i < no.numChaves && no.chaves[i] < cod){
        i++;
    }
    if((i+1) > no.numChaves || no.chaves[i] > cod){
        int filhoI = no.filhos[i];
        return busca(arq_index, filhoI, cod, pos);
    }
    *pos = i;
    return pos_arq;
}

#endif