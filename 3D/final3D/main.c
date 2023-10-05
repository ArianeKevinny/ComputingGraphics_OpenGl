#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

int selected;

struct Objeto{
    float x;
    float y;
    float z;
    float alpha; //x
    float beta; //y
    float omega; //z
    float delta;
}; typedef struct Objeto Objeto;

Objeto bule = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0};
Objeto bola = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0};
Objeto toro = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0};

int init(void){

    glClearColor(1.0f,1.0f,1.0f,1.0f); //RGB
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(150.0, 120.0, 150.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

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

    glColor3f(0.0f,1.0f,0.0f);
    // Chão
    glBegin(GL_POLYGON);
        glVertex3f(100.0, 0.0, 100.0);
        glVertex3f(100.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 100.0);
    glEnd();

    glColor3f(0.0f,1.0f,0.0f);
    // Paredes
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.0, 100.0);
        glVertex3f(0.0, 100.0, 100.0);
        glVertex3f(0.0, 100.0, 0.0);
        glVertex3f(100.0, 100.0, 0.0);
        glVertex3f(100.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
    glEnd();

    glColor3f(240.0/255.0, 128.0/255.0, 128.0/255.0);

    glPushMatrix();
        glTranslatef(bule.x, bule.y, bule.z);
        glRotatef(bule.alpha, 1, 0, 0);
        glRotatef(bule.beta, 0, 1, 0);
        glRotatef(bule.omega, 0, 0, 1);
        glScalef(bule.delta, bule.delta, bule.delta);
        glutSolidTeapot(30.0f);
    glPopMatrix();

    glColor3f(173.0/255.0, 216.0/255.0, 230.0/255.0);

    glPushMatrix();
        glTranslatef(bola.x, bola.y, bola.z);
        glRotatef(bola.alpha, 1, 0, 0);
        glRotatef(bola.beta, 0, 1, 0);
        glRotatef(bola.omega, 0, 0, 1);
        glScalef(bola.delta, bola.delta, bola.delta);
        glutSolidSphere(20.0f, 50, 50);
    glPopMatrix();

    glColor3f(0.0/255.0, 139.0/255.0, 139.0/255.0);

    glPushMatrix();
        glTranslatef(toro.x, toro.y, toro.z);
        glRotatef(toro.alpha, 1, 0, 0);
        glRotatef(toro.beta, 0, 1, 0);
        glRotatef(toro.omega, 0, 0, 1);
        glScalef(toro.delta, toro.delta, toro.delta);
        glutSolidTorus(8.0, 20.0, 20, 20);
    glPopMatrix();


    glFlush(); //Desenha o que eu não coloquei comando direto
}
/*
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
*/
int main(int argc, char** argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(200,0);
    glutCreateWindow("3D - Trabalho Final I");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;

}
