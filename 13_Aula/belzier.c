#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Point {
  float x;
  float y;
  float z;
};

float t = 0.0;
float tstep = 0.01;
struct Point P0;
struct Point P1;
struct Point P2;
struct Point P3;
struct Point P;

struct Point a;
struct Point b;
struct Point c;
struct Point d;
struct Point e;


GLfloat light0_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

GLfloat angleX = 0.0f;
GLfloat angleY = 0.0f;
GLfloat angleZ = 0.0f;

void lightning(){
    glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,white);

  //Fonte de Luz Direcional - Efeito de Holofote
  GLfloat light1_pos[] = {-2.0, -2.0, -2.0f, 1.0f};
  glLightfv(GL_LIGHT1,GL_POSITION,light1_pos);
  glLightfv(GL_LIGHT1,GL_DIFFUSE, white);
  glLightfv(GL_LIGHT1,GL_SPECULAR, white);
  GLfloat direction[] = {2.0f, 2.0f, 2.0f};
  glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,direction);       //vetor direção
  glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,30.0f);               //espalhamento angular
  glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,0.5f);    

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void init(){
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.0, 1.0, 3.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0, 3.0, -3.0, 3.0, 0.0, 8.0);
    glViewport(0, 0, 500, 500);
    glShadeModel(GL_SMOOTH);
    lightning();

    P0.x = -2.0;
    P0.y = -2.0;
    P0.z = 0.0;
    P1.x = -2.0;
    P1.y = 2.0;
    P1.z = 0.0;
    P2.x = 2.0;
    P2.y = 2.0;
    P2.z = 0.0;
    P3.x = 2.0;
    P3.y = -2.0;
    P3.z = 0.0;
}

void cube(){
    GLfloat shininess;
    GLfloat diffuse[4];
    GLfloat specular[4];

    shininess = 65.0;
    diffuse[0] = 0.65;
    diffuse[1] = 0.0;
    diffuse[2] = 0.0;
    diffuse[3] = 1.0;
    specular[0] = 1.0;
    specular[1] = 1.0;
    specular[2] = 1.0;
    specular[3] = 1.0;
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
    glMaterialf(GL_FRONT,GL_SHININESS,shininess);

    glBegin(GL_POLYGON);
        glNormal3f(-0.5,-0.5,0.5);
        glVertex3f(-0.5,-0.5,0.5);
        glNormal3f(0.5,-0.5,0.5);
        glVertex3f(0.5,-0.5,0.5);
        glNormal3f(0.5,0.5,0.5);
        glVertex3f(0.5,0.5,0.5);
        glNormal3f(-0.5,0.5,0.5);
        glVertex3f(-0.5,0.5,0.5);
    glEnd();

    shininess = 65.0;
    diffuse[0] = 0.0;
    diffuse[1] = 0.65;
    diffuse[2] = 0.0;
    diffuse[3] = 1.0;
    specular[0] = 1.0;
    specular[1] = 1.0;
    specular[2] = 1.0;
    specular[3] = 1.0;
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
    glMaterialf(GL_FRONT,GL_SHININESS,shininess);

    glBegin(GL_POLYGON);
        glNormal3f(0.5,0.5,0.5);
        glVertex3f(0.5,0.5,0.5);
        glNormal3f(0.5,-0.5,0.5);
        glVertex3f(0.5,-0.5,0.5);
        glNormal3f(0.5,-0.5,-0.5);
        glVertex3f(0.5,-0.5,-0.5);
        glNormal3f(0.5,0.5,-0.5);
        glVertex3f(0.5,0.5,-0.5);
    glEnd();

    shininess = 65.0;
    diffuse[0] = 0.0;
    diffuse[1] = 0.0;
    diffuse[2] = 0.65;
    diffuse[3] = 1.0;
    specular[0] = 1.0;
    specular[1] = 1.0;
    specular[2] = 1.0;
    specular[3] = 1.0;
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
    glMaterialf(GL_FRONT,GL_SHININESS,shininess);

    glBegin(GL_POLYGON);
        glNormal3f(0.5,-0.5,0.5);
        glVertex3f(0.5,-0.5,0.5);
        glNormal3f(-0.5,-0.5,0.5);
        glVertex3f(-0.5,-0.5,0.5);
        glNormal3f(-0.5,-0.5,-0.5);
        glVertex3f(-0.5,-0.5,-0.5);
        glNormal3f(0.5,-0.5,-0.5);
        glVertex3f(0.5,-0.5,-0.5);
    glEnd();

    shininess = 65.0;
    diffuse[0] = 0.65;
    diffuse[1] = 0.65;
    diffuse[2] = 0.0;
    diffuse[3] = 1.0;
    specular[0] = 1.0;
    specular[1] = 1.0;
    specular[2] = 1.0;
    specular[3] = 1.0;
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
    glMaterialf(GL_FRONT,GL_SHININESS,shininess);

    glBegin(GL_POLYGON);
        glNormal3f(-0.5,0.5,0.5);
        glVertex3f(-0.5,0.5,0.5);
        glNormal3f(0.5,0.5,0.5);
        glVertex3f(0.5,0.5,0.5);
        glNormal3f(0.5,0.5,-0.5);
        glVertex3f(0.5,0.5,-0.5);
        glNormal3f(-0.5,0.5,-0.5);
        glVertex3f(-0.5,0.5,-0.5);
    glEnd();

    shininess = 65.0;
    diffuse[0] = 0.0;
    diffuse[1] = 0.65;
    diffuse[2] = 0.65;
    diffuse[3] = 1.0;
    specular[0] = 1.0;
    specular[1] = 1.0;
    specular[2] = 1.0;
    specular[3] = 1.0;
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
    glMaterialf(GL_FRONT,GL_SHININESS,shininess);

    glBegin(GL_POLYGON);
        glNormal3f(-0.5,-0.5,-0.5);
        glVertex3f(-0.5,-0.5,-0.5);
        glNormal3f(-0.5,0.5,-0.5);
        glVertex3f(-0.5,0.5,-0.5);
        glNormal3f(0.5,0.5,-0.5);
        glVertex3f(0.5,0.5,-0.5);
        glNormal3f(0.5,-0.5,-0.5);
        glVertex3f(0.5,-0.5,-0.5);
    glEnd();

    shininess = 65.0;
    diffuse[0] = 0.65;
    diffuse[1] = 0.65;
    diffuse[2] = 0.65;
    diffuse[3] = 1.0;
    specular[0] = 1.0;
    specular[1] = 1.0;
    specular[2] = 1.0;
    specular[3] = 1.0;
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR,specular);
    glMaterialf(GL_FRONT,GL_SHININESS,shininess);

    glBegin(GL_POLYGON);
        glNormal3f(-0.5,0.5,-0.5);
        glVertex3f(-0.5,0.5,-0.5);
        glNormal3f(-0.5,-0.5,-0.5);
        glVertex3f(-0.5,-0.5,-0.5);
        glNormal3f(-0.5,-0.5,0.5);
        glVertex3f(-0.5,-0.5,0.5);
        glNormal3f(-0.5,0.5,0.5);
        glVertex3f(-0.5,0.5,0.5);
    glEnd();
}
void displayFunc() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(P.x,P.y,P.z);
        cube();
        glPopMatrix();
        lightning();
        glutSwapBuffers();
}

void timerFunc(int value){
  if(t>1.0 || t<0.0)
    tstep = -tstep;
  t+=tstep;

  a.x = (1.0-t)*P0.x+t*P1.x;
  a.y = (1.0-t)*P0.y+t*P1.y;
  a.z = (1.0-t)*P0.z+t*P1.z;
  b.x = (1.0-t)*P1.x+t*P2.x;
  b.y = (1.0-t)*P1.y+t*P2.y;
  b.z = (1.0-t)*P1.z+t*P2.z;
  c.x = (1.0-t)*P2.x+t*P3.x;
  c.y = (1.0-t)*P2.y+t*P3.y;
  c.z = (1.0-t)*P2.z+t*P3.z;
  d.x = (1.0-t)*a.x+t*b.x;
  d.y = (1.0-t)*a.y+t*b.y;
  d.z = (1.0-t)*a.z+t*b.z;
  e.x = (1.0-t)*b.x+t*c.x;
  e.y = (1.0-t)*b.y+t*c.y;
  e.z = (1.0-t)*b.z+t*c.z;
  
  
  P.x = (1.0-t)*d.x+t*e.x;
  P.y = (1.0-t)*d.y+t*e.y;
  P.z = (1.0-t)*d.z+t*e.z;
  glutPostRedisplay();
  glutTimerFunc(50,timerFunc,1);
}

int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(500,500);
    glutCreateWindow("Belzier");
    init();
    glutDisplayFunc(displayFunc);
    glutTimerFunc(50,timerFunc,1);
    glutMainLoop();
    return 0;
}