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

    for(int i = 0; i < config->li; i++){ //percorre todas as linhas da matriz de configuração

        //quando encontrar uma bomba disposta na horizontal:
        if(config->dados[i][0] != config->dados[i][2]){

            //preenche o mapa na linha y0, coluna x0 ate x1
            for(int j = config->dados[i][0]-1; j < config->dados[i][2]-1; j++){ //for para percorrer de x0 ate x1

                mapa->dados[config->dados[i][1]][j] = config->dados[i][5];
            
            }

        }

        //se nao estiver na horizontal, a bomba daquela linha está na vertical
        else{

            //preenche o mapa na coluna x0, da linha y0 ate y1;
            for(int j = config->dados[i][1]; j < config->dados[i][3]; j++){

                mapa->dados[j][config->dados[i][0]] = config->dados[i][5];

            }

        }

    }

    return mapa;

}

int verificaConfiguracao(Matriz* config){

    //cria um mapa com as cores daquela configuração para facilitar a verificação
    Matriz* mapa = mapeiaConfiguracao(config);

    //percorre todas as linhas da configuração
    for(int i = 0; i < config->li; i++){

        //bomba na horizontal
        if(config->dados[i][0] != config->dados[i][2]){

            //a bomba esta encostada no teto
            if(config->dados[i][1] == 1){

                //a bomba esta encostada no teto e na parede esquerda
                if(config->dados[i][0] == 1){

                    //o vizinho a direita da bomba no mapa tem o mesmo código de cor
                    if(mapa->dados[config->dados[i][1]-1][config->dados[i][2]] == config->dados[i][5])
                        return 0;

                    //percorre os vizinhos de baixo no mapa para ver se algum tem o mesmo código de cor
                    for(int j = config->dados[i][0]; j < config->dados[i][2]; j++){
                        if(mapa->dados[config->dados[i][1]][j] == config->dados[i][5])
                            return 0;
                    }

                }

                //a bomba esta encostada no teto e na parede direita
                else if(config->dados[i][2] == 6){

                    //o vizinho a esquerda da bomba no mapa tem o mesmo código de cor
                    if(mapa->dados[config->dados[i][1]-1][config->dados[i][0]] == config->dados[i][5])
                        return 0;

                    //percorre os vizinhos de baixo no mapa para ver se algum tem o mesmo código de cor
                    for(int j = config->dados[i][0]; j < config->dados[i][2]; j++){
                        if(mapa->dados[config->dados[i][1]][j] == config->dados[i][5])
                            return 0;
                    }

                }

            }


            //a bomba esta encostada no chão
            if(config->dados[i][1] == 6){

                //a bomba esta encostada no chão e na parede esquerda
                if(config->dados[i][0] == 1){

                    //o vizinho a direita da bomba no mapa tem o mesmo código de cor
                    if(mapa->dados[config->dados[i][1]-1][config->dados[i][2]] == config->dados[i][5])
                        return 0;

                    //percorre os vizinhos de baixo no mapa para ver se algum tem o mesmo código de cor
                    for(int j = config->dados[i][0]; j < config->dados[i][2]; j++){
                        if(mapa->dados[config->dados[i][1]][j] == config->dados[i][5])
                            return 0;
                    }

                }

                //a bomba esta encostada no chão e na parede direita
                else if(config->dados[i][2] == 6){

                    //o vizinho a esquerda da bomba no mapa tem o mesmo código de cor
                    if(mapa->dados[config->dados[i][1]-1][config->dados[i][0]] == config->dados[i][5])
                        return 0;

                    //percorre os vizinhos de baixo no mapa para ver se algum tem o mesmo código de cor
                    for(int j = config->dados[i][0]; j < config->dados[i][2]; j++){
                        if(mapa->dados[config->dados[i][1]][j] == config->dados[i][5])
                            return 0;
                    }

                }

            }

        }

        //bomba na vertical
        else{

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