#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float angX = 0;
float angY = 0;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, -10, 10);
    glPushMatrix();
}

void cabelos() {
    // Cabelo Esquerda
    glColor3f(1.0f, 0.0f, 1.0f);
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(-10.0, 8.0, 2.5);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidSphere(3, 50, 50);
    glPopMatrix();

    glColor3f(2.0f, 0.5f, 1.0f);
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(-10.0, 8.0, -2.5);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidSphere(3, 50, 50);
    glPopMatrix();

    glColor3f(1.0f, 0.0f, 1.0f);
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(-7.0, 8.0, -7.5);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidSphere(3, 50, 50);
    glPopMatrix();

    glColor3f(2.0f, 0.5f, 1.0f);
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(-2.0, 8.0, -9.5);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidSphere(3, 50, 50);
    glPopMatrix();

    // Cabelo Direita
    glColor3f(1.0f, 0.0f, 1.0f);
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(10.0, 8.0, 2.5);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidSphere(3, 50, 50);
    glPopMatrix();

    glColor3f(2.0f, 0.5f, 1.0f);
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(10.0, 8.0, -2.5);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidSphere(3, 50, 50);
    glPopMatrix();

    glColor3f(1.0f, 0.0f, 1.0f);
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(7.0, 8.0, -7.5);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidSphere(3, 50, 50);
    glPopMatrix();

    glColor3f(2.0f, 0.5f, 1.0f);
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(2.0, 8.0, -9.5);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidSphere(3, 50, 50);
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);

    glPopMatrix();
    glPushMatrix();

    glRotatef(angX, 1, 0, 0);
    glRotatef(angY, 0, 1, 0);

    glColor3f(1.0, 1.0, 1.0);

    // Cabeça
    glPushMatrix();
    glScalef(0.8, 0.8, 0.8);
    glutSolidSphere(3, 50, 50);
    glPopMatrix();

    // Olho 1
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(5.0, 5.0, 9.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidSphere(3, 50, 50);
    glPopMatrix();

    // Olho 2
    glColor3f(0.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(-5.0, 5.0, 9.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidSphere(3, 50, 50);
    glPopMatrix();

    // Nariz
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glTranslatef(0.0, 0.0, 12.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidSphere(3, 50, 50);
    glPopMatrix();

    // Chapéu
    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glScalef(0.8, 0.8, 0.8);
    glTranslatef(0.0, 2.5, 0.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidCone(2, 3, 50, 50);
    glPopMatrix();

    cabelos();

    glFlush();
}

void timerFunc() {

    angY += 15;
    angY = fmod(angY, 360);

    glutPostRedisplay();
    glutTimerFunc(100, timerFunc, 0);
}

void transformacoes(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        angX += 15;
        break;
    case GLUT_KEY_DOWN:
        angX -= 15;
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(600, 600);
    glutCreateWindow("CG - Palhaco");
    glutDisplayFunc(display);
    glutSpecialFunc(transformacoes);
    glutTimerFunc(100, timerFunc, 0);
    init();
    glutMainLoop();
}