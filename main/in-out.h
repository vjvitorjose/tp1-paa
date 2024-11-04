#ifndef IO
#define IO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "kit-config.h"

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DE ARQUIVOS
--------------------------------------------------------------------------------*/

FILE* abrirArquivo(char* caminho);
void fecharArquivo(FILE* file);

/*--------------------------------------------------------------------------------
MÉTODOS PARA TRATAMENTO DA COMPOSIÇÃO
--------------------------------------------------------------------------------*/

Matriz* leituraComposicao(char* optarg);

Configuracao* leituraConfiguracao(char* optarg);

#endif