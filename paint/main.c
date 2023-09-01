#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

#define TOTAL_OBJ 100
#define TOTAL_P 100

int modoDesenho = -1;
int totalobjetos = 0;
int totalpontos = 0;

struct Ponto{
    float x;
    float y;
    float rColor;
    float gColor;
    float bColor;

}; typedef struct Ponto Ponto;

struct Objeto{

    int tipoObjeto;
    int totalPontos;
    Ponto pontos[TOTAL_P];

}objetos[TOTAL_OBJ];

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
    gluOrtho2D(0.0,400.0,0.0,300.0);

}

void desenha_pontos(){
//Implementar
}

void desenha_retas(){
//Implementar
}

void desenha_poligonos(){
    //Imlementar
}

void display(void){

    //Define o método de desenho

    glClear(GL_COLOR_BUFFER_BIT);
    //glMatrixMode(GL_MODELVIEW);

    for(int i=0; i<=totalobjetos; i++){

        switch(objetos[i].tipoObjeto){
        case 0:
        glPointSize(3.0);
        glBegin(GL_POINTS);
            for(int j=0; j<=objetos[i].totalPontos; j++){
                glColor3f(objetos[i].pontos[j].rColor, objetos[i].pontos[j].gColor, objetos[i].pontos[j].bColor);
                glVertex2f(objetos[i].pontos[j].x, objetos[i].pontos[j].y);
            }
        glEnd();
        break;
        case 1:
        glLineWidth(2.0);
        glBegin(GL_LINES);
            for(int j=0; j<objetos[i].totalPontos; j++){
                glColor3f(objetos[i].pontos[j].rColor, objetos[i].pontos[j].gColor, objetos[i].pontos[j].bColor);
                glVertex2f(objetos[i].pontos[j].x, objetos[i].pontos[j].y);
            }
        glEnd();
        break;
        case 2:
        glBegin(GL_POLYGON);
            for(int j=0; j<objetos[i].totalPontos; j++){
                glColor3f(objetos[i].pontos[j].rColor, objetos[i].pontos[j].gColor, objetos[i].pontos[j].bColor);
                glVertex2f(objetos[i].pontos[j].x, objetos[i].pontos[j].y);
            }
        glEnd();
        break;
        }
    }

    glFlush(); //Desenha o que eu não coloquei comando direto
}

void Teclado(unsigned char tecla, int x, int y){

    switch(tecla){
        case 27:
            exit(0);
            break;
        case 13:
            ++totalobjetos;
            totalpontos = 0;
            break;
    }


}

void Teclado_Especial(unsigned char tecla, int x, int y){

    switch(tecla)
    {
    case GLUT_KEY_F1:
        glutFullScreen();
        break;
    }

}

void Mouse(int button, int state, int x, int y){

    switch(state)
    {
    case GLUT_DOWN:
        if(modoDesenho == 0){
            objetos[totalobjetos].pontos[totalpontos].bColor = 0.0;
            objetos[totalobjetos].pontos[totalpontos].gColor = 0.0;
            objetos[totalobjetos].pontos[totalpontos].rColor = 0.0;
            objetos[totalobjetos].pontos[totalpontos].x = (float)x;
            objetos[totalobjetos].pontos[totalpontos].y = (float)y;
            objetos[totalobjetos].tipoObjeto = 0;
             ++totalpontos;
            objetos[totalobjetos].totalPontos = totalpontos;
            break;
        }
        if(modoDesenho == 1){
            //Armazena Segmento de Reta
            objetos[totalobjetos].pontos[totalpontos].bColor = 1.0;
            objetos[totalobjetos].pontos[totalpontos].gColor = 0.0;
            objetos[totalobjetos].pontos[totalpontos].rColor = 0.0;
            objetos[totalobjetos].pontos[totalpontos].x = (float)x;
            objetos[totalobjetos].pontos[totalpontos].y = (float)y;
            objetos[totalobjetos].tipoObjeto = 1;
            ++totalpontos;
            objetos[totalobjetos].totalPontos = totalpontos;
            break;
        }
        if(modoDesenho == 2){
            //Armazena Segmento de Reta
            objetos[totalobjetos].pontos[totalpontos].bColor = 0.0;
            objetos[totalobjetos].pontos[totalpontos].gColor = 1.0;
            objetos[totalobjetos].pontos[totalpontos].rColor = 0.0;
            objetos[totalobjetos].pontos[totalpontos].x = (float)x;
            objetos[totalobjetos].pontos[totalpontos].y = (float)y;
            objetos[totalobjetos].tipoObjeto = 2;
            ++totalpontos;
            objetos[totalobjetos].totalPontos = totalpontos;
            break;
        }
        break;
    case GLUT_UP:
        break;
    }

    printf("\n Total Objeto: %d", totalobjetos);
    printf("\n Total Pontos: %d", totalpontos);
    //0 - click LEFT
    //2 - click right
    //1 - roll click
    //3 - roll up
    //4 - roll down

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
    }
}
/*
void menuTransformacao(int opcao){

    switch(opcao)
    {
    case 0: //Transladar
    case 1: //Rotacionar
    case 2: //Escalar
    }
}
*/
int main(int argc, char** argv){

    /*Inicializar o GLUT
    GLUT é uma biblioteca de funcionalidades para OpenGL cujo principal objetivo é
    a abstração do sistema operacional fazendo com que os aplicativos sejam multiplataforma.
    A biblioteca possui funcionalidades para criação e controle de janelas,
    e também tratamento de eventos de dispositivos de entrada
    */

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(200,0);

    glutCreateWindow("PAINT");

    init();


    glutDisplayFunc(display);


    int menuPrincipal;
    menuPrincipal = glutCreateMenu(menuObjeto);
    glutAddMenuEntry("Crie Pontos", 0);
    glutAddMenuEntry("Crie Retas", 1);
    glutAddMenuEntry("Crie Poligonos", 2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMouseFunc(Mouse);
    glutKeyboardFunc(Teclado);
    glutSpecialFunc(Teclado_Especial);
    glutMainLoop();


    return 0;

}
