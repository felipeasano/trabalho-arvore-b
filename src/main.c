#include "view.h"

void imprime_cab(ARQ_BIN* b){
    printf("raiz:  %d\n", b->cab.raiz);
    printf("topo:  %d\n", b->cab.topo);
    printf("livre: %d\n", b->cab.livre);
}

int main(){
    
    ARQ_BIN arq_indices;
    ARQ_BIN arq_dados;

    abre_arq_bin("../indices.bin", &arq_indices, sizeof(NO));
    abre_arq_bin("../dados.bin", &arq_dados, sizeof(PRODUTO));

    int opcao;
    int info;
    char path[40];
    PRODUTO p;
    
    while(1){
        //system("cls");
        imprime_menu();
        scanf("%d", &opcao);

        //imprime_cab(&arq_indices);
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
                printf("Entre com o Codigo do produto a ser removido: ");
                scanf("%d*%c", &info);
                //GerenciaRemocao(&arq_indices, &arq_dados, info);
                break;
            case 3:
                //atualizarPreco();
                atualizar_produto(&arq_indices, &arq_dados, 0);
                break;
            case 4:
                //atualizarEstoque();
                atualizar_produto(&arq_indices, &arq_dados, 1);
                break;
            case 5:
                //imprimirInformacoesProduto();
                busca_produto(&arq_indices, &arq_dados);
                break;
            case 6:
                //imprimirListaProdutos();
                listar_produtos(&arq_indices, &arq_dados);
                break;
            case 7:
                //imprimirArvore();
                imprime_por_niveis(&arq_indices);
                break;
            case 8:
                //imprimirListaLivresIndices();
                imprime_livre_index(&arq_indices);
                break;
            case 9:
                //imprimirListaLivresDados();
                imprime_livre_dados(&arq_dados);
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