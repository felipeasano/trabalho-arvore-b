#ifndef ARVORE_C
#define ARVORE_C

#include "arvore.h"

// Verifica se o nó fornecido é folha
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

// cria uma fila
// Pré-condição: nenhuma
// Pós-condição: fila criada
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

// enfileira uma chave na fila
// Pré-condição: fila existente e chave a ser inserida
// Pós-condição: fila atualizada com chave
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

// desenfileira uma chave na fila
// Pré-condição: fila existente e chave a ser removida
// Pós-condição: fila atualizada sem a chave
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

// Imprime um nó da árvore
// Pré-condição: Ponteiro para nó válido
// Pós-condição: Nenhuma
void imprime_noB(NO* no){
    printf("-[");
    for(int i = 0; i < no->numChaves; i++){
        printf("%d", no->chaves[i]);
        if(i+1 < no->numChaves) printf("|");
    }
    printf("]-");
}

// Imprime a árvore por níveis
// Pré-condição: Arquivo de índices aberto e contendo pelo menos o cabeçalho gravado
// Pós-condição: Impressão da árvore por níveis
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
// Cria um nó da arvore
// Pré-condição: nenhuma
// Pós-condição: nó da arvore criado
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

// Realiza uma busca na árvore para encontrar a posição de um dado específico
// Pré-condição: Ponteiro para nó válido, informação a ser buscada, ponteiro para a variável que armazenará a posição encontrada
// Pós-condição: Retorna 1 se a informação foi encontrada, caso contrário retorna 0 e atualiza a posição
int buscaPos(NO* r, int info, int * pos) {
    for((*pos)=0; (*pos) < r->numChaves; (*pos)++)
        if(info == r->chaves[(*pos)])
            return 1;
        else if(info < r->chaves[(*pos)])
            break;
    return 0;
}

// Adiciona um novo elemento à direita do nó na posição pos_inserido
// Pré-condição: Ponteiro para nó válido, posição de inserção, chave, ponteiro de dado e posição do novo nó
// Pós-condição: Nenhuma
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

// Função auxiliar para inserção na árvore
// Pré-condição: Ponteiro para arquivo de índices válido, posição do arquivo onde ocorrerá a inserção,
// chave e ponteiro de dado a serem inseridos
// Pós-condição: Retorna a posição onde a inserção foi realizada
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
                //printf("pos_aux = %d\n", pos_aux);
                adiciona_direita(&r, pos, m, m_ptdado, pos_aux);
            }
        }
    }
    grava_bloco(arq_index, &r, pos_arquivo);
    return foi_inserido;
}

// Insere um novo elemento na árvore
// Pré-condição: Ponteiro para arquivo de índices válido, chave e ponteiro de dado a serem inseridos
// Pós-condição: Retorna a posição onde a inserção foi realizada
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
            //printf("split raiz = %d\n", posx);
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

// Realiza uma busca na árvore para encontrar a posição de um dado específico
// Pré-condição: Ponteiro para arquivo de índices válido, posição do arquivo onde inicia a busca,
// código a ser buscado, ponteiro para a variável que armazenará a posição encontrada
// Pós-condição: Retorna 1 se o código foi encontrado, caso contrário retorna 0 e atualiza a posição
int busca(ARQ_BIN* arq_index, int pos_arq, int cod, int *pos){
    if(pos_arq == -1){
        return -1;
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

//pré-requisitos: Ponteiro não nulo para nó da árvoreB
//pós-requisitos: Faz o "shift-left" a partir da posição indicada e retorna o filho que não faz mais parte
/*int retiraEsquerda(NO *r, int pos){
    int i;
    int aux;
    aux = r->filhos[pos];
    for(i = pos; i < r->numChaves-1; i++){
        r->chaves[i] = r->chaves[i+1];
        r->registro[i] = r->registro[i+1];
        r->filhos[i] = r->filhos[i+1];
    }
    r->filhos[i] = r->filhos[i+1];
    r->numChaves--;
    return aux;
}

//pré-requisitos: Recebe um ponteiro para um arquivo aberto de uma árvoreB que contém ao menos o
//                cabeçalho de indices gravado e uma posição valida para esse arquvo
//pós-requisitos: Retornar o valor mais a direita da arvoreB a partir da posição, e a posição para o arquivo
//                de dados correspontende
int sucessor(ARQ_BIN *arq_index, int posArquivo, int *ptDados){
    NO r;
    ler_bloco(arq_index, posArquivo, &r);
    int Vsucessor;
    if(eh_folha(&r)){
        Vsucessor =  r.chaves[r.numChaves-1];
        *ptDados = r.registro[r.numChaves-1];
    } else{
        Vsucessor = sucessor(arq_index, r.filhos[r.numChaves], ptDados);
    }
    return Vsucessor;
}

//pré-requisitos: Recebe um ponteiro para um arquivo aberto de uma árvoreB que contém ao menos o
//                cabeçalho de indices gravado e uma posição valida para esse arquvo
//pós-requisitos: Retorna 1 se o nó está com underflow, 0 caso não esteja
int underflow(ARQ_BIN* arq_index, int posArquivo){
    int isUndeflow;
    NO r;
    ler_bloco(arq_index, posArquivo, &r);
    isUndeflow = (r.numChaves < ORDEM / 2);
    return isUndeflow;
}

//pré-requisitos: Recebe um ponteiro para um arquivo aberto de uma árvoreB que contém ao menos o
//                cabeçalho de indices gravado e uma posição valida para esse arquvo
//pós-requisitos: Retorna 1 se o nó pode emprestar, 0 caso não possa
int podeEmprestar(ARQ_BIN* arq_index, int posArquivo){
    NO r;
    ler_bloco(arq_index, posArquivo, &r);
    int pode = r.numChaves > ((ORDEM/2));
    return pode;
}

//pré-requisitos: Ponteiro não nulo para nó da árvoreB
//pós-requisitos: Adiciona os dados do parametro nas posição 0 da arvoreB, e empura os outros uma posição
void adicionaEsquerda(NO *r, int chave, int ptDados, int nova){
    int i = 0;
    for(i = r->numChaves; i > 0; i--){
        r->chaves[i] = r->chaves[i-1];
        r->registro[i] = r->registro[i-1];
        r->filhos[i+1] = r->filhos[i];
    }
    r->filhos[1] = r->filhos[0];
    r->chaves[0] = chave;
    r->registro[0] = ptDados;
    r->filhos[0] = nova;
    r->numChaves++;
}

//pré-requisitos: Ponteiros não nulos para nós da árvoreB
//pós-requisitos: Passo o valor da chave do nó sem_overflow para o pai, e do pai para o nó com underflow
void emprestaEsquerda(NO *raiz, int posUnderflow, NO *com_undeflow, NO *sem_underflow){
    int chavePai, ptDadoPai, chaveSemUnder, ptDadoSemUnder, aux;
    chavePai = raiz->chaves[posUnderflow-1];
    ptDadoPai = raiz->registro[posUnderflow-1];
    chaveSemUnder = sem_underflow->chaves[sem_underflow->numChaves - 1];
    ptDadoSemUnder = sem_underflow->registro[sem_underflow->numChaves - 1];

    aux = sem_underflow->filhos[sem_underflow->numChaves];

    adicionaEsquerda(com_undeflow, chavePai, ptDadoPai, aux);
    raiz->chaves[posUnderflow-1] = chaveSemUnder;
    raiz->registro[posUnderflow-1] = ptDadoSemUnder;

    sem_underflow->numChaves--;
}

//pré-requisitos: Ponteiros não nulos para nós da árvoreB
//pós-requisitos: Passo o valor da chave do nó sem_overflow para o pai, e do pai para o nó com underflow
void emprestaDireita(NO *raiz, int posUnderflow, NO *com_undeflow, NO *sem_underflow){
    int chavePai, ptDadoPai, chaveSemUnder, ptDadoSemUnder, aux;
    chavePai = raiz->chaves[posUnderflow];
    ptDadoPai = raiz->registro[posUnderflow];
    chaveSemUnder = sem_underflow->chaves[0];
    ptDadoSemUnder = sem_underflow->registro[0];
    aux = retiraEsquerda(sem_underflow, 0);

    com_undeflow->chaves[com_undeflow->numChaves] = chavePai;
    com_undeflow->registro[com_undeflow->numChaves] = ptDadoPai;
    com_undeflow->filhos[com_undeflow->numChaves+1] = aux;
    com_undeflow->numChaves++;
    raiz->chaves[posUnderflow] = chaveSemUnder;
    raiz->registro[posUnderflow] = ptDadoSemUnder;
}

//pré-requisitos: Ponteiro não nulo para nó da árvoreB, e arquivo aberto
//pós-requisitos: Retorna 1 se foi possivel emprestar, e 0 se não
int empresta(ARQ_BIN* arq_index, NO *r, int posUnderflow){
    //verifica se não é o mais a direita
    if(posUnderflow - 1 >= 0 && podeEmprestar(arq_index, r->filhos[posUnderflow-1])){
        NO com_undeflow;
        ler_bloco(arq_index, r->filhos[posUnderflow-1], &com_undeflow);

        NO sem_underflow;
        ler_bloco(arq_index, r->filhos[posUnderflow-1], &sem_underflow);

        emprestaEsquerda(r, posUnderflow, &com_undeflow, &sem_underflow);

        grava_bloco(arq_index, &com_undeflow, r->filhos[posUnderflow]);
        grava_bloco(arq_index, &sem_underflow, r->filhos[posUnderflow-1]);

        return 1;
    }
    //verifica se não é o mais a direita
    if(posUnderflow + 1 <= r->numChaves && podeEmprestar(arq_index, r->filhos[posUnderflow+1])){
        NO com_undeflow;
        ler_bloco(arq_index, r->filhos[posUnderflow], &com_undeflow);

        NO sem_underflow;
        ler_bloco(arq_index, r->filhos[posUnderflow+1], &sem_underflow);
        //Carregar os valore que vão sofre o empresta
        emprestaDireita(r, posUnderflow, &com_undeflow, &sem_underflow);
        grava_bloco(arq_index, &com_undeflow, r->filhos[posUnderflow]);

        grava_bloco(arq_index, &sem_underflow, r->filhos[posUnderflow+1]);
        return 1;
    }
    return 0;
}

//pré-requisitos: Ponteiros não nulos para nós da árvoreB
//pós-requisitos: Faz a operação de merge, onde o ponteiro da esquerda sempre recebe os dados da direita
void mergeAux(NO *raiz, int posUnderflow, NO *aDireita, NO *aEsquerda, int isEsq){
    int chavePai, ptDadosPai, i, j, aux;

    chavePai = raiz->chaves[posUnderflow - isEsq];
    ptDadosPai = raiz->registro[posUnderflow - isEsq];
    aEsquerda->chaves[aEsquerda->numChaves] = chavePai;
    aEsquerda->registro[aEsquerda->numChaves] = ptDadosPai;
    aEsquerda->numChaves++;
    j = aEsquerda->numChaves;
    for(i = 0; i < aDireita->numChaves; i++){
        aEsquerda->chaves[j] = aDireita->chaves[i];
        aEsquerda->registro[j] = aDireita->registro[i];
        aEsquerda->filhos[j] = aDireita->filhos[i];
        aEsquerda->numChaves++;
        j++;
    }
    aEsquerda->filhos[j] = aDireita->filhos[i];
    aux = retiraEsquerda(raiz, posUnderflow-isEsq);
   // free(aDireita);
    //inserirLivre
    raiz->filhos[posUnderflow-isEsq] = aux;
}

//pré-requisitos: Ponteiro não nulo para nó da árvoreB, e arquivo aberto
//pós-requisitos: A posição com underfow deixa de estar com underflow
void merge(ARQ_BIN* arq_index, NO *r, int posUnderflow){
    if(posUnderflow - 1 >= 0){
        int posExcluido = r->filhos[posUnderflow];
        int posContinua = r->filhos[posUnderflow - 1];
        NO aDireita;
        ler_bloco(arq_index, r->filhos[posUnderflow], &aDireita);
        NO aEsquerda;
        ler_bloco(arq_index, r->filhos[posUnderflow-1], &aEsquerda);
        mergeAux(r, posUnderflow, &aDireita, &aEsquerda, 1);
        grava_bloco(arq_index, &aEsquerda, posContinua);
        aDireita.filhos[0] = arq_index->cab.livre;
        aDireita.filhos[1] = 1245;
        arq_index->cab.livre = posExcluido;
        grava_bloco(arq_index, &aDireita, posExcluido);
       // printf("Adicionando Livre = %d\n", posExcluido);
        return;
    }
    //verifica se não é o mais a direita
    if(posUnderflow + 1 <= r->numChaves ){
        int posExcluido = r->filhos[posUnderflow + 1];
        int posContinua = r->filhos[posUnderflow];
        NO aDireita;
        ler_bloco(arq_index, r->filhos[posUnderflow+1], &aDireita);
        NO aEsquerda;
        ler_bloco(arq_index, r->filhos[posUnderflow], &aEsquerda);
        mergeAux(r, posUnderflow, &aDireita, &aEsquerda, 0);
        grava_bloco(arq_index, &aEsquerda, posContinua);
        aDireita.filhos[0] = arq_index->cab.livre;
        arq_index->cab.livre = posExcluido;
        grava_bloco(arq_index, &aDireita, posExcluido);
       // printf("Adicionando Livre = %d\n", posExcluido);
        return;
    }
}

//pré-requisitos: Recebe um ponteiro para um arquivo aberto de uma árvoreB que contém ao menos o
//                cabeçalho de indices gravado e uma posição valida para esse arquvo
//pós-requisitos: Info será removido da arvoreB
void removeAux(ARQ_BIN* arq_index, int posArquvio, int info){
    if(posArquvio == -1){
        printf("Elemento não encontrado");
        return;
    }
    NO r;
    ler_bloco(arq_index, posArquvio, &r);
    int pos;
    if(buscaPos(&r,info, &pos)){ // O elemento está no nó
        if(eh_folha(&r)){
            retiraEsquerda(&r, pos);
            r.filhos[0] = -1;
            grava_bloco(arq_index, &r, posArquvio);
            return;
        } else{
            int ptDados;
            r.chaves[pos] = sucessor(arq_index, r.filhos[pos], &ptDados);
            r.registro[pos] = ptDados;
            info = r.chaves[pos];
        }
    }
    removeAux(arq_index, r.filhos[pos], info);
    if(underflow(arq_index, r.filhos[pos])){
        if(!empresta(arq_index, &r, pos)){
            merge(arq_index, &r, pos);
        }
    }
}


//pré-requisitos: Recebe um ponteiro para um arquivo aberto de uma árvoreB que contém ao menos o
//                cabeçalho de indices gravado
//pós-requisitos: Info será removido da arvoreB
void remover(ARQ_BIN* arq_index, int info){
    if(arq_index->cab.raiz == -1){
        printf("Arvore Vazia!\n");
        return;
    }
    //verificar
    removeAux(arq_index, arq_index->cab.raiz, info);
    NO r;
    ler_bloco(arq_index, arq_index->cab.raiz, &r);
    if(r.numChaves == 0){
        int aux = r.filhos[0];
        r.filhos[0] = arq_index->cab.livre;
       // printf("Inserindo Livre %d\n", cab->raiz);
        grava_bloco(arq_index, &r, arq_index->cab.raiz);
        arq_index->cab.livre = arq_index->cab.raiz;
        arq_index->cab.raiz = aux;
    }
    grava_cabecalho(arq_index);
}*/

#endif