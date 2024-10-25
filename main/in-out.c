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
MÉTODO PRINCIPAL
--------------------------------------------------------------------------------*/

void leituraArquivo(int argc, char** argv, int** composicao, int*** configuracoes){

    int opt;

    while((opt = getopt(argc, argv, "a:b:")) != -1){

        switch(opt){

            case 'a':
                printf("entrou no case a");
                leituraComposicao(optarg, composicao);
                break;

            case 'b':
                // setConfiguracoes(optarg, configuracoes);
                break;
        }

    }

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

void main(int argc, char** argv){

    int** composicao = alocaMatriz(12, 3);
    int*** configuracao = NULL;

    leituraArquivo(argc, argv, composicao, configuracao);

    imprimeMatriz(composicao, 12, 3);

    desalocaMatriz(composicao, 12);

    return;

}