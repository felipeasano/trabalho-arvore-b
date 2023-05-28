#include "view.h"

void imprime_cab(ARQ_BIN* b){
    printf("raiz:  %d\n", b->cab.raiz);
    printf("topo:  %d\n", b->cab.topo);
    printf("livre: %d\n", b->cab.livre);
}

int main(){
    
    ARQ_BIN arq_indices;
    ARQ_BIN arq_dados;

    abre_arq_bin("indices.bin", &arq_indices, sizeof(NO));
    abre_arq_bin("dados.bin", &arq_dados, sizeof(PRODUTO));

    int opcao;
    char path[40];
    PRODUTO p;
    NO no;
    ler_bloco(&arq_indices, arq_indices.cab.raiz, &no);

    printf("chaves: ");
    for(int i = 0; i < ORDEM; i++){
        printf("%d |", no.chaves[i]);
    }
    printf("\n");
    printf("filhos: ");
    for(int i = 0; i < ORDEM; i++){
        printf("%d |", no.filhos[i]);
    }
    printf("\nNumChaves: %d\n\n", no.numChaves);

    NO filho0;
    ler_bloco(&arq_indices, no.filhos[0], &filho0);
    printf("\nfilho 0:\n");
    printf("chaves: ");
    for(int i = 0; i < ORDEM; i++){
        printf("%d |", filho0.chaves[i]);
    }
    printf("\n");
    printf("filhos: ");
    for(int i = 0; i < ORDEM; i++){
        printf("%d |", filho0.filhos[i]);
    }
    printf("\nNumChaves: %d\n", filho0.numChaves);

    NO filho1;
    ler_bloco(&arq_indices, no.filhos[1], &filho1);
    printf("\nfilho 1:\n");
    printf("chaves: ");
    for(int i = 0; i < ORDEM; i++){
        printf("%d |", filho1.chaves[i]);
    }
    printf("\n");
    printf("filhos: ");
    for(int i = 0; i < ORDEM; i++){
        printf("%d |", filho1.filhos[i]);
    }
    printf("\nNumChaves: %d\n", filho1.numChaves);

    while(1){
        //system("cls");
        imprime_menu();
        scanf("%d", &opcao);

        imprime_cab(&arq_indices);
        switch (opcao) {
            case 0:
                fecha_arq_bin(&arq_indices);
                fecha_arq_bin(&arq_dados);
                printf("Fim do Programa\n");
                return 0;
            case 1:
                //cadastrar_produto(&arq_dados, &arq_indices);
                p = cria_novo_produto();

                insere_produto(&p, &arq_indices, &arq_dados);
                //imprime_cab(&arq_indices);
                break;
            case 2:
                //removerProduto();
                break;
            case 3:
                //atualizarPreco();
                break;
            case 4:
                //atualizarEstoque();
                break;
            case 5:
                //imprimirInformacoesProduto();
                break;
            case 6:
                //imprimirListaProdutos();
                break;
            case 7:
                //imprimirArvore();
                imprime_por_niveis(&arq_indices);
                break;
            case 8:
                //imprimirListaLivresIndices();
                break;
            case 9:
                //imprimirListaLivresDados();
                break;
            case 10:
                loadPath(&arq_indices, &arq_dados);
                break;
            default:
                printf("Entrada invalida\n");
                break;
        }
        system("pause");
    }

}