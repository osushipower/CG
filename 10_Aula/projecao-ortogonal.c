#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

double theta = 0.0;

double w = 300.0;
double h = 300.0;

void init(){
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); 
  gluLookAt(2.0, 2.0, 2.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-2.0, 2.0, -2.0, 2.0, 0.0, 4.0);
  glViewport(0, 0, w, h);
  
  //imprime as matrized GL_PROJECTION e GL_MODELVIEW
  printf("M_ortho = \n");
  float matrix[16];
  int i,j;
  glGetFloatv(GL_PROJECTION_MATRIX,matrix);
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      printf("%f ",matrix[i + j * 4]);
    }
    printf("\n");
  }
  printf("\n");
  printf("\n\nM_wc,vc = \n");
  glGetFloatv(GL_MODELVIEW_MATRIX,matrix);
  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      printf("%f ",matrix[i + j * 4]);
    }
    printf("\n");
  }
  printf("\n");
}

void cube(){
  glColor3f(1.0,0.0,0.0);
  glBegin(GL_POLYGON);
    glVertex3f(-0.5,-0.5,0.5);
    glVertex3f(0.5,-0.5,0.5);
    glVertex3f(0.5,0.5,0.5);
    glVertex3f(-0.5,0.5,0.5);
  glEnd();
  glColor3f(0.0,1.0,0.0);
  glBegin(GL_POLYGON);
    glVertex3f(0.5,0.5,0.5);
    glVertex3f(0.5,-0.5,0.5);
    glVertex3f(0.5,-0.5,-0.5);
    glVertex3f(0.5,0.5,-0.5);
  glEnd();
  glColor3f(0.0,0.0,1.0);
  glBegin(GL_POLYGON);
    glVertex3f(0.5,-0.5,0.5);
    glVertex3f(-0.5,-0.5,0.5);
    glVertex3f(-0.5,-0.5,-0.5);
    glVertex3f(0.5,-0.5,-0.5);
  glEnd();
  glColor3f(1.0,1.0,0.0);
  glBegin(GL_POLYGON);
    glVertex3f(-0.5,0.5,0.5);
    glVertex3f(0.5,0.5,0.5);
    glVertex3f(0.5,0.5,-0.5);
    glVertex3f(-0.5,0.5,-0.5);
  glEnd();
  glColor3f(0.0,1.0,1.0);
  glBegin(GL_POLYGON);
    glVertex3f(-0.5,-0.5,-0.5);
    glVertex3f(-0.5,0.5,-0.5);
    glVertex3f(0.5,0.5,-0.5);
    glVertex3f(0.5,-0.5,-0.5);
  glEnd();
  glColor3f(1.0,1.0,1.0);
  glBegin(GL_POLYGON);
    glVertex3f(-0.5,0.5,-0.5);
    glVertex3f(-0.5,-0.5,-0.5);
    glVertex3f(-0.5,-0.5,0.5);
    glVertex3f(-0.5,0.5,0.5);
  glEnd();
}

void displayFunc() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  cube();
  glFlush();
  //glutSwapBuffers();
}

void timerFunc(int value)
{
  theta+=0.1;
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(1.0*sin(theta)+1.0*cos(theta),1.0,1.0*cos(theta)-1.0*sin(theta),        
    0.0, 0.0, 0.0,
    0.0, 1.0, 0.0);

  glutPostRedisplay();

  glutTimerFunc(50,timerFunc, 1);
}

int main(int argc, char *argv[]){
  glutInit(&argc,argv);
  //glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50,50);
  glutInitWindowSize(w,h);
  glutCreateWindow("Viewing 3D - Projecao Ortogonal");
  glutDisplayFunc(displayFunc);
  //glutTimerFunc(60,timerFunc,1);
  init();
  glutMainLoop();
  return 0;
}