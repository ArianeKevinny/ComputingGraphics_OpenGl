#ifndef __PICK_H_
#define __PICK_H_

typedef struct{
	unsigned char all;
	unsigned char esquerda;
	unsigned char direita;
	unsigned char acima;
	unsigned char abaixo;
} Regioes;

Regioes computaRegioes(float px, float py, float xmin, float xmax, float ymin, float ymax);

int pickLinha(float x0, float y0, float x1, float y1, float mx, float my, float t);

int pickPonto(float px, float py, float mx, float my, int t);

int pick_return_ID(Lista *lista, float mx, float my);

#endif // __PICK_H_
