#include <windows.h>
#include <GL\glut.h>

// Posição inicial do quadrado
// Posição inicial do quadrado
GLfloat x1 = 100.0f;
GLfloat y_1 = 150.0f;
GLsizei rsize = 50;

// Passo nas direções x e y
GLfloat xstep = 0.05f;
GLfloat ystep = 0.05f;

// Medidas da janela
GLfloat windowWidth = 600;
GLfloat windowHeight = 600;

void init()
{
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST); // habilita o teste de profundidade
   glColor3f(1.0, 1.0, 1.0);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // limpa o buffer
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
}

void displayFunc(void)
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // limpa o buffer
   glColor3f(1.0f, 0.0f, 0.0f);
   glRectf(x1, y_1, x1 + rsize, y_1 + rsize);
   glutSwapBuffers();
}

void anima()
{
   // Direção oposta qdo atinge o canto direito ou esquerdo
   if (x1 > windowWidth - rsize || x1 < 0)
      xstep = -xstep;

   // Direção oposta qdo atinge o lado de cima ou de baixo
   if (y_1 > windowHeight - rsize || y_1 < 0)
      ystep = -ystep;

   // passo que movimenta o quadrado
   x1 += xstep;
   y_1 += ystep;

   // Redesenha a cena com as novas coordenadas
   glutPostRedisplay();
}

void mouseFunc(int button, int state, int x, int y)
{
   switch (button)
   {
   case GLUT_LEFT_BUTTON:
      if (state == GLUT_DOWN)
         glutIdleFunc(anima);
      break;
   case GLUT_RIGHT_BUTTON:
      if (state == GLUT_DOWN)
         glutIdleFunc(NULL);
      break;
   default:
      break;
   }
}

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowPosition(50, 50);
   glutInitWindowSize(windowWidth, windowHeight);
   glutCreateWindow("Contra as Paredes");
   init();
   glutDisplayFunc(displayFunc);
   glutMouseFunc(mouseFunc);
   glutMainLoop();
}