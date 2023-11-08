#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

GLfloat k = -100.0f;

GLfloat kstep = 1.0f;

GLfloat z = 0.0f;

GLfloat zstep = 0.5f;

void drawObject(){
     glBegin(GL_TRIANGLES);
        glVertex2i(50,-50);
        glVertex2i(0,50);
        glVertex2i(-50,-50);
     glEnd();
}

void drawOutline(){
     glBegin(GL_LINE_LOOP);
        glVertex2i(-100,100);
        glVertex2i(100,100);
        glVertex2i(100,-100);
        glVertex2i(-100,-100);
     glEnd();
}

void init(){
     glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void timerFunc(int value)
{
     if(k > 100 || k < -300)
        kstep = -kstep;

    k += kstep;

    if(z > 150 || z < 0)
        zstep = -zstep;

    z += zstep;

    glutPostRedisplay();
    glutTimerFunc(10,timerFunc,1);
}

void displayFunc() {
     glClear(GL_COLOR_BUFFER_BIT);

     glMatrixMode(GL_PROJECTION);

     glLoadIdentity();
     gluOrtho2D(-100.0f, 100.0f, -100.0f, 100.0f);
     glViewport(0, 300, 300, 300);
     glColor3f(1.0f, 0.0f, 0.0f);
     drawObject();

     glLoadIdentity();
     gluOrtho2D(k, k+200.0f, -100.0f, 100.0f);
     glViewport(300, 300, 300, 300);
     glColor3f(0.0f, 1.0f, 0.0f);
     drawObject();

     glLoadIdentity();
     gluOrtho2D(-100.0f, 100.0f, k, k+200.0f);
     glViewport(0, 0, 300, 300);
     glColor3f(0.0f, 0.0f, 1.0f);
     drawObject();

     glLoadIdentity();
     gluOrtho2D(-z,z,-z,z);
     glViewport(300, 0, 300, 300);
     glColor3f(0.0f, 0.0f, 0.0f);
     drawObject();

/*
     glLoadIdentity();
     gluOrtho2D(-200,200,-200,200);
     glViewport(0, 0, 600, 600);
     // GL_MODELVIEW utilizada para aplicar transformações geométricas às coordenadas dos objetos

     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();

     glColor3f(0.0f, 0.0f, 0.0f);
     glTranslatef(-100,-100,0);
     drawOutline();

     glLoadIdentity();
     glTranslatef(100,-100,0);
     drawOutline();

     glLoadIdentity();
     glTranslatef(-100,100,0);
     drawOutline();

     glLoadIdentity();
     glTranslatef(100,100,0);
     drawOutline();
*/
  
     glLoadIdentity();

     glutSwapBuffers();
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(600,600);
    glutCreateWindow("Viewing 2D");
    glutDisplayFunc(displayFunc);
    glutTimerFunc(10,timerFunc,1);
    init();
    glutMainLoop();
    return 0;
}