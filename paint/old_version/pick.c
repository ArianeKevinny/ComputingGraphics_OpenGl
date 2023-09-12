#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 3.0
float t = 0.05;

typedef struct{
	unsigned char all;
	unsigned char esquerda;
	unsigned char direita;
	unsigned char acima;
	unsigned char abaixo;
} Regioes;

Regioes computaRegioes(float px, float py, float xmin, float xmax, float ymin, float ymax){

	Regioes code;
	code.esquerda -0, code.direita = 0, code.acima = 0, code.abaixo = 0, code.all = 0;

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

int pickPonto(float px, float py, float mx, float my, int t){

    if(mx <= px + t && mx >= px - t){
        if(my <= py + t && my >= py - t){
            return 1;
        }
    }
    return 0;
}

int pick_return_ID(Lista *lista, float mx, float my){

    Objeto *inicio = lista->inicio;

    while(inicio != NULL){
        if (inicio->tipoObjeto == 0){
            if (pickPonto(inicio->pontos[0].x, inicio->pontos[0].y, my, mx, t)){
                return inicio->idObjeto;
            }
            inicio = inicio->proximo;
            continue;
        }
        if (inicio->tipoObjeto == 1){
            if (pickLinha(inicio->pontos[0].x, inicio->pontos[0].y, inicio->pontos[1].x, inicio->pontos[1].y, my, mx, t)){
                return inicio->idObjeto;
            }
            inicio = inicio->proximo;
            continue;
        }
        inicio = inicio->proximo;

    }
    return 0;
}
