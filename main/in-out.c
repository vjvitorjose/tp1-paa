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

    if(file == NULL)
        perror("Erro ao fechar o arquivo");

    fclose(file);

}

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DA COMPOSIÇÃO
--------------------------------------------------------------------------------*/

Matriz* leituraComposicao(char* optarg){

    FILE* file = abrirArquivo(optarg);

    if(file == NULL){
        perror("Erro ao abrir Composicao.txt");
        return NULL;
    }

    Matriz* matriz = alocaMatriz(12, 3);

    if(matriz == NULL){
        perror("Erro ao alocar matriz para composição");
        return NULL;
    }

    int index, qtd, tam, corInt;
    char corStr[3];

    while(fscanf(file, "%d %d%2s", &qtd, &tam, corStr) == 3){

        if(!strcmp(corStr, "Am")){
            corInt = 0;
        } 
        else if(!strcmp(corStr, "Az")){
            corInt = 1;
        } 
        else if(!strcmp(corStr, "Vd")){
            corInt = 2;
        } 
        else if(!strcmp(corStr, "Vm")){
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

    if(file == NULL){
        perror("Erro ao abrir Configuracoes.txt");
        return NULL;
    }

    Configuracao* configuracao = criaConfiguracao();

    if(configuracao == NULL){
        perror("Erro ao criar struct Composicao");
        fecharArquivo(file);
        return NULL;
    }

    Matriz* mapa = criaMapa();

    if(mapa == NULL){
        perror("Erro ao criar mapa");
        fecharArquivo(file);
        // desalocaConfiguracao(configuracao);
        return NULL;
    }

    int cor, x0, y0, x1, y1, tam, i = 1;
    char buffer[13];

    if(!fgets(buffer, sizeof(buffer), file)){
        perror("Erro ao ler a configuração");
    }

    while(1){

        printf("fora\n");

        while(1){

            printf("dentro\n");

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
                printf("Configuração %d inválida.\n", configuracao->qtd);
                desalocaMatriz(&configuracao->matriz[configuracao->qtd-1]);
                configuracao->qtd--;
                break;
            }

            for(int j = 0; j < 5; j++){
                configuracao->matriz[configuracao->qtd-1].dados[configuracao->matriz[configuracao->qtd-1].li-1][j] = buffer[j*2] - '0';
            }

            configuracao->matriz[configuracao->qtd-1].dados[configuracao->matriz[configuracao->qtd-1].li-1][5] = cor;

            if(fgets(buffer, sizeof(buffer), file) && buffer[0] != '\n')
                adicionarLinha(&configuracao->matriz[configuracao->qtd-1]);

            else 
                break;

        }

        if(feof(file))
            break;

        i++;
        inicializaMatriz(mapa);
        acrescentarMatriz(configuracao);
        fgets(buffer, sizeof(buffer), file);

    }

    fecharArquivo(file);
    desalocaMatriz(mapa);

    return configuracao;

}