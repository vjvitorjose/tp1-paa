#include "in-out.h"

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DE ARQUIVOS
--------------------------------------------------------------------------------*/

FILE* abrirArquivo(char* caminho){

    FILE* file = malloc(sizeof(FILE));
    file = fopen(caminho, "r");
    return file;

}

void fecharArquivo(FILE* file){
    fclose(file);
}

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DE MATRIZES
--------------------------------------------------------------------------------*/

int** alocaMatriz(int linhas, int colunas){

    int** matriz = malloc(linhas*sizeof(int*));
    for(int i = 0; i < linhas; i++){
        matriz[i] = (int*)malloc(colunas*sizeof(int));
    }

    return matriz;

}

void desalocaMatriz(int** matriz, int linhas){

    for(int i = 0; i < linhas; i++){
        free(matriz[i]);
    }
    free(matriz);

}

/*--------------------------------------------------------------------------------
MÉTODO PRINCIPAL
--------------------------------------------------------------------------------*/

void leituraArquivo(int argc, char** argv){

    int opt = getopt(argc, argv, "a:b:");

    while(opt != -1){

        switch(opt){
            case 'a':
                setComposicao(optarg);
                break;

            case 'b':
                printf("%s\n", optarg);
                break;
        }

        opt = getopt(argc, argv, "a:b:");

    }

}

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DA COMPOSIÇÃO
--------------------------------------------------------------------------------*/

int** setComposicao(char* optarg){

    FILE* file = abrirArquivo(optarg);
    int** matriz = alocaMatriz(12, 3);

    char* buffer = malloc(sizeof(char));

    int cor;

    while(fgets(buffer, sizeof(buffer), file)){
        
        for(int j = 0; j < 7; j++){
            printf("%c", buffer[j]);
        }

        printf("%d\n", buffer[3]+buffer[4]);
        
        cor = (int)buffer[3] + (int)buffer[4];
        //Am(174), Az(187), Vd(186), Vm(195)

        matriz[][0] = (int)buffer[0];
        matriz[][1] = (int)buffer[2];
        matriz[][2] = cor;

    }

    free(buffer);

    desalocaMatriz(matriz, 12);
    fecharArquivo(file);

}

void main(int argc, char** argv){

    setComposicao("/home/vitorvsgp/vitorvsgp/Área de Trabalho/tp1-paa/main/Composicao.txt");

    return;

}