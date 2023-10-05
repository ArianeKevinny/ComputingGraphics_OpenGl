#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>

float alpha = 0.0;
float beta = 0.0;
int selected;

int init(void){
    /*
glMatrixMode: modo de operação da matriz
○ glutOrtho2D: os parâmetros que estão sendo fornecidos trata-se da estrutura
de janela de recorte. A área de desenho é como se tivesse no sistema cartesiano
x, y (infinito). Portanto, é necessário selecionar qual parte do sistema cartesiano
que vai parar na tela do openGL, setando o menor e o maior valor de x e y
    */
    glClearColor(0.0,0.0,0.0,0.0); //RGB
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION); //Matriz de projeção
    glLoadIdentity();
    glOrtho(-150.0,150.0,-150.0,150.0,-150.0,150.0);

}

void modificaObjeto(int objeto){


}


void display(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();
        glTranslated(50, 0, 0);
        glColor3f(0.0, 0.0, 1.0);
        glRotatef(alpha, 1, 0, 1);
        glutWireTeapot(30.0f);
    glPopMatrix();


    glPushMatrix();
        glTranslated(-50, 0, 0);
        glColor3f(1.0, 1.0, 0.0);
        glRotatef(beta, 1, 1, 1);
        glutWireCube(30.0f);
    glPopMatrix();



    glFlush(); //Desenha o que eu não coloquei comando direto
}

void Teclado(unsigned char tecla, int x, int y){

    switch(tecla){
        case 49:
            selected = 1;
            break;
        case 50:
            selected = 2;
            break;
        case 13:
            selected = 0;
            break;
    }
    glutPostRedisplay();
}


void Teclado_Especial(unsigned char tecla, int x, int y){

    switch(tecla)
    {
    case GLUT_KEY_LEFT:
        if(selected == 1){
            beta += 1;
            break;}
        if(selected == 2){
            alpha += 1;
            break;}
        break;
    case GLUT_KEY_RIGHT:
        if(selected == 1){
            beta -= 1;
            break;}
        if(selected == 2){
            alpha -= 1;
            break;}
        break;
    }
    glutPostRedisplay();

}

int main(int argc, char** argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(200,0);
    glutCreateWindow("3D - Chaleira e cubo");


    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(Teclado);
    glutSpecialFunc(Teclado_Especial);

    glutMainLoop();

    return 0;

}
