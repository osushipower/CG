#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Eduardo Augusto Saito
// Tales Miguel

float thetaX = 0.0;
float thetaY = 0.0;
float theta = 0.0;
int subindo = 0;

void cubo()
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.12, 0.12, 0.12);
    glVertex3f(0.12, 0.12, 0.12);
    glVertex3f(0.12, -0.12, 0.12);
    glVertex3f(-0.12, -0.12, 0.12);
    glEnd();
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.12, 0.12, -0.12);
    glVertex3f(0.12, 0.12, -0.12);
    glVertex3f(0.12, -0.12, -0.12);
    glVertex3f(-0.12, -0.12, -0.12);
    glEnd();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.12, -0.12, 0.12);
    glVertex3f(0.12, 0.12, 0.12);
    glVertex3f(0.12, 0.12, -0.12);
    glVertex3f(0.12, -0.12, -0.12);
    glEnd();
    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.12, -0.12, 0.12);
    glVertex3f(-0.12, 0.12, 0.12);
    glVertex3f(-0.12, 0.12, -0.12);
    glVertex3f(-0.12, -0.12, -0.12);
    glEnd();
    glColor3f(1.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.12, 0.12, 0.12);
    glVertex3f(0.12, 0.12, 0.12);
    glVertex3f(0.12, 0.12, -0.12);
    glVertex3f(-0.12, 0.12, -0.12);
    glEnd();
    glColor3f(0.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.12, -0.12, 0.12);
    glVertex3f(0.12, -0.12, 0.12);
    glVertex3f(0.12, -0.12, -0.12);
    glVertex3f(-0.12, -0.12, -0.12);
    glEnd();
}

void desenhaMembro(float scaleX, float scaleY, float scaleZ, float  tX, float tY, float tZ, float rX, float rY, float rZ){
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(thetaX, 1.0, 0.0, 0.0);
    glRotatef(thetaY, 0.0, 1.0, 0.0);
    glRotatef(theta, rX, rY, rZ);
    glScalef(scaleX, scaleY, scaleZ);
    glTranslatef(tX, tY, tZ);
    cubo();
    glPopMatrix();
}

void desenha()
{
    glClearColor(0, 0, 0, 0); // Preto
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Cabeça
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(thetaX, 1.0, 0.0, 0.0);
    glRotatef(thetaY, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.5, 0.0);
    cubo();
    glPopMatrix();

    // Corpo
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(thetaX, 1.0, 0.0, 0.0);
    glRotatef(thetaY, 0.0, 1.0, 0.0);
    glScalef(1.5, 2.0, 1.5);
    glTranslatef(0.0, 0.05, 0.0);
    cubo();
    glPopMatrix();

    // Perna 1 L1
    desenhaMembro(0.5, 1.5, 0.5, -0.2, -0.2, 0.0, 1.0, 0.0, 0.0);

    // Perna 1 L2
    desenhaMembro(0.5, 1.5, 0.5, -0.2, -0.45, 0.0, 1.0, 0.0, 0.0);

    // Perna 2 R1
    desenhaMembro(0.5, 1.5, 0.5, 0.2, -0.2, 0.0, -1.0, 0.0, 0.0);


    // Perna 2 R2
    desenhaMembro(0.5, 1.5, 0.5, 0.2, -0.45, 0.0, -1.0, 0.0, 0.0);


    // Braço Esquerdo L1
    desenhaMembro(1.5, 0.5, 0.5, 0.1, 0.3, 0.0, 0.0, 0.0, -1.0);

    // Braço Esquerdo L2
    desenhaMembro(1.5, 0.5, 0.5, 0.35, 0.3, 0.0, 0.0, 0.0, -1.0);


    // Braço Direito L1
    desenhaMembro(1.5, 0.5, 0.5, -0.1, 0.3, 0.0, 0.0, 0.0, 1.0);


    // Braço Direito L2
    desenhaMembro(1.5, 0.5, 0.5, -0.35, 0.3, 0.0, 0.0, 0.0, 1.0);


    glFlush();
}

void timerFunc() {
    if (theta == 45.0) {
        subindo = -1;
    } else if (theta == -50.0)
    {
        subindo = 1;
    }
    
    if (subindo == 1) {
        theta += 1.0;
    } else {
        theta -= 1.0;
    }

    glutPostRedisplay();
    glutTimerFunc(100, timerFunc, 0);
}

void tecladoEspecial(int tecla, int x, int y)
{
    switch (tecla)
    {
    case GLUT_KEY_RIGHT:
        thetaY += 2;
        break;
    case GLUT_KEY_LEFT:
        thetaY -= 2;
        break;
    case GLUT_KEY_UP:
        thetaX += 2;
        break;
    case GLUT_KEY_DOWN:
        thetaX -= 2;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cubo");
    glutDisplayFunc(desenha);
    glutSpecialFunc(tecladoEspecial);
    glutTimerFunc(100, timerFunc, 0);
    glutMainLoop();
    return 0;
}