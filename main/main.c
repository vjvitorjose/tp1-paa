#include "in-out.h"
#include "kit-config.h"

int main(int argc, char** argv){

    int opt;
    Matriz* composicao;
    Configuracao* configuracao;

    while((opt = getopt(argc, argv, "a:b:")) != -1){

        switch(opt){

            case 'a':

                composicao = leituraComposicao(optarg);

                if(composicao == NULL){
                    perror("Erro ao alocar a composição");
                    return 0;
                }

                verificaComposicao(composicao);

            case 'b':

                configuracao = leituraConfiguracao(optarg);

                if(configuracao == NULL){
                    perror("Erro ao alocar configuração");
                    break;
                }

                verificaConfiguracao(configuracao, composicao);
                break;

            default:

                printf("Opção inválida.\n");
                return 0;

        }

    }

    return 0;

}