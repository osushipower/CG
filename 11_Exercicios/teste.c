#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

static void
Init(void)
{
  glMatrixMode(GL_PROJECTION);
  glFrustum(-1, 1, -1, 1, 2, 6);

  glMatrixMode(GL_MODELVIEW);
  glTranslatef(0.0, 0.0, -3.0);
  glRotatef(45.0, 1, 0, 0);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT1);
  GLfloat ambient1[] = { 0.7f, 0.0f, 0.0f, 1.0f };
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
  GLfloat diffuse1[] = { 1.0, 0.0, 0.0, 1.0 };
  glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
  GLfloat specular1[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
  GLfloat light_position1[] = { 0.0f, 0.0f, 0.2f, 0.0f };
  glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
  GLfloat spotExp = 20.0;
  glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotExp);
  GLfloat spotCutoff = 60.0;
  glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotCutoff);
}

static void
drawPlane(int w, int h)
{
  int i, j;
  float dw = 1.0 / w;
  float dh = 1.0 / h;

  glNormal3f(0.0, 0.0, 1.0);
  for (j = 0; j < h; ++j) {
    glBegin(GL_TRIANGLE_STRIP);
    for (i = 0; i <= w; ++i) {
      glVertex2f(dw * i, dh * (j + 1));
      glVertex2f(dw * i, dh * j);
    }
    glEnd();
  }
}

static void
Draw(void)
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glPushMatrix();
  glTranslatef(1, 1, 0);
  float light_pos[4] = {0,0,0,1};
  glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
  float light_dir[3] = {0,-1,0};
  glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_dir);
  glPopMatrix();

  glPushMatrix();
  glRotatef(-90.0, 1, 0, 0);
  glScalef(1.9, 1.9, 1.0);
  glTranslatef(-0.5, -0.5, 0.0);
  drawPlane(16, 16);
  glPopMatrix();
  glFlush();
}

int
main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE);
  glutCreateWindow("spotlight");
  Init();
  glutDisplayFunc(Draw);
  glutMainLoop();
  return 0;
}