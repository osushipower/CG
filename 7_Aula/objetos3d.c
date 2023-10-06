#include <GL/glut.h>

GLUquadricObj *obj;

int objId = 1;
float angX = 0;
float angY = 0;

void init()
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST); // habilita o teste de profundidade
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glOrtho(-7, 7, -7, 7, -7, 7);
   glPushMatrix();
   obj = gluNewQuadric();
   gluQuadricDrawStyle(obj, GLU_LINE);
}

void display()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // limpa o buffer
   glColor3f(0.0, 0.0, 1.0);

   glPopMatrix();
   glPushMatrix();

   glRotatef(angX, 1, 0, 0);
   glRotatef(angY, 0, 1, 0);

   switch (objId)
   {
   case 1:
      glutWireSphere(3, 50, 50);
      // glutSolidSphere(radius,slices,stacks);
      break;
   case 2:
      glutWireCube(3);
      // glutSolidCube(size);
      break;
   case 3:
      glutWireCone(3, 5, 5, 5);
      // glutSolidCone(radius,slices,stacks);
      break;
   case 4:
      glutWireTorus(3, 4, 20, 20);
      // glutSolidTorus(innerRadius,outerRadius,slices,stacks);
      break;
   case 5:
      glScalef(3, 3, 3);
      glutWireIcosahedron();
      // glutSolidIcosahedron();
      break;
   case 6:
      glScalef(3, 3, 3);
      glutWireOctahedron();
      // glutSolidOctahedron();
      break;
   case 7:
      glScalef(3, 3, 3);
      glutWireTetrahedron();
      // glutSolidTetrahedron();
      break;
   case 8:
      glScalef(3, 3, 3);
      glutWireDodecahedron();
      // glutSolidDodecahedron();
      break;
   case 9:
      glutWireTeapot(3);
      // glutSolidTeapot(size);
      break;
   case 10:
      gluCylinder(obj, 2, 2, 5, 20, 20);
      break;
   case 11:
      gluDisk(obj, 2, 5, 10, 10);
      break;
   case 12:
      gluSphere(obj, 2, 10, 10);
      break;
   default:
      break;
   }
   glFlush();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key)
   {
   case '1':
      objId = 1;
      break;
   case '2':
      objId = 2;
      break;
   case '3':
      objId = 3;
      break;
   case '4':
      objId = 4;
      break;
   case '5':
      objId = 5;
      break;
   case '6':
      objId = 6;
      break;
   case '7':
      objId = 7;
      break;
   case '8':
      objId = 8;
      break;
   case '9':
      objId = 9;
      break;
   case 'a':
      objId = 10;
      break;
   case 'b':
      objId = 11;
      break;
   case 'c':
      objId = 12;
      break;
   default:
      break;
   }
   glutPostRedisplay();
}

void transformacoes(int key, int x, int y)
{
   switch (key)
   {
   case GLUT_KEY_UP:
      angX += 15;
      break;
   case GLUT_KEY_DOWN:
      angX -= 15;
      break;
   case GLUT_KEY_LEFT:
      angY -= 15;
      break;
   case GLUT_KEY_RIGHT:
      angY += 15;
      break;
   default:
      break;
   }
   glutPostRedisplay();
}

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowPosition(50, 50);
   glutInitWindowSize(600, 600);
   glutCreateWindow("Objetos 3D - OpenGL");
   glutDisplayFunc(display);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(transformacoes);
   init();
   glutMainLoop();
}