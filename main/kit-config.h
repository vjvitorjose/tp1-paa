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

#endif