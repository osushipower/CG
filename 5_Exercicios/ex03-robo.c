#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.141592654

float theta = 0.0;
float up = 0.0;

void robot(){
    // Head
    glColor3f(0.5, 0.5, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.15, 0.7);
        glVertex2f(0.15, 0.7);
        glVertex2f(0.15, 0.4);
        glVertex2f(-0.15, 0.4);
    glEnd();

    // Chest
    glColor3f(0.7, 0.5, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.35, 0.4);
        glVertex2f(0.35, 0.4);
        glVertex2f(0.25, -0.20);
        glVertex2f(-0.25, -0.20);
    glEnd();

    // Legs
    glColor3f(0.5, 0.5, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(0.2, -0.2);
        glVertex2f(0.1, -0.2);
        glVertex2f(0.1, -0.75);
        glVertex2f(0.2, -0.75);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.2, -0.2);
        glVertex2f(-0.1, -0.2);
        glVertex2f(-0.1, -0.75);
        glVertex2f(-0.2, -0.75);
    glEnd();

    // Eyes and Mouth
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.10, 0.6);
        glVertex2f(-0.04, 0.6);
        glVertex2f(-0.045, 0.55);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(0.10, 0.6);
        glVertex2f(0.04, 0.6);
        glVertex2f(0.045, 0.55);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(-0.10, 0.5);
        glVertex2f(0.10, 0.5);
        glVertex2f(0.0, 0.45);
    glEnd();
}

void leftArm() {
    glColor3f(0.7, 0.5, 1.0);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.8, 0.35);
        glVertex2f(-0.30, 0.35);
        glVertex2f(-0.8, 0.30);
    glEnd();
}

void rightArm() {
    glBegin(GL_TRIANGLES);
        glVertex2f(0.8, 0.35);
        glVertex2f(0.30, 0.35);
        glVertex2f(0.8, 0.30);
    glEnd();
}

void onKeyPress(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_UP:
            up-=0.05;
            theta-=5;
            break;
        case GLUT_KEY_DOWN:
            up+=0.05;
            theta+=5;
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

    robot();

    glPushMatrix();
    glTranslatef(-0.30, 0.35, 0.0);
    glRotatef(theta, 0.0, 0.0, 1.0);
    glTranslatef(0.30, -0.35, 0.0);
    leftArm();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.30, 0.35, 0.0);
    glRotatef(-theta, 0.0, 0.0, 1.0);
    glTranslatef(-0.30, -0.35, 0.0);
    rightArm();
    glPopMatrix();

    glFlush();
}

int main ( int argc , char * argv [] ){
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50, 100);
    glutInitWindowSize (500, 500);
    glutCreateWindow("CG - Robo");
    glutDisplayFunc(display);
    glutSpecialFunc(onKeyPress);
    glutMainLoop ();
    return 0;
}