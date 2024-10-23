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

    int opt;

    do{

        opt = getopt(argc, argv, "a:b:");

        switch(opt){
            case 'a':
                setComposicao(optarg);
        }

    }while(opt != -1);

}

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DA COMPOSIÇÃO
--------------------------------------------------------------------------------*/

int** setComposicao(char* optarg){

    FILE* file = abrirArquivo(optarg);
    int** matriz = alocaMatriz(12, 3);

    char* buffer = malloc(5*sizeof(char));

    int i = 0;

    do{

        fgets(buffer, 5, file);

        matriz[i][0] = buffer[0] - '0';
        matriz[i][1] = buffer[2] - '0';

        switch(buffer[3]){

            case 'A':

                switch(buffer[4]){

                    case 'z':
                        matriz[i][3] = 1;
                        break;

                    case 'm':
                        matriz[i][3] = 2;
                        break;
                
                }

            case 'V':

                switch(buffer[4]){

                    case 'm':
                        matriz[i][3] = 3;
                        break;

                    case 'd':
                        matriz[i][3] = 4;
                        break;

                }

        }

        i++;

    }while(buffer != NULL);

    free(buffer);

    desalocaMatriz(matriz, 12);
    fecharArquivo(file);

}

void main(int argc, char** argv){

    leituraArquivo(argc, argv);

    return;

}