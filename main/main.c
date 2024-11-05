#include "in-out.h"
#include "kit-config.h"

int main(int argc, char** argv){

    int opt, resultado;
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

                resultado = verificaComposicao(composicao);

                if(resultado == -2){
                    printf("Composição falha: Essa composição não cabe no kit.\n");
                    break;
                }

                else if(resultado == -1){
                    printf("Composição falha: O kit possui espaços vazios.\n");
                    break;
                }

                else if(resultado == 1){
                    printf("Composição falha: O kit não possui todas as cores.");
                    break;
                }

                else if(!resultado){
                    printf("Composição Ok.\n");
                    continue;
                }

                else{
                    printf("Resultado inesperado, execução interrompida.\n");
                    return 0;
                }

            case 'b':

                configuracao = leituraConfiguracao(optarg);

                if(configuracao == NULL){
                    perror("Erro ao alocar configuração");
                    break;
                }

                verificaConfiguracao(configuracao);
                break;

            default:

                printf("Opção inválida.\n");
                return 0;

        }

    }

    return 0;

}