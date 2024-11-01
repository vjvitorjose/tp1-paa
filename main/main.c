#include <stdio.h>
#include <unistd.h>

#include "in-out.h"
#include "kit-config.h"

int main(int argc, char *argv[]){

    Matriz* matriz = alocaMatriz(12, 3);

    for(int i = 0; i < matriz->li; i++){
        for(int j = 0; j < matriz->co; j++){
            matriz->dados[i][j] = j;
        }
    }

    imprimeMatriz(matriz);
    desalocaMatriz(matriz);

    return 0;

}