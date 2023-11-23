#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

float global_x = 0.0f;
float global_y = 0.0f;

float angle = 0.0f;

void lighting() {
    //GLfloat light_position1[] = { 0.0f, 0.0f, 0.2f, 0.0f };
    //GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    // GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    //glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    

    // float light_pos[4] = {0, 0, 2, 1};
    // float light_dir[3] = {0, 0, -1};
    // //glTranslatef(0, 0, 2);
    // glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
    // glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_dir);
    // glLightfv(GL_LIGHT1, GL_AMBIENT, black);
    // glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    // glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    // glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.5);
    // glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0);

    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};

    //Fonte de Luz Direcional - Efeito de Holofote
    GLfloat light1_pos[] = {global_x, global_y, 3.0f, 1.0f};
    GLfloat direction[] = {0.0f, 0.0f, -1.0f};
    glLightfv(GL_LIGHT1,GL_POSITION,light1_pos);
    glLightfv(GL_LIGHT1,GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1,GL_SPECULAR, white);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction);       //vetor direção
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20.0f);               //espalhamento angular
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.5f);              //atenuação angular
  
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    glEnable(GL_COLOR_MATERIAL);
}

void mouseEvent(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);

        GLdouble modelview[16];
        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

        GLdouble projection[16];
        glGetDoublev(GL_PROJECTION_MATRIX, projection);

        GLfloat winX, winY, winZ;
        GLdouble posX, posY, posZ;

        winX = (float)x;
        winY = (float)viewport[3] - (float)y;
        glReadPixels(x, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

        gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

        global_x = posX;
        global_y = posY;
    }
}

void timerFunc()
{
    angle += 1.0f; 
    if (angle > 360.0) {
        angle -= 360.0; 
    }

    glutPostRedisplay(); 
    glutTimerFunc(25, timerFunc, 0); 
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 1.0,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
}

void displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    lighting();

    glMatrixMode(GL_MODELVIEW);
    
    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-4.0, -4.0, 0.0);
    glutSolidSphere(1.5, 40, 40);
    glPopMatrix();

    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(4.0, 4.0, 0.0);
    glutSolidSphere(1.5, 40, 40);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-4.0, 4.0, 0.0);
    glutSolidSphere(1.5, 40, 40);
    glPopMatrix();

    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glScalef(0.2, 0.2, 0.2);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(4.0, -4.0, 0.0);
    glutSolidSphere(1.5, 40, 40);
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char *argv[]){
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(50,50);
  glutInitWindowSize(500,500);
  glutCreateWindow("Viewing 3D - Projecao Perspectiva");
  init();
  glutDisplayFunc(displayFunc);
  glutMouseFunc(mouseEvent);
  glutTimerFunc(25, timerFunc, 0); // Start the update loop
  glutMainLoop();
  return 0;
}