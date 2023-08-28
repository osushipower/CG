#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

GLfloat gl_x = 0.0f;
GLfloat gl_y = 0.0f;

void iteracao_mouse(int botao, int estado, int x, int y)
{
    if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
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

    glColor3f(0.0f, 0.0f, 1.0f);
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
    glutCreateWindow("CG - Exercicio 1");
    glutDisplayFunc(display);
    glutMouseFunc(iteracao_mouse);

    glClearColor(0, 0, 0, 0);

    glutMainLoop();

    return 0;
}