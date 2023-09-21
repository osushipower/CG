#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592654

float theta = 0.0;
float right = 0.0;

void wheel(){
    int i;
    float angulo = 0.0;
    glBegin(GL_POLYGON);
        for (i=0;i<=10;i++) {
            angulo= 2 * PI * i / 10.0;
            glVertex2f(0.125*cos(angulo), 0.125*sin(angulo));
        }
    glEnd ();
}

void car(){
    // Parte de cima
    glBegin(GL_POLYGON);
        glVertex2f(-0.25, 0.35);
        glVertex2f(0.25, 0.35);
        glVertex2f(0.25, 0.20);
        glVertex2f(-0.25, 0.20);
    glEnd();

    // Parte de baixo
    glBegin(GL_POLYGON);
        glVertex2f(-0.5, 0.20);
        glVertex2f(0.5, 0.20);
        glVertex2f(0.5, 0);
        glVertex2f(-0.5, 0);
    glEnd();
}

void onKeyPress(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_RIGHT:
            right+=0.05;
            theta+=5;
            break;
        case GLUT_KEY_LEFT:
            right-=0.05;
            theta-=5;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void display(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClearColor(0, 0, 0, 0); //Preto
    glClear(GL_COLOR_BUFFER_BIT);

    glTranslatef(right,0.0,0.0);

    glPushMatrix();
    glColor3f(0.0, 0.0, 1.0);
    car();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(0.3, 0.0,0.0);
    glRotatef(theta,0.0,0.0,1.0);
    wheel();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-0.3,0.0, 0.0);
    glRotatef(theta,0.0,0.0,1.0);
    wheel();
    glPopMatrix();

    glFlush();
}

int main ( int argc , char * argv [] ){
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50, 100);
    glutInitWindowSize (500, 500);
    glutCreateWindow("CG - Carro");
    glutDisplayFunc(display);
    glutSpecialFunc(onKeyPress);
    glutMainLoop ();
    return 0;
}