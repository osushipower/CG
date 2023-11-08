#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

GLfloat k = -2.0f;

GLfloat kstep = 0.05f;

GLfloat z = 2.0f;

GLfloat zstep = 0.05f;

void init(){
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(1.0, 1.0, 1.0,   //posição da câmera (P_0)
              0.0, 0.0, 0.0,   //para onde a câmera aponta (P_ref)
              0.0, 1.0, 0.0); //vetor view-up (V)
}

void drawCube(){
     glColor3f(1.0,0.0,0.0);
     glBegin(GL_POLYGON);
        glVertex3f(-0.5,-0.5,0.5);
        glVertex3f(0.5,-0.5,0.5);
        glVertex3f(0.5,0.5,0.5);
        glVertex3f(-0.5,0.5,0.5);
     glEnd();
     glColor3f(0.0,1.0,0.0);
     glBegin(GL_POLYGON);
        glVertex3f(0.5,0.5,0.5);
        glVertex3f(0.5,-0.5,0.5);
        glVertex3f(0.5,-0.5,-0.5);
        glVertex3f(0.5,0.5,-0.5);
     glEnd();
     glColor3f(0.0,0.0,1.0);
     glBegin(GL_POLYGON);
        glVertex3f(0.5,-0.5,0.5);
        glVertex3f(-0.5,-0.5,0.5);
        glVertex3f(-0.5,-0.5,-0.5);
        glVertex3f(0.5,-0.5,-0.5);
     glEnd();
     glColor3f(1.0,1.0,0.0);
     glBegin(GL_POLYGON);
        glVertex3f(-0.5,0.5,0.5);
        glVertex3f(0.5,0.5,0.5);
        glVertex3f(0.5,0.5,-0.5);
        glVertex3f(-0.5,0.5,-0.5);
     glEnd();
     glColor3f(0.0,1.0,1.0);
     glBegin(GL_POLYGON);
        glVertex3f(-0.5,-0.5,-0.5);
        glVertex3f(-0.5,0.5,-0.5);
        glVertex3f(0.5,0.5,-0.5);
        glVertex3f(0.5,-0.5,-0.5);
     glEnd();
     glColor3f(1.0,1.0,1.0);
     glBegin(GL_POLYGON);
        glVertex3f(-0.5,0.5,-0.5);
        glVertex3f(-0.5,-0.5,-0.5);
        glVertex3f(-0.5,-0.5,0.5);
        glVertex3f(-0.5,0.5,0.5);
     glEnd();
}

void timerFunc(int value)
{
    if(k > 0.0 || k < -4.0)
        kstep = -kstep;

    k += kstep;

    if(z > 4.0 || z < 1.0)
        zstep = -zstep;

    z += zstep;

    glutPostRedisplay();

    glutTimerFunc(50,timerFunc, 1);
}

void displayFunc() {
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     glOrtho(-2.0, 2.0, -2.0, 2.0, 0.0, 3.0);
     glViewport(0, 300, 300, 300);
     drawCube();

     glLoadIdentity();
     glOrtho(k, k+4.0, -2.0, 2.0, 0.0, 3.0);
     glViewport(300, 300, 300, 300);
     drawCube();

     glLoadIdentity();
     glOrtho(-2.0, 2.0f, k, k+4.0, 0.0, 3.0);
     glViewport(0, 0, 300, 300);
     drawCube();

     glLoadIdentity();
     glOrtho(-z,z,-z,z,0.0,3.0);
     glViewport(300, 0, 300, 300);
     drawCube();

     glutSwapBuffers();
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(600,600);
    glutCreateWindow("Viewing 3D");
    glutDisplayFunc(displayFunc);
    glutTimerFunc(50,timerFunc,1);
    init();
    glutMainLoop();
    return 0;
}