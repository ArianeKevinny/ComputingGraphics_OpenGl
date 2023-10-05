#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"
#include "objeto.h"
#include "estruturas.h"


void calculaCentroide(Objeto *objeto){
    float aux1 = 0.0;
    float aux2 = 0.0;

    for (int i = 0; i < objeto->totalPontos; i++){
        aux1 += objeto->pontos[i].x;
        aux2 += objeto->pontos[i].y;
    }

    objeto->x_meio = aux1/(float)objeto->totalPontos;
    objeto->y_meio = aux2/(float)objeto->totalPontos;
}

void remover(Lista *lista, Objeto *objeto) {
    Objeto *inicio = lista->inicio; // ponteiro para o início da lista
    Objeto * noARemover = objeto; // ponteiro para o nó a ser removido

    if(inicio != NULL && lista->inicio == noARemover) { // remover 1º elemento
        noARemover = lista->inicio;
        lista->inicio = noARemover->proximo;
        if(lista->inicio == NULL)
            lista->fim = NULL;
    } else { // remoção no meio ou no final
        while(inicio != NULL && inicio->proximo != NULL && inicio->proximo != noARemover) {
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

void inserirFim(Lista *lista, int idObjeto, int tipoObjeto, int totalPontos, Ponto *pontos){
    printf("entrou");
    Objeto *novo = (Objeto*)malloc(sizeof(Objeto)); // cria um novo nó
    novo->idObjeto = idObjeto;
    novo->tipoObjeto = tipoObjeto;
    novo->totalPontos = totalPontos;

    for (int i = 0; i < totalPontos; i++){
        novo->pontos[i].bColor = pontos[i].bColor;
        novo->pontos[i].gColor = pontos[i].gColor;
        novo->pontos[i].rColor = pontos[i].rColor;
        novo->pontos[i].x = pontos[i].x;
        novo->pontos[i].y = pontos[i].y;
    }
    calculaCentroide(novo);
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

void transladaObjeto(Objeto *objeto, float tx, float ty){

    float** mTranslada = criar_matriz();
    preenche_matriz_traslacao(mTranslada, tx, ty);
    printf("%d", objeto->totalPontos);

    for (int i = 0; i < objeto->totalPontos; i++){
        modifica_pontos(mTranslada, &objeto->pontos[i].x, &objeto->pontos[i].y, objeto->pontos[i].x, objeto->pontos[i].y);
    }
    calculaCentroide(objeto);
    printf("Centroide: %f", objeto->x_meio);
    desaloca_matriz(mTranslada);
}

void rotacionaObjeto(Objeto *objeto, float teta){

    printf("Rotacionando");

    if(objeto->tipoObjeto == 0){ //Ele é um ponto
        float** mRotaciona = criar_matriz();
        preenche_matriz_rotacao(mRotaciona, teta);
        modifica_pontos(mRotaciona, &objeto->pontos[0].x, &objeto->pontos[0].y, objeto->pontos[0].x, objeto->pontos[0].y);
        desaloca_matriz(mRotaciona);
    }
    else{
        float** mTranslada = criar_matriz();
        float** mRotaciona = criar_matriz();
        preenche_matriz_traslacao(mTranslada, objeto->x_meio, objeto->y_meio);
        preenche_matriz_rotacao(mRotaciona, teta);
        float** result1 = multiplica_matriz(mTranslada, mRotaciona);
        preenche_matriz_traslacao(mTranslada, -objeto->x_meio, -objeto->y_meio);
        float** result2 = multiplica_matriz(result1, mTranslada);

        printf("\nMeio x: %f", objeto->x_meio);
        printf("\nMeio y: %f", objeto->y_meio);

        for (int i = 0; i < objeto->totalPontos; i++){
            modifica_pontos(result2, &objeto->pontos[i].x, &objeto->pontos[i].y, objeto->pontos[i].x, objeto->pontos[i].y);
        }
        //Desalocando
        desaloca_matriz(mRotaciona);
        desaloca_matriz(result1);
        desaloca_matriz(mTranslada);
        desaloca_matriz(result2);

    }
    calculaCentroide(objeto);
}

void escalaObjeto(Objeto *objeto, float sx, float sy){

    if(objeto->tipoObjeto != 0){

        float** mTranslada = criar_matriz();
        float** mEscala = criar_matriz();
        preenche_matriz_traslacao(mTranslada, objeto->x_meio, objeto->y_meio);
        preenche_matriz_escala(mEscala, sx, sy);
        float** result1 = multiplica_matriz(mTranslada, mEscala);
        preenche_matriz_traslacao(mTranslada, -objeto->x_meio, -objeto->y_meio);
        float** result2 = multiplica_matriz(result1, mTranslada);

        printf("\nMeio x: %f", objeto->x_meio);
        printf("\nMeio y: %f", objeto->y_meio);

        for (int i = 0; i < objeto->totalPontos; i++){
            modifica_pontos(result2, &objeto->pontos[i].x, &objeto->pontos[i].y, objeto->pontos[i].x, objeto->pontos[i].y);
        }
        //Desalocando
        desaloca_matriz(mEscala);
        desaloca_matriz(result1);
        desaloca_matriz(mTranslada);
        desaloca_matriz(result2);

    }
    calculaCentroide(objeto);

}

int pickPoligono(Objeto *poligono, float x, float y, float t){

    float p1_x, p1_y, p2_x, p2_y;
    int intersect = 0;

    for (int i = 0; i < poligono->totalPontos; i++){

        p1_x = poligono->pontos[i].x;
        p1_y = poligono->pontos[i].y;
        if(i+1 == poligono->totalPontos){
            p2_x = poligono->pontos[0].x;
            p2_y = poligono->pontos[0].y;
        }else{
            p2_x = poligono->pontos[i+1].x;
            p2_y = poligono->pontos[i+1].y;
        }

        //Casos Triviais
        if((p1_y > y) && (p2_y > y)){
            continue;
        }
        else if ((p1_y < y) && (p2_y < y)){
            continue;
        }
        else if((p1_x < x) && (p2_x < x)){
            continue;
        }
        else if(p1_y == p2_y){
            continue;
        }
        else if ((p1_x > x && p2_x > x) && ((p1_y > y && p2_y < y) || (p1_y < y && p2_y > y))){

            //Arestas à direita, uma acima e outra abaixo do ponto em y
            ++intersect;

        }
        else{
            //CALCULA A ABSCISSA
            float xi = p1_x + (y - p1_y)*(p2_x - p1_x)/(p2_y - p1_y);

            // Se a intersecção (xi) for maior que x, então o tiro intercepta, caso contrário, não
            if (xi > x){
                ++intersect;
            }
            else if (xi == p1_x && (p2_y > y || p2_y < y)){
                ++intersect;
            }
            else if(xi == p2_x && (p1_y > y || p1_y < y)){
                ++intersect;
            }
        }
    }//FOR

    printf("Inter %d", intersect);
    //Testa se é impar
    if(intersect % 2 == 0){
        return 0;
    }else{
        return 1;
    }

}

typedef struct Regioes{
	unsigned char all;
	unsigned char esquerda;
	unsigned char direita;
	unsigned char acima;
	unsigned char abaixo;
} Regioes;

Regioes computaRegioes(float px, float py, float xmin, float xmax, float ymin, float ymax){

	Regioes code;
	code.esquerda = 0, code.direita = 0, code.acima = 0, code.abaixo = 0, code.all = 0;

	if (px > xmax){
		code.direita = 1;
		code.all += 2;
	} else if (px < xmin){
		code.esquerda = 1;
		code.all += 1;
	}
	if (py > ymax){
		code.acima = 1;
		code.all += 8;
	} else if (py < ymin){
		code.abaixo = 1;
		code.all += 4;
	}
	return code;

}

int pickLinha(float x0, float y0, float x1, float y1, float mx, float my, float t){

	Regioes regioes0, regioes1, regioesOut;
	float x, y;
	int accept = 0;
	int done = 0;

	float xmin = mx - t;
	float xmax = mx + t;
	float ymin = my - t;
	float ymax = my + t;

	regioes0 = computaRegioes(x0, y0, xmin, xmax, ymin, ymax);
	regioes1 = computaRegioes(x1, y1, xmin, xmax, ymin, ymax);

	do {
		if (regioes0.all == 0 && regioes1.all == 0){
			accept = 1;
			done = 1;
		} else if((regioes0.all & regioes1.all) != 0){
			done = 1;
		}else{
			if(regioes0.all != 0){
				regioesOut = regioes0;
			}else{
				regioesOut = regioes1;
			}

			if (regioesOut.acima){
				x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
				y = ymax;
			} else if (regioesOut.abaixo){
				x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
				y = ymin;
			} else if (regioesOut.direita){
				y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
				x = xmax;
			} else if (regioesOut.esquerda){
				y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
				x = xmin;
			}

			if (regioesOut.all == regioes0.all){
				regioes0 = computaRegioes(x, y, xmin, xmax, ymin, ymax);
			}else{
				regioes1 = computaRegioes(x, y, xmin, xmax, ymin, ymax);
			}
		}
	}while (done == 0);

	if (accept == 1){
		return 1;
	}

    return 0;
}

int pickPonto(float px, float py, float mx, float my, float t){

    if(mx <= px + t && mx >= px - t){
        if(my <= py + t && my >= py - t){
            return 1;
        }
    }
    return 0;
}

Objeto *selecionaObjeto(Lista *lista, float mx, float my){

    Objeto *inicio = lista->inicio;
    float t = 6.0;

    while(inicio != NULL){
        if (inicio->tipoObjeto == 0){
            printf("AQUI");
            if (pickPonto(inicio->pontos[0].x, inicio->pontos[0].y, mx, my, t)){
                return inicio;
            }
            inicio = inicio->proximo;
            continue;
        }
        if (inicio->tipoObjeto == 1){
            if (pickLinha(inicio->pontos[0].x, inicio->pontos[0].y, inicio->pontos[1].x, inicio->pontos[1].y, mx, my, t)){
                return inicio;
            }
            inicio = inicio->proximo;
            continue;
        }
        if (inicio->tipoObjeto == 2){
            if (pickPoligono(inicio, mx, my, t)){
                return inicio;
            }
            inicio = inicio->proximo;
            continue;
        }
        inicio = inicio->proximo;

    }
    printf("Retorna NULL");
    return NULL;
}



