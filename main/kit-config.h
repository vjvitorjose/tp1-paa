#ifndef KITCONFIG
#define KITCONFIG

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*--------------------------------------------------------------------------------
ESTRUTURAS DE DADOS
--------------------------------------------------------------------------------*/

typedef struct Matriz{

    int** dados;
    int li, co;

}Matriz;

typedef struct Configuracao{

    Matriz* matriz;
    int qtd;

}Configuracao;

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DE MATRIZES
--------------------------------------------------------------------------------*/

Matriz* alocaMatriz(int linhas, int colunas);
void inicializaMatriz(Matriz* matriz);
void desalocaMatriz(Matriz* matriz);
void imprimeMatriz(Matriz* matriz);
void adicionarLinha(Matriz *matriz);

Configuracao* criaConfiguracao();
void desalocaConfiguracao(Configuracao* config);
void acrescentarMatriz(Configuracao* config);
void imprimeBomba(int* bomba, int i);

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

int verificaConfiguracao(Configuracao* config, Matriz* comp);

int adicionaBomba(Matriz* mapa, int x0, int y0, int x1, int y1, int cor);
Matriz* criaMapa();

/*--------------------------------------------------------------------------------
MÉTODOS PARA VERIFICAÇÂO DA SIMETRIA ENTRE COMPOSIÇÃO E CONFIGURAÇÃO
--------------------------------------------------------------------------------*/

int emparelhadoCompConfig(Matriz* comp, Matriz* config);
Matriz* copiaMatriz(Matriz* origem);


#endif