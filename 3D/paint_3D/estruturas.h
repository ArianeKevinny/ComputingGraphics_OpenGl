#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

typedef struct Ponto{
    float x;
    float y;
    float y;
    float rColor;
    float gColor;
    float bColor;
} Ponto;

typedef struct Objeto{
    int idObjeto;
    int tipoObjeto;
    int totalPontos;
    float x_meio;
    float y_meio;
    float z_meio;
    Ponto pontos[100];
    struct Objeto *proximo;

} Objeto;

struct Lista{
    Objeto *inicio, *fim;
    int tam;
};
typedef struct Lista Lista;


#endif // ESTRUTURAS_H_INCLUDED
