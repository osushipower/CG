#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int rotationDirection = 1; // 1 para sentido horario, -1 para anti-heroi
float rotationAngle = 0.0;

void drawPetal(float x, float y) {
    int i;
    int numPoints = 100;
    float radiusX = 0.2;
    float radiusY = 0.5;

    glBegin(GL_POLYGON);
    for (i = 0; i < numPoints; i++) {
        float theta = 2.0f * 3.1415926f * i / numPoints;
        float px = x + radiusX * cos(theta);
        float py = y + radiusY * sin(theta);
        glVertex2f(px, py);
    }
    glEnd();
}

void drawStem() {
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2f(-0.05, 0);
    glVertex2f(0.05, 0);
    glVertex2f(0.05, -1);
    glVertex2f(-0.05, -1);
    glEnd();
}

void drawCenter(float x, float y) {
    int i;
    int numPoints = 100;
    float radiusX = 0.2;
    float radiusY = 0.2;

    glColor3f(1.0, 1.0, 0.0);

    glBegin(GL_POLYGON);
    for (i = 0; i < numPoints; i++) {
        float theta = 2.0f * 3.1415926f * i / numPoints;
        float px = x + radiusX * cos(theta);
        float py = y + radiusY * sin(theta);
        glVertex2f(px, py);
    }
    glEnd();
}


void drawFlower() {
    int i;
    int numPetals = 6;

    drawStem();

    glTranslatef(0.0, 0.0, -1.0);
    glRotatef(rotationAngle, 0.0, 0.0, 1.0);

    glColor3f(1.0, 0.0, 0.0);
    for (i = 0; i < numPetals; i++) {
        glPushMatrix();
        glRotatef(i * 60.0, 0.0, 0.0, 1.0);
        drawPetal(0.0, 0.0);
        glPopMatrix();
    }

    drawCenter(0.0, 0.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawFlower();

    glutSwapBuffers();
}

void onKeyPress(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_RIGHT:
            rotationDirection = 1;
            break;
        case GLUT_KEY_LEFT:
            rotationDirection = -1;
            break;
        default:
            break;
    }
    rotationAngle += rotationDirection * 1.0;
    glutPostRedisplay();
}

int main ( int argc , char * argv [] ){
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50 ,100);
    glutInitWindowSize (500, 500);
    glutCreateWindow ("CG - Flor");
    glutDisplayFunc(display);
    glutSpecialFunc(onKeyPress);
    glutMainLoop();
    return 0;
}