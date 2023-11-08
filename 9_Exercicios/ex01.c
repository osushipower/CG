#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// Define region codes for the four regions
#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

// Define the viewport boundaries
const int xMin = 100;
const int xMax = 400;
const int yMin = 100;
const int yMax = 400;

typedef struct {
    int x, y;
} Point; 

int click_count = 0;
Point points[2] = {{.x = 0, .y = 0}, {.x = 0, .y = 0}};

// Function to compute the region code for a point (x, y)
int computeRegionCode(int x, int y) {
    int code = INSIDE;

    if (x < xMin)
        code |= LEFT;
    else if (x > xMax)
        code |= RIGHT;

    if (y < yMin)
        code |= BOTTOM;
    else if (y > yMax)
        code |= TOP;

    return code;
}

// Function to clip a line segment using the Cohen-Sutherland algorithm
void cohenSutherlandClippingAlgorithm(int x1, int y1, int x2, int y2) {
    int code1 = computeRegionCode(x1, y1);
    int code2 = computeRegionCode(x2, y2);
    int accept = 0;

    while (1) {
        if (!(code1 | code2)) {
            // Line is completely inside the region
            accept = 1;
            break;
        } else if (code1 & code2) {
            // Line is completely outside the region
            break;
        } else {
            // Clip the line and update the endpoints
            int x, y;

            // Pick the first point outside the region
            int codeOut = code1 ? code1 : code2;

            // Find the intersection point
            if (codeOut & TOP) {
                x = x1 + (x2 - x1) * (yMax - y1) / (y2 - y1);
                y = yMax;
            } else if (codeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (yMin - y1) / (y2 - y1);
                y = yMin;
            } else if (codeOut & RIGHT) {
                y = y1 + (y2 - y1) * (xMax - x1) / (x2 - x1);
                x = xMax;
            } else {
                y = y1 + (y2 - y1) * (xMin - x1) / (x2 - x1);
                x = xMin;
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeRegionCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeRegionCode(x2, y2);
            }
        }
    }

    if (accept) {
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINES);
            glVertex2i(x1, y1);
            glVertex2i(x2, y2);
        glEnd();
    }
}

void mouseEvent(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (click_count < 2) {
            points[click_count].x = x;
            points[click_count].y = glutGet(GLUT_WINDOW_HEIGHT) - y;
            click_count++;
        }

        if (click_count == 2) {
            glutPostRedisplay();
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    

    if (click_count == 2) {
        // Caso queira ver a linha original fora da viewport
        
        // glColor3f(1.0, 0.0, 0.0);
        // glBegin(GL_LINES);
        // glVertex2i(points[0].x, points[0].y);
        // glVertex2i(points[1].x, points[1].y);
        // glEnd();

        printf("x1: %d | x2: %d\n", points[0].x, points[0].y);
        printf("x2: %d | y2: %d\n", points[1].x, points[1].y);
        cohenSutherlandClippingAlgorithm(points[0].x, points[0].y, points[1].x, points[1].y);
        click_count = 0;
    }

    glFlush();
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Aula 9 - Algoritmo Cohen Sutherland - Linha");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseEvent);
    glutMainLoop();

    return 0;
}