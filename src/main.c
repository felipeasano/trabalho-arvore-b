#include "view.h"

int main(){
    
    ARQ_BIN arq_indices;
    ARQ_BIN arq_dados;

    abre_arq_bin("indices.bin", &arq_indices, sizeof(NO));
    abre_arq_bin("dados.bin", &arq_dados, sizeof(PRODUTO));

    int opcao;

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

        switch (opcao) {
            case 1:
                //cadastrar_produto(&arq_dados, &arq_indices);
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