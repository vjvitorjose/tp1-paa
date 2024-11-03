#ifndef KITCONFIG
#define KITCONFIG

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Matriz{

    int** dados;
    int li, co;

}Matriz;

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DE MATRIZES
--------------------------------------------------------------------------------*/

Matriz* alocaMatriz(int linhas, int colunas);
void inicializaMatriz(Matriz* matriz);
void desalocaMatriz(Matriz* matriz);
void imprimeMatriz(Matriz* matriz);
void adicionarLinha(Matriz *matriz);

/*--------------------------------------------------------------------------------
MÉTODOS PARA VERIFICAÇÂO DA COMPOSIÇÃO
--------------------------------------------------------------------------------*/

int verificaComposicao(Matriz* composicao);

/*--------------------------------------------------------------------------------
MÉTODOS PARA VERIFICAÇÂO DA CONFIGURAÇÃO
--------------------------------------------------------------------------------*/

Matriz* mapeiaConfiguracao(Matriz* config);

//VERIFICAÇÃO DA POSIÇÃO DE UMA BOMBA

int estaNoTeto(int* bomba);
int estaNoChao(int* bomba);
int estaNaParedeEsquerda(int* bomba);
int estaNaParedeDireita(int* bomba);

//VERIFICAÇÃO DOS VIZINHOS DE UMA BOMBA

int verificaVizinhosDireita(int* bomba, Matriz* mapa);
int verificaVizinhosEsquerda(int* bomba, Matriz* mapa);
int verificaVizinhosBaixo(int* bomba, Matriz* mapa);
int verificaVizinhosCima(int* bomba, Matriz* mapa);

int verificaConfiguracao(Matriz* config);

/*--------------------------------------------------------------------------------
MÉTODOS PARA VERIFICAÇÂO DA SIMETRIA ENTRE COMPOSIÇÃO E CONFIGURAÇÃO
--------------------------------------------------------------------------------*/

int emparelhadoCompConfig(Matriz* comp, Matriz* config);


#endif