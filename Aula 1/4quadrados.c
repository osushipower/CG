#include <GL/glut.h>
#include <GL/gl.h>

float incX = 0.5;
float incY = 0.5;

void desenha(){
    glClearColor(0, 0, 0, 0); //Preto
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.125+incX, 0.125+incY);
        glVertex2f(0.125+incX, 0.125+incY);
        glVertex2f(0.125+incX, -0.125+incY);
        glVertex2f(-0.125+incX, -0.125+incY);
    glEnd();

    incY=-incY;
    glColor3f(1.0,0.0,0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.125+incX, 0.125+incY);
        glVertex2f(0.125+incX, 0.125+incY);
        glVertex2f(0.125+incX, -0.125+incY);
        glVertex2f(-0.125+incX, -0.125+incY);
    glEnd();

    incX=-incX;
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.125+incX, 0.125+incY);
        glVertex2f(0.125+incX, 0.125+incY);
        glVertex2f(0.125+incX, -0.125+incY);
        glVertex2f(-0.125+incX, -0.125+incY);
    glEnd();

    incY=-incY;
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.125+incX, 0.125+incY);
        glVertex2f(0.125+incX, 0.125+incY);
        glVertex2f(0.125+incX, -0.125+incY);
        glVertex2f(-0.125+incX, -0.125+incY);
    glEnd();

    glFlush();
}

int main ( int argc , char * argv [] ){
    glutInit(&argc , argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (50 ,100);
    glutInitWindowSize (400 ,400);
    glutCreateWindow ("Primeiro programa usando OpenGL");
    glutDisplayFunc (desenha);
    glutMainLoop ();
    return 0;
}