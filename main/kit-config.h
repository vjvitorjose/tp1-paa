#ifndef KITCONFIG
#define KITCONFIG

typedef struct Bomba{

    int tam;
    int cor; //Am(1), Vm(2), Vd(3), Az(4)

} Bomba;

typedef struct kitBoom{

    Bomba *bombas;
    int *quantidades;

} kitBoom;

typedef struct coordenadas{

    int x0, x1;
    int y0, y1;

} coordenadas;

typedef struct configuracao{

    Bomba *bombas;
    coordenadas *coordenadas;

} configuracao;

#endif