#include "in-out.h"

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DE ARQUIVOS
--------------------------------------------------------------------------------*/

FILE* abrirArquivo(char* caminho){

    FILE* file = fopen(caminho, "r");

    if(file == NULL)
        perror("Erro ao abrir o arquivo");

    return file;

}

void fecharArquivo(FILE* file){
    fclose(file);
}

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DA COMPOSIÇÃO
--------------------------------------------------------------------------------*/

Matriz* leituraComposicao(char* optarg){

    FILE* file = abrirArquivo(optarg);

    Matriz* matriz = alocaMatriz(12, 3);

    char buffer[8];

    int index, qtd, tam, corInt;
    char corStr[3];

    while(fscanf(file, "%d %d %2s", &qtd, &tam, corStr) == 3){

        if(strcmp(corStr, "Am") == 0){
            corInt = 0;
        } 
        else if(strcmp(corStr, "Az") == 0){
            corInt = 1;
        } 
        else if(strcmp(corStr, "Vd") == 0){
            corInt = 2;
        } 
        else if(strcmp(corStr, "Vm") == 0){
            corInt = 3;
        }

        index = (corInt * 3) + (tam % 3);

        matriz->dados[index][0] = qtd;
        matriz->dados[index][1] = tam;
        matriz->dados[index][2] = corInt;

    }

    fecharArquivo(file);

    return matriz;

}

Matriz* leituraConfiguracao(char* optarg){

    FILE* file = abrirArquivo(optarg);

    Matriz* configuracao = alocaMatriz(1, 6);

    char corStr[3];
    int x0, y0, x1, y1, tam, corInt;

    fscanf(file, "%d %d %d %d %d %2s", &x0, &y0, &x1, &y1, &tam, corStr);

    while(1){

        if(strcmp(corStr, "Am") == 0){
            corInt = 0;
        } 
        else if(strcmp(corStr, "Az") == 0){
            corInt = 1;
        } 
        else if(strcmp(corStr, "Vd") == 0){
            corInt = 2;
        } 
        else if(strcmp(corStr, "Vm") == 0){
            corInt = 3;
        }

        configuracao->dados[configuracao->li - 1][0] = x0;
        configuracao->dados[configuracao->li - 1][1] = y0;
        configuracao->dados[configuracao->li - 1][2] = x1;
        configuracao->dados[configuracao->li - 1][3] = y1;
        configuracao->dados[configuracao->li - 1][4] = tam;
        configuracao->dados[configuracao->li - 1][5] = corInt;

        if((fscanf(file, "%d %d %d %d %d %2s", &x0, &y0, &x1, &y1, &tam, corStr) != 6))
            break;
        
        adicionarLinha(configuracao);

    }

    fecharArquivo(file);

    return configuracao;

}