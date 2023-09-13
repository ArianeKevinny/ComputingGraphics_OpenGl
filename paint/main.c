#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "estruturas.h"
#include "objeto.h"
#include "matrix.h"

//CRIANDO LISTA GLOBAL

Ponto pontos_temp[100];

Lista lista = {.inicio = NULL, .fim = NULL, .tam = 0};


//Definindo objeto selecionado;
Objeto *selecionado = NULL;

//Criando vetor temporario de pontos


//Auxiliares
int aux;
int modoDesenho = -1;
int totalpontos = 0;
int count_idObjeto = 1;
int selected = 0;
int tipo_modifica = 0;

float pos_x = 0.0;
float pos_y = 0.0;
float teta = 0.0;

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
    //glMatrixMode(GL_MODELVIEW);

    Objeto *inicio = lista.inicio;

    for(int i=0; i<lista.tam; i++){

        switch(inicio->tipoObjeto){
        case 0:
            glPointSize(4.0);
            glBegin(GL_POINTS);
                glColor3f(inicio->pontos[0].rColor, inicio->pontos[0].gColor, inicio->pontos[0].bColor);
                glVertex2f(inicio->pontos[0].x, inicio->pontos[0].y);
            glEnd();
            break;
        case 1:
            glLineWidth(4.0);
            glBegin(GL_LINES);
                glColor3f(inicio->pontos[0].rColor, inicio->pontos[0].gColor, inicio->pontos[0].bColor);
                glVertex2f(inicio->pontos[0].x, inicio->pontos[0].y);
                glColor3f(inicio->pontos[1].rColor, inicio->pontos[1].gColor, inicio->pontos[1].bColor);
                glVertex2f(inicio->pontos[1].x, inicio->pontos[1].y);
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
    glFlush(); //Desenha o que eu não coloquei comando direto
    //glutSwapBuffers();
}

void Teclado(unsigned char tecla, int x, int y){

    switch(tecla){
        case 27:
            exit(0);
            break;
        case 13:
            if(modoDesenho == 2 && totalpontos > 2){
                inserirFim(&lista, count_idObjeto, 2, totalpontos, pontos_temp);
                totalpontos = 0;
                ++count_idObjeto;
            }
            break;
        case 8: // Backspace
            if(modoDesenho == 3 && selecionado != NULL){
                remover(&lista, selecionado);
            }
            break;
    }
    glutPostRedisplay();
}

void Teclado_Especial(unsigned char tecla, int x, int y){

    switch(tecla)
    {
    case GLUT_KEY_F12:
        glutFullScreen();
        break;
    case GLUT_KEY_F1:
        if(modoDesenho == 3 && selecionado != NULL){
            escalaObjeto(selecionado, 1.01, 1.01);
        }
        break;
    case GLUT_KEY_F2:
        if(modoDesenho == 3 && selecionado != NULL){
            printf("entrou aqui");
            escalaObjeto(selecionado, 1.0/1.01, 1.0/1.01);
        }
        break;
    case GLUT_KEY_LEFT:
        if(modoDesenho == 3 && selecionado != NULL){
            printf("Entrou aqui");
            transladaObjeto(selecionado, -5.0, 0.0);
        }
        break;
    case GLUT_KEY_UP:
        if(modoDesenho == 3 && selecionado != NULL){
            transladaObjeto(selecionado, 0.0, 5.0);
        }
        break;
    case GLUT_KEY_DOWN:
        if(modoDesenho == 3 && selecionado != NULL){
            transladaObjeto(selecionado, 0.0, -5.0);
        }
        break;
    case GLUT_KEY_RIGHT:
        if(modoDesenho == 3 && selecionado != NULL){
            transladaObjeto(selecionado, 5.0, 0.0);
        }
        break;
    }
    glutPostRedisplay();

}

void Mouse(int button, int state, int x, int y){

    float mx = x;
    float my = (float)glutGet(GLUT_WINDOW_HEIGHT)-y;


    switch(state)
    {
    case GLUT_DOWN:
        //CRIANDO PONTO
        if(modoDesenho == 0 && button == 0){

            pontos_temp[0].bColor = 0.0;
            pontos_temp[0].gColor = 0.0;
            pontos_temp[0].rColor = 1.0;
            pontos_temp[0].x = mx;
            pontos_temp[0].y = my;
            printf("Desenhou");
            ++totalpontos;

            if(totalpontos == 1){
                inserirFim(&lista, count_idObjeto, 0, totalpontos, pontos_temp);
                totalpontos = 0;
                ++count_idObjeto;
            }
            break;
        }
        //CRIANDO LINHA
        if(modoDesenho == 1 && button == 0){
            //Armazena Segmento de Reta
            pontos_temp[totalpontos].bColor = 0.0;
            pontos_temp[totalpontos].gColor = 1.0;
            pontos_temp[totalpontos].rColor = 0.0;
            pontos_temp[totalpontos].x = mx;
            pontos_temp[totalpontos].y = my;
            printf("temp x:  %f", pontos_temp[totalpontos].x);
            ++totalpontos;
            if(totalpontos == 2){
                inserirFim(&lista, count_idObjeto, 1, totalpontos, pontos_temp);
                totalpontos = 0;
                ++count_idObjeto;
            }
            break;
        }
        //CRIANDO POLIGONOS
        if(modoDesenho == 2 && button == 0){
            //Armazena Poligonos
            pontos_temp[totalpontos].bColor = 1.0;
            pontos_temp[totalpontos].gColor = 0.0;
            pontos_temp[totalpontos].rColor = 0.0;
            pontos_temp[totalpontos].x = mx;
            pontos_temp[totalpontos].y = my;
            ++totalpontos;
            //CONFIRMA COM O ENTER
            break;
        }
        if(modoDesenho == 3 && button == 0){
            printf("button: %d", button);
            selecionado = selecionaObjeto(&lista, mx, my);
            break;
        }
        if(button == 3 && modoDesenho == 3 && selecionado != NULL){
            printf("Entrou aqui - ROLL");
            rotacionaObjeto(selecionado, 0.005);
            break;
        }
        if(button == 4 && modoDesenho == 3 && selecionado != NULL){
            printf("Entrou aqui - ROLL down");
            rotacionaObjeto(selecionado, -0.005);
            break;
        }
        break;
    case GLUT_UP:
        break;
    }
    glutPostRedisplay();
}

void menuObjeto(int opcao){
    switch(opcao)
    {
    case 0:
        modoDesenho = 0;
        printf("  Desenhando Ponto  ");//Ponto
        break;
    case 1:
        modoDesenho = 1;
        printf("  Desenhando Reta   ");//Reta
        break;
    case 2:
        modoDesenho = 2;
        printf("  Desenhando Poligono   "); //Poligono
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

    init();

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;

}
