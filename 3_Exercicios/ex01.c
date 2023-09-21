#include <GL/freeglut.h>
#include <stdio.h>

typedef struct {
    int x, y;
} Point; 

int click_count = 0;
Point points[2] = {{.x = 0, .y = 0}, {.x = 0, .y = 0}};
GLfloat color[3] = {0.0f, 0.0f, 1.0f};

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

void draw_pixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void bresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        draw_pixel(x1, y1);

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void onKeyPress(unsigned char key, int x, int y)
{
    if (key >= '0' && key <= '9')
    {
        color[0] = colors[key - '0'][0];
        color[1] = colors[key - '0'][1];
        color[2] = colors[key - '0'][2];
    }
}

void mouseEvent(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (click_count < 2) {
            points[click_count].x = x;
            points[click_count].y = glutGet(GLUT_WINDOW_HEIGHT) - y;
            click_count++;
        }

        if (click_count == 2) {
            glColor3f(color[0], color[1], color[2]);
            bresenham(points[0].x, points[0].y, points[1].x, points[1].y);
            click_count = 0;
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("CG - Aula 3 - Exercicio 1");

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