#ifndef IO
#define IO

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "kit-config.h"

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DE ARQUIVOS
--------------------------------------------------------------------------------*/

FILE* abrirArquivo(char* caminho);
void fecharArquivo(FILE* file);

/*--------------------------------------------------------------------------------
MÉTODO PRINCIPAL
--------------------------------------------------------------------------------*/

void leituraArquivo(int argc, char** argv, int** comp);
int getOpt(int argc, char** argv);

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DA COMPOSIÇÃO
--------------------------------------------------------------------------------*/

int** leituraComposicao(char* optarg, int** matriz);

#endif