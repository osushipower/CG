#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade

    glMatrixMode(GL_MODELVIEW); //define que a matrix È a model view
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(0.0, 0.0, 1.0,   //posiÁ„o da c‚mera
              0.0, 0.0, 0.0,   //para onde a c‚mera aponta
              0.0, 1.0, 0.0);  //vetor view-up

    glMatrixMode(GL_PROJECTION); //define que a matrix È a de projeÁ„o
    glLoadIdentity(); //carrega a matrix de identidade
    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.0, 4.0); //define uma projeÁ„o ortogonal
    glViewport(0, 0, 500, 500);
    glShadeModel(GL_SMOOTH);
    lightning();
    glPushMatrix();
}

void cube(){
    GLfloat shininess;   //Coeficiente de reflexão da luz ambiente k_a
    GLfloat diffuse[4];  //Coeficiente de reflexão difusa k_d
    GLfloat specular[4]; //Coeficiente de reflexão especular k_s

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer

        glMatrixMode(GL_MODELVIEW); //define que a matrix È a model view
        glLoadIdentity(); //carrega a matrix de identidade
        gluLookAt(0.0, 0.0, 1.0,   //posiÁ„o da c‚mera
                  0.0, 0.0, 0.0,   //para onde a c‚mera aponta
                  0.0, 1.0, 0.0);  //vetor view-up

        glPushMatrix();
        glRotatef(angleX,1.0,0.0,0.0);
        glRotatef(angleY,0.0,1.0,0.0);
        glRotatef(angleZ,0.0,0.0,1.0);
        cube();
        glPopMatrix();

        lightning();

        glFlush();
}

void keyboard (unsigned char key, int x, int y){
    switch(key){
       case 'x':
       case 'X':
            angleX+=5.0f;
          break;
       case 'y':
       case 'Y':
            angleY+=5.0f;
          break;
      case 'z':
      case 'Z':
            angleZ+=5.0f;
          break;
      default:
          break;
    }
    glutPostRedisplay();
}



int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(500,500);
    glutCreateWindow("Iluminacao");
    glutDisplayFunc(displayFunc);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}