#ifndef KITCONFIG
#define KITCONFIG

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DE MATRIZES
--------------------------------------------------------------------------------*/

int** alocaMatriz(int linhas, int colunas);
void inicializaMatriz(int** matriz, int linhas, int colunas);
void desalocaMatriz(int** matriz, int linhas);
void imprimeMatriz(int** matriz, int linhas, int colunas);

#endif