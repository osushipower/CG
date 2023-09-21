#include <GL/freeglut.h>
#include <stdio.h>

typedef struct
{
    int x, y;
} Point;

Point circle_vertex = {.x = 0, .y = 0};
int radius = 100;

void drawCircle(int origin_x, int origin_y, int r)
{
    int x = 0, y = r;
    int decision = 3 - 2 * r; // Parâmetro de decisão inicial

    while (x <= y)
    {
        glBegin(GL_POINTS);
        // Primeiro Quadrante
        glVertex2i(origin_x + x, origin_y + y);
        glVertex2i(origin_x + y, origin_y + x);

        // Segundo Quadrante
        glVertex2i(origin_x + x, origin_y - y);
        glVertex2i(origin_x + y, origin_y - x);

        // Terceiro Quadrante
        glVertex2i(origin_x - x, origin_y - y);
        glVertex2i(origin_x - y, origin_y - x);

        // Quarto Quadrante
        glVertex2i(origin_x - x, origin_y + y);
        glVertex2i(origin_x - y, origin_y + x);
        
        glEnd();

        x++;

        if (decision > 0)
        {
            y--;
            decision = decision + 4 * (x - y) + 10;
        }
        else
        {
            decision = decision + 4 * x + 6;
        }
    }
}

void onKeyPress(unsigned char key, int x, int y)
{
    if (key >= '1' && key <= '9')
    {
        radius = (key - '0') * 10;
    }
}

void mouseEvent(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        circle_vertex.x = x;
        circle_vertex.y = glutGet(GLUT_WINDOW_HEIGHT) - y;
        glutPostRedisplay();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircle(circle_vertex.x, circle_vertex.y, radius);
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("CG - Bresenham (Circulo) - Exercicio 1");

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);

    glutDisplayFunc(display);
    glutMouseFunc(mouseEvent);
    glutKeyboardFunc(onKeyPress);

    glutMainLoop();
    return 0;
}