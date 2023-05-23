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

NO* cria_no(){
    NO* no = (NO*)malloc(sizeof(NO));
    no->numChaves = 0;
    for(int i = 0; i < ORDEM; i++){
        no->filhos[i] = -1;
    }
    return no;
}

// Função recursiva para encontrar a referencia da chave passada
// Pré-condição: Ponteiro para manipulador de arvore
// Pós-condição: Retorna o numero da referencia da chave caso seja encontrada,
// caso contrario, -1 é retornado
static int busca_aux(ARQ_BIN* arq_index, int filePos, int key, int *pos) {
    if (filePos == -1)
        return -1;
    NO no;
    ler_bloco(arq_index, filePos, &no);

    int i = 0;
    while (i < no.numChaves && no.chaves[i] < key) {
        i++;
    }
    if (i + 1 > no.numChaves || no.chaves[i] > key)
        return busca_aux(arq_index, no.filhos[i], key, pos);
    *pos = i;
    return filePos;
}

// Procura a referencia da chave fornecida na arvore B
// Pré-condição: Ponteiro para manipulador de arvore válido
// Pós-condição: Retorna a referencia da chave, caso não seja encontrada,
// -1 é retornado
int busca(ARQ_BIN* arq_index, int key) {
    int pos, registro;

    if (arq_index->cab.raiz == -1)
        registro = -1;
    else
        registro = busca_aux(arq_index, arq_index->cab.raiz, key, &pos);

    if (registro != -1) {
        NO no;
        ler_bloco(arq_index, registro, &no);
        registro = no.registro[pos];
    }
    return registro;
}

// Busca a posicao em que a chave esta ou estaria no nó
// Pré-condição: Ponteiro para nó valido
// Pós-condição: Retorna 1 caso chave esteja no nó e 0 caso contrario
int busca_pos_chave(NO *no, int chave, int *pos) {
    for ((*pos) = 0; (*pos) < no->numChaves; (*pos)++) {
        if (chave == no->chaves[(*pos)])
            return 1;
        else if (chave < no->chaves[(*pos)])
            break;
    }
    return 0;
}

// Adiciona a chave e referencia posição fornecida no nó fornecido, adicionando
// o filho fornecio a direita
// Pré-condição: Ponteiro para nó valido
// Pós-condição: Nó modificado
void addToRight(NO *no, int pos, int chave, int registro, int rightChild) {
    for (int i = no->numChaves; i > pos; i--) {
        no->chaves[i] = no->chaves[i - 1];
        no->registro[i] = no->registro[i - 1];
        no->filhos[i + 1] = no->filhos[i];
    }
    no->chaves[pos] = chave;
    no->registro[pos] = registro;
    no->filhos[pos + 1] = rightChild;
    no->numChaves++;
}

// Adiciona a chave e referencia posição fornecida no nó fornecido, adicionando
// o filho fornecio a esquerda
// Pré-condição: Ponteiro para nó valido
// Pós-condição: Nó modificado
void addToLeft(NO *no, int pos, int chave, int registro, int leftChild) {
    for (int i = no->numChaves; i > pos; i--) {
        no->chaves[i] = no->chaves[i - 1];
        no->registro[i] = no->registro[i - 1];
        no->filhos[i + 1] = no->filhos[i];
    }
    no->filhos[pos+1] = no->filhos[pos];
    no->chaves[pos] = chave;
    no->registro[pos] = registro;
    no->filhos[pos] = leftChild;
    no->numChaves++;
}

// Adiciona novo nó ao arquivo de indices, caso nenhuma posiçao livre exista
// o nó é adicionado no topo do arquivo, caso contrario a posicao livre é utilizada
// Pré-condição: Ponteiro para manipulador de indices valido e ponteiro para nó
// Pós-condição: Retorna a posição do nó no arquivo de indices
int add_no(ARQ_BIN* arq_index, NO *no) {
    int pos;
    if (arq_index->cab.livre == -1) {
        pos = arq_index->cab.topo;
        arq_index->cab.topo++;
    } else {
        pos = arq_index->cab.livre;
        NO *aux;
        ler_bloco(arq_index, arq_index->cab.livre, aux);
        arq_index->cab.livre = aux->numChaves;
        free(aux);
    }
    grava_bloco(arq_index, no, pos);
    grava_cabecalho(arq_index);
    return pos;
}

NO* split(NO* over_no, int *chave_med, int *registro_med){
    NO* novo_no = cria_no();
    int q = over_no->numChaves/2;
    novo_no->numChaves = over_no->numChaves-q-1;
    *chave_med = over_no->chaves[q];
    *registro_med = over_no->registro[q];
    over_no->numChaves = q;
    novo_no->filhos[0] = over_no->filhos[q+1];

    for(int i = 0; i < novo_no->numChaves; i++){
        novo_no->chaves[i] = over_no->chaves[q+i+1];
        novo_no->registro[i] = over_no->registro[q+i+1];
        novo_no->filhos[i+1] = over_no->filhos[q+i+2];
    }
    return novo_no;
}

// Função recursiva para inserir chave na arvore B, busca a posicao de insercao e
// corrige nós em overflow
// Pré-condição: Ponteiro para manipulador de arvore válido
// Pós-condição: Retorna o nó da posição fornecida com as modificações necessárias
NO* insere_aux(ARQ_BIN* arq_index, int pos_no, int chave, int registro){
    int pos;
    NO* no;
    ler_bloco(arq_index, pos_no, no);

    if(busca_pos_chave(no, chave, &pos)){
        if(eh_folha(no)){
            addToRight(no, pos, chave, registro, -1);
        }else{
            NO* aux = insere_aux(arq_index, no->filhos[pos], chave, registro);
            if(eh_overflow(aux)){
                int chave_med, registro_med;
                NO* novo_no = split(aux, &chave_med, &registro_med);
                int novo_registro = add_no(arq_index, novo_no);
                addToRight(no, pos, chave_med, registro_med, novo_registro);
                grava_bloco(arq_index, aux, no->filhos[pos]);
                free(novo_no);
            }
            grava_bloco(arq_index, aux, no->filhos[pos]);
            free(aux);
        }
    }
    return no;
}

// Insere uma chave e uma referencia na arvore B realizando as devidas
// correçoes caso o nó fiquem em overflow
// Pré-condição: Ponteiro para manipulador de arvore válido
// Pós-condição: Chave e referencia adicionadas
void insere(ARQ_BIN* arq_index, int cod, int registro){
    NO* no;
    if(arq_index->cab.raiz == -1){
        arq_index->cab.topo++;
        arq_index->cab.raiz = 0;
        grava_cabecalho(arq_index);
        no = cria_no();
        no->chaves[0] = cod;
        no->registro[0] = registro;
        no->numChaves++;
        grava_bloco(arq_index, no, 0);
    }else{
        no = insere_aux(arq_index, arq_index->cab.raiz, cod, registro);
        if(eh_overflow(no)){
            int chave_med;
            int registro_med;
            NO* aux = split(no, &chave_med, &registro_med);
            int registro_aux = add_no(arq_index, aux);
            NO* nova_raiz = cria_no();
            nova_raiz->chaves[0] = chave_med;
            nova_raiz->registro[0] = registro_med;
            nova_raiz->filhos[0] = arq_index->cab.raiz;
            nova_raiz->filhos[1] = registro_aux;

            for(int i = (ORDEM/2)+1; i < ORDEM; i++){
                no->filhos[i] = -1;
            }
            nova_raiz->numChaves = 1;
            int pos_raiz = add_no(arq_index, nova_raiz);
            grava_bloco(arq_index, no, arq_index->cab.raiz);
            arq_index->cab.raiz = pos_raiz;
            grava_cabecalho(arq_index);
        }else{
            grava_bloco(arq_index, no, arq_index->cab.raiz);
        }
    }
    free(no);
}
#endif