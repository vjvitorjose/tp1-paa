#include "in-out.h"

#include <stdio.h>
#include <stdlib.h>

kitBoom configComposicao(){

    kitBoom *kit = malloc(sizeof(kitBoom));

}

void configInOut(int argc, char *argv){

    int opt;
    do{
        opt = getopt(argc, argv);

        switch(opt){
            case 'a':
                configComposicao();
                break;

            case 'b':
                configConfiguracao();
                break;  
        }

    }while(opt != -1);

}