#include <math.h>
#include <GL/glut.h>

int n = 10;
float ang = 0;

void desenha(){
    int i;
    glClearColor(0, 0, 0, 0); //Preto
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINE_LOOP);
        for(i=0;i<n;i++){
            glVertex2f(0.5*cos(ang),0.5*sin(ang));
            ang = ang+(2*M_PI)/n;
        }
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