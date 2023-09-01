#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

float grausRadiano(float angulo_grau){
    // 360º para 360 pontos -> 1 grau de diatancia -> radiano -> 2pi*grau = 360*radiano
    return (angulo_grau * 2 * M_PI)/360.0;
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

    gluOrtho2D(0.0,400.0,0.0,200.0);

}

void display(void){

    //Define o método de desenho

    glClear(GL_COLOR_BUFFER_BIT);

    //Verde: esperança
    glColor3f(0.0, 0.612, 0.231); //Definindo a cor do onj
    glBegin(GL_QUADS);
        glVertex2i(50,10);
        glVertex2i(50,190);
        glVertex2i(350,190);
        glVertex2i(350,10);
    glEnd();

    // Amarelo: sei lá, desespero
    glColor3f(1.0, 0.991, 0.0);
    glBegin(GL_QUADS);
        glVertex2i(60,100);
        glVertex2i(200,180);
        glVertex2i(340,100);
        glVertex2i(200,20);
    glEnd();

    //https://ptcomputador.com/P/cc-programming/86089.html
    //Azul: Não sei

    float x_meio = 200.0;
    float y_meio = 100.0;
    float raio = 50.0;
    int num_pontos = 10000;
    float dist = grausRadiano(360.0/num_pontos);
    float angulo = dist;

    glShadeModel(GL_FLAT);
    //glColor3f(0.0, 0.153, 0.463);
    glBegin(GL_POLYGON);
        glColor3f(0.0, 0.153, 0.463);
        for(int i=0; i <num_pontos; i++){
            int x = raio * cos(angulo) + x_meio;
            int y = raio * sin(angulo) + y_meio;
            glVertex2f(x, y);
            angulo = angulo + dist;
        }
    glEnd();

    // Usando Circulo

    glFlush(); //Desenha o que eu não coloquei comando direto
}

int main(int argc, char** argv){

    /*Inicializar o GLUT
    GLUT é uma biblioteca de funcionalidades para OpenGL cujo principal objetivo é
    a abstração do sistema operacional fazendo com que os aplicativos sejam multiplataforma.
    A biblioteca possui funcionalidades para criação e controle de janelas,
    e também tratamento de eventos de dispositivos de entrada
    */

    glutInit(&argc,argv);

    //Configura o modo de display
    glutInitDisplayMode(GLUT_SINGLE| GLUT_RGB);

    //Altura e largura da janela
    glutInitWindowSize(400, 200);
    glutInitWindowPosition(200,0);

    //Criando a janela
    glutCreateWindow("Bandeira");

    //Chama o inicializador
    init();

    //Função callback de exibição
    glutDisplayFunc(display);

    //Mostra tudo e espere
    glutMainLoop();

    return 0;

}
