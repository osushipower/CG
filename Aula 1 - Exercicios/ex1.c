#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

void iteracao_mouse(int botao, int estado, int x, int y) {
    if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
        printf("X: %d | Y: %d\n", x, y);
    }
}

void desenha(){
    glClearColor(0, 0, 0, 0); //Preto
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}


int main(int argc , char * argv []) {
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50 ,100);
    glutInitWindowSize (400 ,400);
    glutCreateWindow ("Primeiro programa usando OpenGL");
    glutDisplayFunc (desenha);
    glutMouseFunc(iteracao_mouse);
    glutMainLoop ();
    
    return 0;
}