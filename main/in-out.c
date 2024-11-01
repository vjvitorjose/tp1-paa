#include "in-out.h"

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DE ARQUIVOS
--------------------------------------------------------------------------------*/

FILE* abrirArquivo(char* caminho){

    FILE* file = fopen(caminho, "r");

    if(file == NULL)
        printf("ERRO: erro ao abrir o arquivo.\n");

    return file;

}

void fecharArquivo(FILE* file){
    fclose(file);
}

/*--------------------------------------------------------------------------------
MÉTODO PRINCIPAL
--------------------------------------------------------------------------------*/

int getOpt(int argc, char** argv){

    int opt = getopt(argc, argv, "a:b:");
    return opt; 

}

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DA COMPOSIÇÃO
--------------------------------------------------------------------------------*/

int** leituraComposicao(char* optarg, int** matriz){

    FILE* file = abrirArquivo(optarg);

    char* buffer = malloc(8*sizeof(char));

    int cor, index, qtd, tam;

    while(fgets(buffer, sizeof(buffer), file)){
        
        cor = (int)buffer[3] + (int)buffer[4];
        //Am(174), Az(187), Vd(186), Vm(195)

        switch(cor){
            case 174:
                cor = 0;
                break;
            case 187:
                cor = 3;
                break;
            case 186:
                cor = 6;
                break;
            case 195:
                cor = 9;
                break;
        }

        qtd = buffer[0] - '0';
        tam = buffer[2] - '0';
        index = cor + (tam % 3);

        matriz[index][0] = qtd;
        matriz[index][1] = tam;
        matriz[index][2] = cor;

    }

    free(buffer);
    fecharArquivo(file);

}

//_____________________________________________________________________________