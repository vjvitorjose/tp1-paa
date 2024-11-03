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

    int cor, index, qtd, tam;

    while(fgets(buffer, sizeof(buffer), file)){
        
        cor = (int)buffer[3] + (int)buffer[4];
        //Am(174), Az(187), Vd(186), Vm(195)

        switch(cor){
            case 174:
                cor = 0;
                break;
            case 187:
                cor = 1;
                break;
            case 186:
                cor = 2;
                break;
            case 195:
                cor = 3;
                break;
        }

        qtd = buffer[0] - '0';
        tam = buffer[2] - '0';
        index = (cor * 3) + (tam % 3);

        matriz->dados[index][0] = qtd;
        matriz->dados[index][1] = tam;
        matriz->dados[index][2] = cor;

    }

    fecharArquivo(file);

    return matriz;

}

Matriz* leituraConfiguracao(char* optarg){

    FILE* file = abrirArquivo(optarg);

    Matriz* configuracao = alocaMatriz(1, 6);

    int cor, i = 0;

    char buffer[13];

    fgets(buffer, sizeof(buffer), file);

    while(1){

        cor = (int)buffer[9] + (int)buffer[10];
        //Am(174), Az(187), Vd(186), Vm(195)

        switch(cor){
            case 174:
                cor = 0;
                break;
            case 187:
                cor = 1;
                break;
            case 186:
                cor = 2;
                break;
            case 195:
                cor = 3;
                break;
        }

        for(int i = 0; i < 5; i++){
            configuracao->dados[configuracao->li-1][i] = buffer[i*2] - '0';
        }

        configuracao->dados[configuracao->li-1][5] = cor;

        if(fgets(buffer, sizeof(buffer), file))
            adicionarLinha(configuracao);

        else 
            break;

    }

    fecharArquivo(file);

    return configuracao;

}