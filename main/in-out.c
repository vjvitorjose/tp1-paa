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

Configuracao* leituraConfiguracao(char* optarg){

    FILE* file = abrirArquivo(optarg);

    Configuracao* configuracao = criaConfiguracao();

    Matriz* mapa = criaMapa();

    int cor;

    int x0, y0, x1, y1, tam;

    char buffer[13];

    fgets(buffer, sizeof(buffer), file);

    while(1){

        while(1){

            if(buffer[0] == '\n')
                break;

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

            if(!adicionaBomba(mapa, buffer[0]-'0', buffer[2]-'0', buffer[4]-'0', buffer[6]-'0', cor)){
                printf("Bombas sobrepostas\n");
                return NULL;
            }

            for(int i = 0; i < 5; i++){
                configuracao->matriz[configuracao->qtd-1].dados[configuracao->matriz[configuracao->qtd-1].li-1][i] = buffer[i*2] - '0';
            }

            configuracao->matriz[configuracao->qtd-1].dados[configuracao->matriz[configuracao->qtd-1].li-1][5] = cor;

            if(fgets(buffer, sizeof(buffer), file) && buffer[0] != '\n')
                adicionarLinha(&configuracao->matriz[configuracao->qtd-1]);

            else 
                break;

        }

        if(feof(file))
            break;

        acrescentarMatriz(configuracao);
        fgets(buffer, sizeof(buffer), file);

    }

    fecharArquivo(file);

    return configuracao;

}