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
            matriz->dados[i][j] = -1;
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

void adicionarLinha(Matriz *matriz) {

    int **temp = realloc(matriz->dados, (matriz->li+1) * sizeof(int*));

    matriz->dados = temp;

    matriz->dados[matriz->li] = malloc(matriz->co * sizeof(int));

    for(int i = 0; i < matriz->co; i++) {
        matriz->dados[matriz->li][i] = 0;
    }

    matriz->li++;

}

Matriz* copiaMatriz(Matriz* origem){

    Matriz* copia = alocaMatriz(origem->li, origem->co);

    for(int i = 0; i < copia->li; i++){
        for(int j = 0; j < copia->co; j++){
            copia->dados[i][j] = origem->dados[i][j];
        }
    }

    return copia;

}

Configuracao* criaConfiguracao(){

    Configuracao* config = malloc(sizeof(Configuracao));

    config->matriz = alocaMatriz(1, 6);
    config->qtd = 1;

    return config;

}

void desalocaConfiguracao(Configuracao* config){

    for(int i = 0; i < config->qtd; i++){
        desalocaMatriz(&(config->matriz[i]));
    }

    free(config->matriz);

}

void acrescentarMatriz(Configuracao* config) {

    Matriz* novo_matrizes = (Matriz*)realloc(config->matriz, (config->qtd+1) * sizeof(Matriz));

    config->matriz = novo_matrizes;

    Matriz* temp = alocaMatriz(1, 6);
    config->matriz[config->qtd] = *temp;
    desalocaMatriz(temp);

    config->qtd++;

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

            if(composicao->dados[i][0] > 0){

                somatorio += composicao->dados[i][0];

                index = composicao->dados[i][2];

                if(!flags[index])
                    flags[index] = 1;

            }

    }    

    if(somatorio > 36)
        return 0;

    for(int i = 0; i < 4; i++){
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
            for(int j = config->dados[i][0]-1; j < config->dados[i][2]; j++){ //for para percorrer de x0 ate x1

                mapa->dados[config->dados[i][1]-1][j] = config->dados[i][5];
            
            }

        }

        //a bomba daquela linha está na vertical
        else if(config->dados[i][1] != config->dados[i][3]){

            //preenche o mapa na coluna x0, da linha y0 ate y1;
            for(int j = config->dados[i][1]-1; j < config->dados[i][3]; j++){

                mapa->dados[j][config->dados[i][0]-1] = config->dados[i][5];

            }

        }

        //a bomba tem 1 de tamanho
        else{
            mapa->dados[config->dados[i][1]-1][config->dados[i][0]-1] = config->dados[i][5];
        }

    }

    return mapa;

}

int estaNoTeto(int* bomba){

    if(bomba[1] == 1)
        return 1;

    return 0;

}

int estaNoChao(int* bomba){

    if(bomba[3] == 6)
        return 1;

    return 0;

}

int estaNaParedeEsquerda(int* bomba){

    if(bomba[0] == 1)
        return 1;

    return 0;

}

int estaNaParedeDireita(int* bomba){

    if(bomba[2] == 6)
        return 1;

    return 0;

}

int verificaVizinhosDireita(int* bomba, Matriz* mapa){
    
    //percorrendo ele verticalmente
    for(int i = bomba[1]-1; i < bomba[3]; i++){
        if(mapa->dados[i][bomba[2]] == bomba[5])
            return 0;
    }

    return 1;

}

void imprimeBomba(int* bomba, int i){

    for(int j = 0; j < i; j++){
        printf("%d ", bomba[j]);
    }
    printf("\n");

}

int verificaVizinhosEsquerda(int* bomba, Matriz* mapa){
    
    //percorrendo ele verticalmente
    for(int i = bomba[1]-1; i < bomba[3]; i++){
        if(mapa->dados[i][bomba[0]-2] == bomba[5]){
            return 0;
        }
    }

    return 1;

}

int verificaVizinhosBaixo(int* bomba, Matriz* mapa){
    
    //percorrendo ele horizontalmente
    for(int i = bomba[0]-1; i < bomba[2]; i++){
        if(mapa->dados[bomba[3]][i] == bomba[5])
            return 0;
    }

    return 1;

}

int verificaVizinhosCima(int* bomba, Matriz* mapa){
    
    //percorrendo ele horizontalmente
    for(int i = bomba[0]-1; i < bomba[2]; i++){
        if(mapa->dados[bomba[1]-2][i] == bomba[5])
            return 0;
    }

    return 1;

}

int verificaConfiguracao(Matriz* config, Matriz* comp){

    if(!emparelhadoCompConfig(comp, config))
        return 0;

    //cria um mapa com as cores daquela configuração para facilitar a verificação
    Matriz* mapa = mapeiaConfiguracao(config);

    //percorre todas as linhas da configuração
    for(int i = 0; i < config->li; i++){

        //bomba na horizontal
        if(config->dados[i][0] != config->dados[i][2]){

            if(estaNoTeto(config->dados[i])){

                if(!verificaVizinhosBaixo(config->dados[i], mapa))
                    return 0;

                if(estaNaParedeEsquerda(config->dados[i])){

                    if(!verificaVizinhosDireita(config->dados[i], mapa))
                        return 0;

                }

                else if(estaNaParedeDireita(config->dados[i])){

                    if(!verificaVizinhosEsquerda(config->dados[i], mapa))
                        return 0;

                }

                else{

                    if(!verificaVizinhosDireita(config->dados[i], mapa) || !verificaVizinhosEsquerda(config->dados[i], mapa))
                        return 0;

                }

            }


            else if(estaNoChao(config->dados[i])){

                if(!verificaVizinhosCima(config->dados[i], mapa))
                    return 0;

                if(estaNaParedeEsquerda(config->dados[i])){

                    if(!verificaVizinhosDireita(config->dados[i], mapa))
                        return 0;

                }

                else if(estaNaParedeDireita(config->dados[i])){

                    if(!verificaVizinhosEsquerda(config->dados[i], mapa))
                        return 0;

                }

                else{

                    if(!verificaVizinhosEsquerda(config->dados[i], mapa) || !verificaVizinhosDireita(config->dados[i], mapa))
                        return 0;

                }

            }

            else{

                if(!verificaVizinhosCima(config->dados[i], mapa) || !verificaVizinhosBaixo(config->dados[i], mapa))
                    return 0;

                if(estaNaParedeDireita(config->dados[i])){

                    if(!verificaVizinhosEsquerda(config->dados[i], mapa))
                        return 0;

                }

                else if(estaNaParedeEsquerda(config->dados[i])){

                    if(!verificaVizinhosDireita(config->dados[i], mapa))
                        return 0;

                }

                else{

                    if(!verificaVizinhosEsquerda(config->dados[i], mapa) || !verificaVizinhosDireita(config->dados[i], mapa))
                        return 0;

                }

            }

        }

        //bomba na vertical
        else{

            if(estaNaParedeEsquerda(config->dados[i])){

                if(!verificaVizinhosDireita(config->dados[i], mapa))
                    return 0;

                if(estaNoTeto(config->dados[i])){

                    if(!verificaVizinhosBaixo(config->dados[i], mapa))
                        return 0;

                }

                else if(estaNoChao(config->dados[i])){

                    if(!verificaVizinhosCima(config->dados[i], mapa))
                        return 0;

                }

                else{

                    if(!verificaVizinhosCima(config->dados[i], mapa) || !verificaVizinhosBaixo(config->dados[i], mapa))
                        return 0;

                }

            }

            else if(estaNaParedeDireita(config->dados[i])){

                if(!verificaVizinhosEsquerda(config->dados[i], mapa))
                    return 0;

                if(estaNoTeto(config->dados[i])){

                    if(!verificaVizinhosBaixo(config->dados[i], mapa))
                        return 0;

                }

                else if(estaNoChao(config->dados[i])){

                    if(!verificaVizinhosCima(config->dados[i], mapa))
                        return 0;

                }

                else{

                    if(!verificaVizinhosCima(config->dados[i], mapa) || !verificaVizinhosBaixo(config->dados[i], mapa))
                        return 0;

                }

            }

            else{

                if(estaNoTeto(config->dados[i])){

                    if(!verificaVizinhosBaixo(config->dados[i], mapa) || !verificaVizinhosEsquerda(config->dados[i], mapa) 
                            || !verificaVizinhosDireita(config->dados[i], mapa))
                        return 0;

                }

                else if(estaNoChao(config->dados[i])){

                    if(!verificaVizinhosCima(config->dados[i], mapa) || !verificaVizinhosEsquerda(config->dados[i], mapa) 
                            || !verificaVizinhosDireita(config->dados[i], mapa))
                        return 0;

                }

                else{

                    if(!verificaVizinhosEsquerda(config->dados[i], mapa) || !verificaVizinhosDireita(config->dados[i], mapa) 
                            || !verificaVizinhosCima(config->dados[i], mapa) || !verificaVizinhosBaixo(config->dados[i], mapa))
                        return 0;

                }

            }

        }

    }

    return 1;

}

int emparelhadoCompConfig(Matriz* comp, Matriz* config){

    int index;
    Matriz* copiaComp = copiaMatriz(comp);

    for(int i = 0; i < config->li; i++){

        index = (config->dados[i][5] * 3) + (config->dados[i][4] % 3);
        copiaComp->dados[index][0] = 0;

    }

    for(int i = 0; i < config->li; i++){

        index = (config->dados[i][5] * 3) + (config->dados[i][4] % 3);
        copiaComp->dados[index][0]++;

    }

    for(int i = 0; i < copiaComp->li; i++){
        if(copiaComp->dados[i][0] != comp->dados[i][0])
            return 0;
    }

    return 1;

}