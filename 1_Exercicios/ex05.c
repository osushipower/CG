#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>

GLfloat color[3] = {0.0f, 0.0f, 1.0f};

typedef struct
{
    GLfloat x, y;
} Points;
// Definindo uma estrutura compatível para ambos linha e triângulo

Points line_points[2];
Points triangle_points[3];

int triangle_points_count = 0; // Número de
int line_point_count = 0; // Número de vértices para linha
int triangleMode = 0; // Começa Falso

void drawLine(float x1, float y1, float x2, float y2)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    glColor3fv(color);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3fv(color);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (triangleMode)
    {
        if (triangle_points_count == 3)
        {
            drawTriangle(triangle_points[0].x, triangle_points[0].y,
                         triangle_points[1].x, triangle_points[1].y,
                         triangle_points[2].x, triangle_points[2].y);
        }
    }
    else
    {
        if (line_point_count == 2)
        {
            drawLine(line_points[0].x, line_points[0].y, line_points[1].x, line_points[1].y);
        }
    }
    glFlush();
}

void onMouseClick(int button, int state, int x, int y)
{

    GLfloat normalized_x = (2.0f * x) / glutGet(GLUT_WINDOW_WIDTH) - 1.0f;
    GLfloat normalized_y = 1.0f - (2.0f * y) / glutGet(GLUT_WINDOW_HEIGHT);

    if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON)
    {
        if (triangleMode)
        {
            if (triangle_points_count < 3)
            {
                triangle_points[triangle_points_count].x = normalized_x;
                triangle_points[triangle_points_count].y = normalized_y;
                triangle_points_count++;
            }
            else if (triangle_points_count == 3)
            {
                triangle_points[0].x = normalized_x;
                triangle_points[0].y = normalized_y;
                triangle_points_count = 1;
                glutPostRedisplay();
            }
        }
        else
        {
            if (line_point_count < 2)
            {
                line_points[line_point_count].x = normalized_x;
                line_points[line_point_count].y = normalized_y;
                line_point_count++;
            }
            else if (line_point_count == 2)
            {
                line_points[0].x = normalized_x;
                line_points[0].y = normalized_y;
                line_point_count = 1;
                glutPostRedisplay();
            }
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

        color[0] = colors[key - '0'][0];
        color[1] = colors[key - '0'][1];
        color[2] = colors[key - '0'][2];
    }
    else
    {
        switch (key)
        {
        case 't':
        case 'T':
            triangleMode = 1;
            break;
        case 'r':
        case 'R':
            triangleMode = 0;
            break;
        }
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("CG - Exercicio 5");
    glutDisplayFunc(display);
    glutMouseFunc(onMouseClick);
    glutKeyboardFunc(onKeyPress);

    glClearColor(0, 0, 0, 0);

    glutMainLoop();
    return 0;
}