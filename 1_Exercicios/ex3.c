#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

int pointCount = 0;
GLfloat points[2][2] = {{0.0f, 0.0f}, {0.0f, 0.0f}};
GLfloat lineColor[3] = {0.0f, 0.0f, 1.0f};
int lineMode = 0;

void drawLine(float x1, float y1, float x2, float y2)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    glColor3fv(lineColor);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawLine(points[0][0], points[0][1], points[1][0], points[1][1]);
    glFlush();
}

void onMouseClick(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    {
        if (lineMode == 0 || lineMode == 2)
        {
            points[0][0] = (2.0f * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0f;
            points[0][1] = 1.0f - (2.0f * y) / glutGet(GLUT_WINDOW_HEIGHT);
            lineMode = 1;
            glutPostRedisplay();
        }
        else if (lineMode == 1)
        {
            points[1][0] = (2.0f * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0f;
            points[1][1] = 1.0f - (2.0f * y) / glutGet(GLUT_WINDOW_HEIGHT);
            lineMode = 2;
            glutPostRedisplay();
        }
    }
}

void onKeyPress(unsigned char key, int x, int y)
{
    if (key >= '0' && key <= '9')
    {
        GLfloat colors[10][3] = {
            {0.0f, 0.0f, 1.0f}, // Blue
            {1.0f, 0.0f, 0.0f}, // Red
            {0.0f, 1.0f, 0.0f}, // Green
            {1.0f, 1.0f, 0.0f}, // Yellow
            {1.0f, 0.0f, 1.0f}, // Magenta
            {0.0f, 1.0f, 1.0f}, // Cyan
            {1.0f, 0.5f, 0.0f}, // Orange
            {0.5f, 0.5f, 0.5f}, // Gray
            {0.5f, 0.0f, 0.5f}, // Purple
            {0.0f, 0.5f, 0.5f}  // Teal
        };

        lineColor[0] = colors[key - '0'][0];
        lineColor[1] = colors[key - '0'][1];
        lineColor[2] = colors[key - '0'][2];

        drawLine(points[0][0], points[0][1], points[1][0], points[1][1]);
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("CG - Exercicio 3");
    glutDisplayFunc(display);
    glutMouseFunc(onMouseClick);
    glutKeyboardFunc(onKeyPress);

    glClearColor(0, 0, 0, 0);

    glutMainLoop();
    return 0;
}