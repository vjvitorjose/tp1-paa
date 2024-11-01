#include "kit-config.h"

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DE MATRIZES
--------------------------------------------------------------------------------*/

Matriz* alocaMatriz(int linhas, int colunas){

    Matriz* matriz = malloc(sizeof(Matriz));

    matriz->li = linhas;
    matriz->co = colunas;

    matriz->dados = malloc(linhas*sizeof(int*));
    for(int i = 0; i < linhas; i++){
        matriz->dados[i] = (int*)malloc(colunas*sizeof(int));
    }

    inicializaMatriz(matriz);
    return matriz;

}

void inicializaMatriz(Matriz* matriz){

    for(int i = 0; i < matriz->li; i++){
        for(int j = 0; j < matriz->co; j++){
            matriz->dados[i][j] = 0;
        }
    }

}

void desalocaMatriz(Matriz* matriz){

    for(int i = 0; i < matriz->li; i++){
        free(matriz->dados[i]);
    }
    free(matriz->dados);
    free(matriz);

}

void imprimeMatriz(Matriz* matriz){

    for(int i = 0; i < matriz->li; i++){
        for(int j = 0; j < matriz->co; j++){
            printf("%d\t", matriz->dados[i][j]);
        }
        printf("\n");
    }

}

/*--------------------------------------------------------------------------------
MÉTODOS PARA VERIFICAÇÂO DA COMPOSIÇÃO
--------------------------------------------------------------------------------*/

int verificaComposicao(Matriz* composicao){

    int somatorio = 0;
    int flags[4] = {0, 0, 0, 0};
    //flags = {Am, Az, Vd, Vm}

    int index;

    for(int i = 0; i < composicao->li; i++){

        somatorio += composicao->dados[i][0];

        index = composicao->dados[i][2];

        if(!flags[index])
            flags[index] = 1;

    }    

    if(somatorio > 36)
        return -1;

    for(int i = 0; i < 3; i++){
        if(!flags[i])
            return 0;
    }

    return 1;

}

/*--------------------------------------------------------------------------------
MÉTODOS PARA VERIFICAÇÂO DA CONFIGURAÇÃO
--------------------------------------------------------------------------------*/

Matriz* mapeiaConfiguracao(Matriz* config){

    Matriz* mapa = alocaMatriz(6, 6);

    int orientacao;
    //0(horizontal), 1(vertical)

    for(int i = 0; i < config->li; i++){

        if(config->dados[i][0] != config->dados[i][2])
            orientacao = 0;

        else
            orientacao = 1;

        if(orientacao == 0){

            for(int j = config->dados[i][0]-1; j < config->dados[i][2]-1; j++){
                mapa->dados[config->dados[i][1]][]
            }

        }

    }

}

int verificaConfiguracao(Matriz* config){

    int orientacao;
    //0(horizontal), 1(vertical)

    for(int i = 0; i < config->li; i++){

        if(config->dados[i][0] != config->dados[i][2])
            orientacao = 0;

        else
            orientacao = 1;

        if(orientacao == 0){

            if(config->dados[i][0] != 1){

                config->

            }

        }

    }

}

int emparelhadoCompConfig(Matriz* comp, Matriz* config){

    int index;
    Matriz copiaComp = *comp;

    for(int i = 0; i < config->li; i++){

        index = (config->dados[i][5] * 3) + (config->dados[i][4] % 3);
        copiaComp.dados[index][0]--;

    }

    for(int i = 0; i < copiaComp.li; i++){
        if(copiaComp.dados[i][0] != 0)
            return 0;
    }

    return 1;

}