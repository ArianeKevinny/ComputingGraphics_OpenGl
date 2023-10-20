#include <windows.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut.h>

int selected = 0;

struct Objeto{
    float x;
    float y;
    float z;
    float alpha; //x
    float beta; //y
    float omega; //z
    float delta;
    float pos_x;
    float pos_y;
    float pos_z;
}; typedef struct Objeto Objeto;

Objeto bule = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 50.0, 12.0, 50.0};
Objeto bola = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 130.0, 25.0, 40.0};
Objeto toro = {0.0, 0.0, 0.0, 90.0, 0.0, 0.0, 1.0, 105.0, 8.0, 105.0};

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

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(40.0, 40.0, 40.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION); //Matriz de projeção
    glLoadIdentity();
    glOrtho(-150.0,150.0,-150.0,150.0,-150.0,150.0);

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

void desenhaCenario(){

    materialColor(134.0, 96.0, 96.0, 0.0f, 0.3f);

    //Paredes
    //glColor3f(146.0/255.0, 158.0/255.0, 141./255.0);
    glBegin(GL_POLYGON);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 150.0);
        glVertex3f(0.0, 150.0, 150.0);
        glVertex3f(0.0, 150.0, 0.0);
        glVertex3f(150.0, 150.0, 0.0);
        glVertex3f(150.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
    glEnd();

    // Chão
    materialColor(246.0, 228.0, 228.0, 0.0f, 0.1f);
    //glColor3f(213.0/255.0, 213.0/255.0, 202./255.0);
    glBegin(GL_POLYGON);
        glVertex3f(150.0, 0.0, 150.0);
        glVertex3f(150.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 150.0);
    glEnd();
}

void display(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    desenhaCenario();

    materialColor(0.0, 139.0, 139.0, 35.0f, 0.7f);
    glPushMatrix();
        glTranslatef(bule.pos_x, bule.pos_y, bule.pos_z);
        glRotatef(bule.alpha, 1, 0, 0);
        glRotatef(bule.beta, 0, 1, 0);
        glRotatef(bule.omega, 0, 0, 1);
        glScalef(bule.delta, bule.delta, bule.delta);
        glutSolidTeapot(15.0f);
    glPopMatrix();

    materialColor(0.0, 153.0, 76.0, 35.0f, 0.7f);
    glPushMatrix();
        glTranslatef(bola.pos_x, bola.pos_y, bola.pos_z);
        glRotatef(bola.alpha, 1, 0, 0);
        glRotatef(bola.beta, 0, 1, 0);
        glRotatef(bola.omega, 0, 0, 1);
        glScalef(bola.delta, bola.delta, bola.delta);
        glutSolidSphere(25.0f, 50, 50);
    glPopMatrix();

    materialColor(240.0, 28.0, 28.0, 55.0f, 0.6f);
    glPushMatrix();
        glTranslatef(toro.pos_x, toro.pos_y, toro.pos_z);
        glRotatef(toro.alpha, 1, 0, 0);
        glRotatef(toro.beta, 0, 1, 0);
        glRotatef(toro.omega, 0, 0, 1);
        glScalef(toro.delta, toro.delta, toro.delta);
        glutSolidTorus(8.0, 20.0, 20, 20);
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
        case 51:
            selected = 3;
            break;
        case 13:
            selected = 0;
            break;
    }
    glutPostRedisplay();
}


void Teclado_Especial(unsigned char tecla, int x, int y){

    printf("Aqui");
    switch(tecla)
    {
    case GLUT_KEY_LEFT:
        if((selected == 1) && (bule.pos_x-1>=25)){
            bule.pos_x -= 1;
            break;
        }
        if((selected == 2) && (bola.pos_x-1>=20)){
            bola.pos_x -= 1;
            break;
        }
        if((selected == 3) && (toro.pos_x-1>=30)){
            toro.pos_x -= 1;
            break;
        }
        break;
    case GLUT_KEY_RIGHT:
        if((selected == 1) && (bule.pos_x+1<=135)){
            bule.pos_x += 1;
            break;
        }
        if((selected == 2) && (bola.pos_x+1<=130)){
            bola.pos_x += 1;
            break;
        }
        if((selected == 3) && (toro.pos_x+1<=125)){
            toro.pos_x += 1;
            break;
        }
        break;
    case GLUT_KEY_UP:
        if((selected == 1) && (bule.pos_z-1>=25)){
            bule.pos_z -= 1;
            break;
        }
        if((selected == 2) && (bola.pos_z-1>=20)){
            bola.pos_z -= 1;
            break;
        }
        if((selected == 3) && (toro.pos_z-1>=30)){
            toro.pos_z -= 1;
            break;
        }
        break;
    case GLUT_KEY_DOWN:
        if((selected == 1) && (bule.pos_z+1<=135)){
            bule.pos_z += 1;
            break;
        }
        if((selected == 2) && (bola.pos_z+1<=130)){
            bola.pos_z += 1;
            break;
        }
        if((selected == 3) && (toro.pos_z+1<=125)){
            toro.pos_z += 1;
            break;
        }
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y){

    switch(state)
    {
    case GLUT_DOWN:
        //Rotação em Z
        if(button == 3 && selected == 1){
            bule.beta += 5;
            break;
        }
        if(button == 3 && selected == 2){
            bola.beta += 5;
            break;
        }
        if(button == 3 && selected == 3){
            toro.omega += 5;
            break;
        }
        if(button == 4 && selected == 1){
            bule.beta -= 5;
            break;
        }
        if(button == 4 && selected == 2){
            bola.beta -= 5;
            break;
        }
        if(button == 4 && selected == 3){
            toro.omega -= 5;
            break;
        }
        break;
    case GLUT_UP:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv){

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200,0);
    glutCreateWindow("3D - Trabalho Final I");

    glutSpecialFunc(Teclado_Especial);
    glutMouseFunc(Mouse);
    glutKeyboardFunc(Teclado);

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;

}
