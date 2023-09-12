#ifndef __OBJETO_H_
#define __OBJETO_H_

struct ponto{
    float x;
    float y;
    float rColor;
    float gColor;
    float bColor;
};
typedef struct ponto Ponto;


typedef struct Objeto{
    int idObjeto;
    int tipoObjeto;
    int totalPontos;
    Ponto pontos[100];
    struct Objeto *proximo;

} Objeto;

typedef struct {
    Objeto *inicio, *fim;
    int tam;
} Lista;


// remover um elemento da lista
void remover(Lista *lista, int idObjeto);

// inserir no final da lista
void inserirFim(Lista *lista,int idObjeto,int tipoObjeto, int totalPontos, Ponto pontos);



#endif // __OBJETO_H_
