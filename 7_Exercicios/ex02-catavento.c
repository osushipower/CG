#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int rotationDirection = -1;
float rotationAngle = 0.0;
float speed = 0.0;
int animated = 0;

void drawPieces()
{
    // Right
    glColor3f(1.0, 0.8, 1.0); // Pinkish
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0, 0);
    glVertex3f(0.3, -0.3, 0);
    glVertex3f(0.6, 0, 0);
    glEnd();

    glColor3f(1.0, 0.0, 0.0); // Red
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0, 0);
    glVertex3f(0.3, 0.3, 0);
    glVertex3f(0.3, 0, 0);
    glEnd();

    // Bottom
    glColor3f(1.0, 0.8, 1.0); // Pinkish
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0, 0);
    glVertex3f(-0.3, -0.3, 0);
    glVertex3f(0, -0.6, 0);
    glEnd();

    glColor3f(1.0, 0.0, 0.0); // Red
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0, 0);
    glVertex3f(0, -0.3, 0);
    glVertex3f(0.3, -0.3, 0);
    glEnd();

    // Left
    glColor3f(1.0, 0.8, 1.0); // Pinkish
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0, 0);
    glVertex3f(-0.3, 0.3, 0);
    glVertex3f(-0.6, 0, 0);
    glEnd();

    glColor3f(1.0, 0.0, 0.0); // Red
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0, 0);
    glVertex3f(-0.3, 0.0, 0);
    glVertex3f(-0.3, -0.3, 0);
    glEnd();

    // Top
    glColor3f(1.0, 0.8, 1.0); // Pinkish
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0, 0);
    glVertex3f(0.3, 0.3, 0);
    glVertex3f(0.0, 0.6, 0);
    glEnd();

    glColor3f(1.0, 0.0, 0.0); // Red
    glBegin(GL_TRIANGLES);
    glVertex3f(0, 0, 0);
    glVertex3f(0.0, 0.3, 0);
    glVertex3f(-0.3, 0.3, 0);
    glEnd();
}

void drawStick()
{
    glColor3f(0.5, 0.35, 0.5);
    glBegin(GL_QUADS);
    glVertex2f(-0.02, 0);
    glVertex2f(0.02, 0);
    glVertex2f(0.02, -1);
    glVertex2f(-0.02, -1);
    glEnd();
}

void drawCenter(float x, float y)
{
    int i;
    int numPoints = 100;
    float radiusX = 0.02;
    float radiusY = 0.02;

    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_POLYGON);
    for (i = 0; i < numPoints; i++)
    {
        float theta = 2.0f * 3.1415926f * i / numPoints;
        float px = x + radiusX * cos(theta);
        float py = y + radiusY * sin(theta);
        glVertex2f(px, py);
    }
    glEnd();
}

void drawPinwheel()
{
    drawStick();

    glTranslatef(0.0, 0.0, -1.0);
    glRotatef(rotationAngle, 0.0, 0.0, 1.0);

    glPushMatrix();
    drawPieces();
    drawCenter(0, 0);
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity();

    drawPinwheel();

    glutSwapBuffers();
}

void timerFunc()
{
    if (animated == 1) {
        if (speed < 10) speed += 1.0;
    } else if (animated == -1){
        if (speed > 0.0) speed -= 1.0;   
    }

    if (speed == 0.0) animated = 0;

    rotationAngle += rotationDirection * speed;
    rotationAngle = fmod(rotationAngle, 360);
    
    glutPostRedisplay();
	glutTimerFunc(50, timerFunc, 0);
}

void mouseFunc(int button, int state, int x, int y)
{
    switch (button)
    {
    case GLUT_LEFT_BUTTON:
        if (state == GLUT_DOWN) {
            animated = 1;
        }
        break;
    case GLUT_RIGHT_BUTTON:
        if (state == GLUT_DOWN) {
            animated = -1;
        }
        break;
    default:
        break;
    }
}

void onKeyPress(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        if (speed < 5.0)
        {
            speed += 1.0;
        }
        break;
    case GLUT_KEY_LEFT:
        if (speed > 0.0)
        {
            speed -= 1.0;
        }
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("CG - Catavento");
    glutDisplayFunc(display);
    glutSpecialFunc(onKeyPress);
    glutMouseFunc(mouseFunc);
    glutTimerFunc(100, timerFunc, 0);
    glutMainLoop();
    return 0;
}