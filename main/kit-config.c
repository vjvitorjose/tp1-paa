#include "kit-config.h"

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DE MATRIZES
--------------------------------------------------------------------------------*/

int** alocaMatriz(int linhas, int colunas){

    int** matriz = malloc(linhas*sizeof(int*));
    for(int i = 0; i < linhas; i++){
        matriz[i] = (int*)malloc(colunas*sizeof(int));
    }

    inicializaMatriz(matriz, linhas, colunas);
    return matriz;

}

void inicializaMatriz(int** matriz, int linhas, int colunas){

    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            matriz[i][j] = 0;
        }
    }

}

void desalocaMatriz(int** matriz, int linhas){

    for(int i = 0; i < linhas; i++){
        free(matriz[i]);
    }
    free(matriz);

}

void imprimeMatriz(int** matriz, int linhas, int colunas){

    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }

}

/*--------------------------------------------------------------------------------
MÉTODOS PARA VERIFICAÇÂO DA COMPOSIÇÃO
--------------------------------------------------------------------------------*/

int checkComposicao(int** matriz){

    int contador = 0;
    int flags[4] = {0, 0, 0, 0};

    for(int i = 0; i < 12; i++){
        for(int j = 0; j < 3; j++){
            contador += matriz[i][0];
        }
    }

    if(contador > 36)
        return 0;

}