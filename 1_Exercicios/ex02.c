#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

GLfloat gl_x = 0.0f;
GLfloat gl_y = 0.0f;
GLfloat pointColor[3] = {0.0f, 0.0f, 1.0f};

void onKeyPress(unsigned char key, int x, int y) {
    if (key >= '0' && key <= '9') {
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
        
        pointColor[0] = colors[key - '0'][0];
        pointColor[1] = colors[key - '0'][1];
        pointColor[2] = colors[key - '0'][2];
    }
}

void onMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        GLfloat norm_x = (2.0f * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0f;
        GLfloat norm_y = 1.0f - (2.0f * y) / glutGet(GLUT_WINDOW_HEIGHT);

        gl_x = norm_x;
        gl_y = norm_y;
        glutPostRedisplay();
    };
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(pointColor[0], pointColor[1], pointColor[2]);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(gl_x, gl_y);
    glEnd();

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("CG - Exercicio 2");
    glutDisplayFunc(display);
    glutMouseFunc(onMouseClick);
    glutKeyboardFunc(onKeyPress);

    glClearColor(0, 0, 0, 0);

    glutMainLoop();

    return 0;
}