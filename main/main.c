#include <stdio.h>
#include <unistd.h>

#include "in-out.h"
#include "kit-config.h"

int main(int argc, char *argv[]){

    int opt = getOpt(argc, argv);

    printf("%d\n", opt);
    printf("%s", optarg);

    return 0;

}