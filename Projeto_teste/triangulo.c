#include <windows.h>
#include <GL/glut.h>

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

    gluOrtho2D(0.0,200.0,0.0,150.0);

}

void display(void){

    //Define o método de desenho

    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0); //Definindo a cor do onj
    glBegin(GL_TRIANGLES);
        glVertex2i(100, 10);
        glVertex2i(200, 10);
        glVertex2i(150,100);
    glEnd();

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
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(200,0);

    //Criando a janela
    glutCreateWindow("Nome que fica lá em cima!");

    //Chama o inicializador
    init();

    //Função callback de exibição
    glutDisplayFunc(display);

    //Mostra tudo e espere
    glutMainLoop();

    return 0;

}
