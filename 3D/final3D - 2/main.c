#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

int selected = 0;

struct Objeto{
    float x;
    float y;
    float z;
    float beta; //y

}; typedef struct Objeto Objeto;

Objeto bule = {0.0, 0.0, 0.0, 0.0};


// MOVIMENTAÇÃO NO CHÃO, X OU EM V DEVE ESTAR ENTRE [0, 150]

void lighting(){

    float global[4] = {0.9f,0.9f,0.9f,1.0f};
    float black[4] = {0.0f,0.0f,0.0f,0.0f};
    float white[4] = {1.0f,1.0f,1.0f,1.0f};
    //float red[4] = {1.0f,0.0f,0.0f,1.0f};
    float position0[4] = {40.0f,100.0f,40.0f,1.0f};
    //float position1[4] = {0.0f,0.0f,150.0f,1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, position0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    //glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.7f);
    //glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);
    //glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);

    //Luz global
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}

int init(void){

    glClearColor(1.0f,1.0f,1.0f,1.0f); //RGB
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION); //Matriz de projeção
    glLoadIdentity();
    glOrtho(-100.0,100.0,-100.0,100.0,-100.0,100.0);

    lighting();

}

void materialColor(float r, float g, float b, float intensidade, float specular){


    float kd[4] = {r/255.0, g/255.0, b/255.0, 1.0f};
    float ks[4] = {specular, specular, specular, 1.0f};
    float ns = intensidade;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, ks);
    glMaterialf(GL_FRONT, GL_SHININESS, ns);

}

void desenhaObjeto(){

    glTranslatef(bule.x, bule.y, bule.z);
    glRotatef(bule.beta, 0, 1, 0);
    glutSolidTeapot(40.0f);

}

void display(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    materialColor(112.0, 14.0, 14.0, 35.0f, 0.6f);
    //XZ
    glViewport(0, 0, 300, 300);
    glPushMatrix();
        gluLookAt(0.0, 1.0, 0.0,
                  0.0, 0.0, 0.0,
                  0.0, 0.0, -1.0);
        desenhaObjeto();
    glPopMatrix();

    //perpective
    glViewport(300, 0, 300, 300);
    glPushMatrix();
        gluLookAt(40.0, 20.0, 40.0,
                0.0, 0.0, 0.0,
                0.0, 1.0, 0.0);
        desenhaObjeto();
    glPopMatrix();

    //XY
    glViewport(0, 300, 300, 300);
    glPushMatrix();
        gluLookAt(0.0, 0.0, 1.0,
                  0.0, 0.0, 0.0,
                  0.0, 1.0, 0.0);
        desenhaObjeto();
    glPopMatrix();

    glViewport(300, 300, 300, 300);
    glPushMatrix();
        gluLookAt(1.0, 0.0, 0.0,
                  0.0, 0.0, 0.0,
                  0.0, 1.0, 0.0);
        desenhaObjeto();
    glPopMatrix();

    glFlush(); //Desenha o que eu não coloquei comando direto
}

int main(int argc, char** argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(200,0);
    glutCreateWindow("3D - Trabalho Final I");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;

}
