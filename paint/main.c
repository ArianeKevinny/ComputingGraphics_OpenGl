#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define TOTAL_PONTOS 100

#include "matrix.h"

// Criando as estruturas

typedef struct{
    float x;
    float y;
    float rColor;
    float gColor;
    float bColor;
} Ponto;

Ponto pontos_temp[TOTAL_PONTOS];

typedef struct Objeto{
    int idObjeto;
    int tipoObjeto;
    int totalPontos;
    float x_meio;
    float y_meio;
    Ponto pontos[100];
    struct Objeto *proximo;
} Objeto;

typedef struct Lista{
    Objeto *inicio, *fim;
    int tam;
} Lista;

struct Lista lista = {.fim = NULL, .inicio=NULL, .tam=0};

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

void inserirFim(Lista *lista,int idObjeto,int tipoObjeto, int totalPontos, float x_meio, float y_meio){

    Objeto *novo = (Objeto*)malloc(sizeof(Objeto)); // cria um novo nó
    novo->idObjeto = idObjeto;
    novo->tipoObjeto = tipoObjeto;
    novo->totalPontos = totalPontos;
    novo->x_meio = x_meio;
    novo->y_meio = y_meio;
    for (int i = 0; i < novo->totalPontos; i++){
        novo->pontos[i].bColor = pontos_temp[i].bColor;
        novo->pontos[i].gColor = pontos_temp[i].gColor;
        novo->pontos[i].rColor = pontos_temp[i].rColor;
        novo->pontos[i].x = pontos_temp[i].x;
        novo->pontos[i].y = pontos_temp[i].y;
    }
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

typedef struct{
	unsigned char all;
	unsigned char esquerda;
	unsigned char direita;
	unsigned char acima;
	unsigned char abaixo;
} Regioes;

// SELEÇÃO

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

int pickPonto(float px, float py, float mx, float my, int t){
    if(mx <= px + t && mx >= px - t){
        if(my <= py + t && my >= py - t){
            return 1;
        }
    }
    return 0;
}

int pick_return_ID(Lista *lista, float mx, float my, float t){

    Objeto *inicio = lista->inicio;

    while(inicio != NULL){
        printf("\nAqui");
        printf("\n Tipo Objeto %d", inicio->tipoObjeto);

        if (inicio->tipoObjeto == 0){
            if (pickPonto(inicio->pontos[0].x, inicio->pontos[0].y, mx, my, t)){
                return inicio->idObjeto;
            }
            inicio = inicio->proximo;
            continue;
        }
        if (inicio->tipoObjeto == 1){
            if (pickLinha(inicio->pontos[0].x, inicio->pontos[0].y, inicio->pontos[1].x, inicio->pontos[1].y, mx, my, t)){
                return inicio->idObjeto;
            }
            inicio = inicio->proximo;
            continue;
        }
        inicio = inicio->proximo;

    }
    return 0;
}

//Auxiliares
int modoDesenho = -1;
int totalpontos = 0;
int count_idObjeto = 1;
int selected = 0;
int tipo_modifica = 0;
float pos_x = 0.0;
float pos_y = 0.0;
float teta = 0.0;
float tol = 1.5;
float soma_x = 0.0;
float soma_y = 0.0;

void modificaElementos(Lista *lista){

    Objeto *inicio = lista->inicio;

    for(int i=0; i<=lista->tam; i++){

        if(inicio->idObjeto == selected && tipo_modifica==1){
            float m1[3][3] = {1.0,0.0,pos_x-inicio->x_meio,0.0,1.0,pos_y-inicio->y_meio,0.0,0.0,1.0};
            for(int j=0; j<soma_x; j++){
                retorna_novos_pontos(&m1, &inicio->pontos[j].x, &inicio->pontos[j].y,inicio->pontos[j].x, inicio->pontos[j].y);
                soma_x += inicio->pontos[j].x;
                soma_y += inicio->pontos[j].y;
                printf("AQUI");
            }
            //recalculo do centroide
            inicio->x_meio = soma_x/inicio->totalPontos;
            inicio->y_meio = soma_y/inicio->totalPontos;
            soma_x = 0;
            soma_y = 0;
        }
        else if(inicio->idObjeto == selected && tipo_modifica==2){
            float m2[3][3] = {1.0,0.0,-inicio->x_meio,0.0,1.0,-inicio->y_meio,0.0,0.0,1.0};
            float m3[3][3] = {cos(teta),-sin(teta),0.0,sin(teta),cos(teta),0.0,0.0,0.0,1.0};
            float m4[3][3] = {1.0,0.0,inicio->x_meio,0.0,1.0,inicio->y_meio,0.0,0.0,1.0};
            float mt[3][3] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
            multiplica_matriz(&m2, &m3, &mt);
            float mj[3][3] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
            multiplica_matriz(&mt, &m4, &mj);
            for(int j=0; j<inicio->totalPontos; j++){
                retorna_novos_pontos(&mj, &inicio->pontos[j].x, &inicio->pontos[j].y,inicio->pontos[j].x, inicio->pontos[j].y);
                soma_x += inicio->pontos[j].x;
                soma_y += inicio->pontos[j].y;
                printf("AQUI");
            }
            //recalculo do centroide
            inicio->x_meio = soma_x/inicio->totalPontos;
            inicio->y_meio = soma_y/inicio->totalPontos;
            soma_x = 0;
            soma_y = 0;
        }
        else if(inicio->idObjeto == selected && tipo_modifica==3){
            float m5[3][3] = {1.0,0.0,-inicio->x_meio,0.0,1.0,-inicio->y_meio,0.0,0.0,1.0};
            float m6[3][3] = {pos_x,0.0,0.0,0.0,pos_y,0.0,0.0,0.0,1.0};
            float m7[3][3] = {1.0,0.0,inicio->x_meio,0.0,1.0,inicio->y_meio,0.0,0.0,1.0};
            float mk[3][3] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
            multiplica_matriz(&m5, &m6, &mk);
            float mi[3][3] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
            multiplica_matriz(&mk, &m7, &mi);
            for(int j=0; j<inicio->totalPontos; j++){
                retorna_novos_pontos(&mi, &inicio->pontos[j].x, &inicio->pontos[j].y,inicio->pontos[j].x, inicio->pontos[j].y);
                soma_x += inicio->pontos[j].x;
                soma_y += inicio->pontos[j].y;
                printf("AQUI");
            }
            //recalculo do centroide
            inicio->x_meio = soma_x/inicio->totalPontos;
            inicio->y_meio = soma_y/inicio->totalPontos;
            soma_x = 0;
            soma_y = 0;
        }

        inicio = inicio->proximo;
    }

}

int init(void){
    /*
glMatrixMode: modo de operação da matriz
○ glutOrtho2D: os parâmetros que estão sendo fornecidos trata-se da estrutura
de janela de recorte. A área de desenho é como se tivesse no sistema cartesiano
x, y (infinito). Portanto, é necessário selecionar qual parte do sistema cartesiano
que vai parar na tela do openGL, setando o menor e o maior valor de x e y
    */

    glClearColor(1.0,1.0,1.0,0.0); //RGB
    glMatrixMode(GL_PROJECTION); //Matriz de projeção
    gluOrtho2D(0.0,800.0,0.0,600.0);

}

void display(void){


    //Define o método de desenho
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    Objeto *inicio = lista.inicio;

    for(int i=0; i<lista.tam; i++){

        switch(inicio->tipoObjeto){
        case 0:
            glPointSize(4.0);
            glBegin(GL_POINTS);
                for(int j=0; j<=inicio->totalPontos; j++){
                    glColor3f(inicio->pontos[j].rColor, inicio->pontos[j].gColor, inicio->pontos[j].bColor);
                    glVertex2f(inicio->pontos[j].x, inicio->pontos[j].y);
                }
            glEnd();
            break;
        case 1:
            glLineWidth(4.0);
            glBegin(GL_LINES);
                for(int j=0; j<inicio->totalPontos; j++){
                    glColor3f(inicio->pontos[j].rColor, inicio->pontos[j].gColor, inicio->pontos[j].bColor);
                    glVertex2f(inicio->pontos[j].x, inicio->pontos[j].y);
                }
            glEnd();
        break;
        case 2:
            glBegin(GL_POLYGON);
                for(int j=0; j<inicio->totalPontos; j++){
                    glColor3f(inicio->pontos[j].rColor, inicio->pontos[j].gColor, inicio->pontos[j].bColor);
                    glVertex2f(inicio->pontos[j].x, inicio->pontos[j].y);
                }
            glEnd();
        break;
        }
        inicio = inicio->proximo;
    }

    //glFlush(); //Desenha o que eu não coloquei comando direto
    glutSwapBuffers();
}

void Teclado(unsigned char tecla, int x, int y){
    switch(tecla){
        case 27:
            exit(0);
            break;
        case 13:
            if(modoDesenho == 2){
                inserirFim(&lista, count_idObjeto, 2, totalpontos, soma_x/(float)totalpontos, soma_y/(float)totalpontos);
                totalpontos = 0;
                ++count_idObjeto;
                soma_y = 0.0;
                soma_x = 0.0;
            }
            break;
        case 8: // Backspace
            if(modoDesenho == 3 && selected != 0){
                remover(&lista, selected);
            }
            break;
        case 46: // Delete
            if(modoDesenho == 3 && selected != 0){
                remover(&lista, selected);
            }
            break;
    }
}

void Teclado_Especial(unsigned char tecla, int x, int y){

    switch(tecla)
    {
    case GLUT_KEY_F1:
        glutFullScreen();
        break;
    case GLUT_KEY_LEFT:
        if(modoDesenho == 3 && selected != 0){
            pos_x -= 5.0;
            tipo_modifica = 2;
            modificaElementos(&lista);
            pos_x = 0;
            pos_y = 0;
        }
        break;
    case GLUT_KEY_UP:
        if(modoDesenho == 3 && selected != 0){
            pos_y += 5.0;
            tipo_modifica = 2;
            modificaElementos(&lista);
            pos_x = 0;
            pos_y = 0;
        }
        break;
    case GLUT_KEY_DOWN:
        if(modoDesenho == 3 && selected != 0){
            pos_y -= 5.0;
            tipo_modifica = 2;
            modificaElementos(&lista);
            pos_x = 0;
            pos_y = 0;
        }
        break;
    case GLUT_KEY_RIGHT:
        if(modoDesenho == 3 && selected != 0){
            pos_x += 5.0;
            tipo_modifica = 2;
            modificaElementos(&lista);
            pos_x = 0;
            pos_y = 0;
        }
        break;
    }

}

void Mouse(int button, int state, int x, int y){

    float my = (float)glutGet(GLUT_WINDOW_HEIGHT)-y;
    float mx = x;
    switch(state)
    {
    case GLUT_DOWN:
        if(modoDesenho == 0){

            pontos_temp[0].bColor = 0.0;
            pontos_temp[0].gColor = 1.0;
            pontos_temp[0].rColor = 0.0;
            pontos_temp[0].x = mx;
            pontos_temp[0].y = my;
            soma_x += mx;
            soma_y += my;
            ++totalpontos;

            if(totalpontos == 1){
                inserirFim(&lista, count_idObjeto, 0, totalpontos, soma_x/(float)totalpontos, soma_y/(float)totalpontos);
                totalpontos = 0;
                ++count_idObjeto;
                soma_y = 0.0;
                soma_x = 0.0;
            }
            break;
        }
        if(modoDesenho == 1){
            //Armazena Segmento de Reta
            pontos_temp[totalpontos].bColor = 1.0;
            pontos_temp[totalpontos].gColor = 0.0;
            pontos_temp[totalpontos].rColor = 0.0;
            pontos_temp[totalpontos].x = mx;
            pontos_temp[totalpontos].y = my;
            soma_x += mx;
            soma_y += my;
            ++totalpontos;

            if(totalpontos == 2){
                inserirFim(&lista, count_idObjeto, 1, totalpontos, soma_x/(float)totalpontos, soma_y/(float)totalpontos);
                totalpontos = 0;
                ++count_idObjeto;
                soma_y = 0.0;
                soma_x = 0.0;
            }
            break;
        }
        if(modoDesenho == 2){
            //Armazena Poligonos
            pontos_temp[totalpontos].bColor = 0.0;
            pontos_temp[totalpontos].gColor = 0.0;
            pontos_temp[totalpontos].rColor = 1.0;
            pontos_temp[totalpontos].x = mx;
            pontos_temp[totalpontos].y = my;
            ++totalpontos;
            soma_x += mx;
            soma_y += my;
            break;
        }
        if(modoDesenho == 3){
            selected = pick_return_ID(&lista, (float)x, (float)glutGet(GLUT_WINDOW_HEIGHT)-y, tol);
            printf("ID OBJETO: %d", selected);
            break;
        }
        break;
    case GLUT_UP:
        if(modoDesenho == 3 && selected != 0){
            pos_x = mx;
            pos_y = my;
            tipo_modifica = 1;
            modificaElementos(&lista);
            pos_x = 0;
            pos_y = 0;
            break;
        }
        break;
    }

    if(button == 3){
        if(modoDesenho == 3 && selected != 0){
            teta -= 10;
            tipo_modifica = 1;
            modificaElementos(&lista);
        }
    }
    else if(button == 4){
        if(modoDesenho == 3 && selected != 0){
            teta += 10;
            tipo_modifica = 1;
            modificaElementos(&lista);
        }
    }
}

void menuObjeto(int opcao){
    switch(opcao)
    {
    case 0:
        modoDesenho = 0;
        printf("  Ponto  ");//Ponto
        break;
    case 1:
        modoDesenho = 1;
        printf("  Reta   ");//Reta
        break;
    case 2:
        modoDesenho = 2;
        printf("  Poligono   "); //Poligono
        break;
    case 3:
        modoDesenho = 3;
        printf("Selecionar Objeto");
        break;
    }
}

int main(int argc, char** argv){

    /*Inicializar o GLUT
    GLUT é uma biblioteca de funcionalidades para OpenGL cujo principal objetivo é
    a abstração do sistema operacional fazendo com que os aplicativos sejam multiplataforma.
    A biblioteca possui funcionalidades para criação e controle de janelas,
    e também tratamento de eventos de dispositivos de entrada
    */

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(300,300);
    glutCreateWindow("PAINT");

    init();

    int menuPrincipal;
    menuPrincipal = glutCreateMenu(menuObjeto);
    glutAddMenuEntry("Crie Pontos", 0);
    glutAddMenuEntry("Crie Retas", 1);
    glutAddMenuEntry("Crie Poligonos", 2);
    glutAddMenuEntry("Selecione um objeto", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMouseFunc(Mouse);
    glutKeyboardFunc(Teclado);
    glutSpecialFunc(Teclado_Especial);

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;

}
