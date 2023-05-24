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
    PRODUTO p;
    NO no;
    ler_bloco(&arq_indices, 0, &no);

    printf("chaves: ");
    for(int i = 0; i < ORDEM; i++){
        printf("%d |", no.chaves[i]);
    }
    printf("\nNumChaves: %d\n", no.numChaves);

    while(1){
        //system("cls");
        imprime_menu();
        scanf("%d", &opcao);
        if(opcao == 0){
            fecha_arq_bin(&arq_indices);
            fecha_arq_bin(&arq_dados);
            printf("Fim do Programa\n");
            break;
        }
        imprime_cab(&arq_indices);
        switch (opcao) {
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
                break;
            case 8:
                //imprimirListaLivresIndices();
                break;
            case 9:
                //imprimirListaLivresDados();
                break;
            case 10:
                //realizarOperacoesLote();
                break;
            default:
                printf("Entrada invalida\n");
                break;
        }
        system("pause");
    }

    return 0;
}