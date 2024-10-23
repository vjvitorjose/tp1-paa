#ifndef IO
#define IO

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DE ARQUIVOS
--------------------------------------------------------------------------------*/

FILE* abrirArquivo(char* caminho);
void fecharArquivo(FILE* file);

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DE MATRIZES
--------------------------------------------------------------------------------*/

int** alocaMatriz(int linhas, int colunas);
void desalocaMatriz(int** matriz, int linhas);

/*--------------------------------------------------------------------------------
MÉTODO PRINCIPAL
--------------------------------------------------------------------------------*/

void leituraArquivo(int argc, char** argv);

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DA COMPOSIÇÃO
--------------------------------------------------------------------------------*/

int** setComposicao(char* optarg);

#endif