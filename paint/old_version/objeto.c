#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "objeto.h"

// Criando as estruturas

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
void remover(Lista *lista, int idObjeto) {
    Objeto *inicio = lista->inicio; // ponteiro para o início da lista
    Objeto * noARemover = NULL; // ponteiro para o nó a ser removido

    if(inicio != NULL && lista->inicio->idObjeto == idObjeto) { // remover 1º elemento
        noARemover = lista->inicio;
        lista->inicio = noARemover->proximo;
        if(lista->inicio == NULL)
            lista->fim = NULL;
    } else { // remoção no meio ou no final
        while(inicio != NULL && inicio->proximo != NULL && inicio->proximo->idObjeto != idObjeto) {
            inicio = inicio->proximo;
        }
        if(inicio != NULL && inicio->proximo != NULL) {
            noARemover = inicio->proximo;
            inicio->proximo = noARemover->proximo;
            if(inicio->proximo == NULL) // se o último elemento for removido
                lista->fim = inicio;
        }
    }
    if(noARemover) {
        free(noARemover); // libera a memória do nó
        lista->tam--; // decrementa o tamanho da lista
    }
}

// inserir no final da lista

void inserirFim(Lista *lista,int idObjeto,int tipoObjeto, int totalPontos, Ponto pontos){
    Objeto *novo = (Objeto*)malloc(sizeof(Objeto)); // cria um novo nó
    novo->idObjeto = idObjeto;
    novo->tipoObjeto = tipoObjeto;
    novo->totalPontos = totalPontos;
    novo->pontos = pontos;
    novo->proximo = NULL;

    if(lista->inicio == NULL) { // lista vazia
        lista->inicio = novo;
        lista->fim = novo;
    } else { // lista não vazia
        lista->fim->proximo = novo;
        lista->fim = novo;
    }
    lista->tam++;
}



