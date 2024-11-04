#include <stdio.h>
#include <unistd.h>

#include "in-out.h"
#include "kit-config.h"

int main(int argc, char** argv){

    int opt;
    Matriz* composicao;
    Matriz* configuracao;

    while((opt = getopt(argc, argv, "a:b:")) != -1){

        switch(opt){

            case 'a':

                composicao = leituraComposicao(optarg);

                if(!verificaComposicao(composicao)){
                    printf("composicao falha\n");
                    break;
                }

                printf("composicao ok\n");
                break;

            case 'b':

                configuracao = leituraConfiguracao(optarg);
                imprimeMatriz(configuracao);

                if(!verificaConfiguracao(configuracao, composicao)){
                    printf("explode\n");
                    break;
                }

                printf("configuracao ok\n");
                break;

        }

    }

    return 0;

}