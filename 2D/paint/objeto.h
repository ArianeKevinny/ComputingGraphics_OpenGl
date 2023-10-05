#ifndef __OBJETO_H_
#define __OBJETO_H_
#include "estruturas.h"

void calculaCentroide(Objeto *objeto);

void remover(Lista *lista, Objeto *objeto);

void inserirFim(Lista *lista, int idObjeto, int tipoObjeto, int totalPontos, Ponto *pontos);

void transladaObjeto(Objeto *objeto, float tx, float ty);

void rotacionaObjeto(Objeto *objeto, float teta);

void escalaObjeto(Objeto *objeto, float sx, float sy);

int pickPoligono(Objeto *poligono, float mx, float my, float t);

typedef struct Regioes Regioes;

Regioes computaRegioes(float px, float py, float xmin, float xmax, float ymin, float ymax);

int pickLinha(float x0, float y0, float x1, float y1, float mx, float my, float t);

int pickPonto(float px, float py, float mx, float my, float t);

Objeto *selecionaObjeto(Lista *lista, float mx, float my);


#endif // __OBJETO_H_
