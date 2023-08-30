#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141592654

void circulo(){
    int i;
    float angulo = 0.0;
    glBegin(GL_POLYGON);
        for (i=0;i<=10;i++) {
            angulo= 2 * PI * i / 10.0;
            glVertex2f(0.25*cos(angulo), 0.25*sin(angulo));
        }
    glEnd ();
}

void quadrado(float incX, float incY){
    glBegin(GL_POLYGON);
        glVertex2f(-0.25+incX, 0.25+incY);
        glVertex2f(0.25+incX, 0.25+incY);
        glVertex2f(0.25+incX, -0.25+incY);
        glVertex2f(-0.25+incX, -0.25+incY);
    glEnd();
}

void desenha(){
    glClearColor(0, 0, 0, 0); //Preto
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    circulo();
    glColor3f(1.0,0.0,0.0);
    quadrado(0.5,0.5);
    glColor3f(0.0,1.0,0.0);
    quadrado(-0.5,0.5);
    glColor3f(0.0,0.0,1.0);
    quadrado(0.5,-0.5);
    glColor3f(1.0,1.0,0.0);
    quadrado(-0.5,-0.5);
    glFlush();
}

int main ( int argc , char * argv [] ){
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50 ,100);
    glutInitWindowSize (400 ,400);
    glutCreateWindow ("Primeiro programa usando OpenGL");
    glutDisplayFunc (desenha);
    glutMainLoop ();
    return 0;
}