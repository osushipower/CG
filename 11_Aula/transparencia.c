#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

GLfloat transX = 0.0f;
GLfloat transY = 0.0f;

void lighting(){
        //define a posição e parâmetros da luz 0
        float position[] = {2.0f, 2.0f, 2.0f, 1.0f};
        float white[] = {1.0f, 1.0f, 1.0f, 1.0f};
        float black[] = {0.0f, 0.0f, 0.0f, 1.0f};

        glLightfv(GL_LIGHT0,GL_POSITION, position);
        glLightfv(GL_LIGHT0,GL_AMBIENT, black);
        glLightfv(GL_LIGHT0,GL_DIFFUSE, white);
        glLightfv(GL_LIGHT0,GL_SPECULAR, white);

        //ativa a iluminação
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        //ativa transparência
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA);
}

void init(){
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //define a cor de fundo
        glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade

        glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
        glLoadIdentity(); //carrega a matrix de identidade
        gluLookAt(0.0, 0.0, 1.0, //posição da câmera
                  0.0, 0.0, 0.0, //para onde a câmera aponta
                  0.0, 1.0, 0.0); //vetor view-up

        glMatrixMode(GL_PROJECTION); //define que a matrix Ã© a de projeção
        glLoadIdentity(); //carrega a matrix de identidade
        glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

        lighting(); //defininido os parâmetros de iluminação
}

void displayFunc(){
        //limpa o buffer
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        //define que a matrix é a de modelo
        glMatrixMode(GL_MODELVIEW);

        //desenho a esfera de dentro
        float diffuse1[] = {0.0f, 0.65f, 0.0f, 0.0f};
        float specular1[] = {0.9f, 0.9f, 0.9f, 0.0f};
        float shininess1 = 65.0f;
        glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,diffuse1);
        glMaterialfv(GL_FRONT,GL_SPECULAR,specular1);
        glMaterialf(GL_FRONT,GL_SHININESS,shininess1);
        glPushMatrix();
        glTranslatef(transX,transY,0.0);
        glutSolidSphere(0.75, 40, 40);
        glPopMatrix();

        //desenho a esfera de fora
        float diffuse2[] = {0.0f, 0.0f, 0.65f, 0.8f};
        float specular2[] = {0.9f, 0.9f, 0.9f, 0.8f};
        float shininess2 = 65.0f;
        glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,diffuse2);
        glMaterialfv(GL_FRONT,GL_SPECULAR,specular2);
        glMaterialf(GL_FRONT,GL_SHININESS,shininess2);
        glutSolidSphere(1.5, 40, 40);

        //força o desenho das primitivas
        glFlush();
}

void translacoes(int key, int x, int y){
     switch (key){
        case GLUT_KEY_LEFT :
           transX-=0.1;
           break ;
        case GLUT_KEY_RIGHT :
           transX+=0.1;
           break ;
        case GLUT_KEY_DOWN :
           transY-=0.1;
           break ;
        case GLUT_KEY_UP :
           transY+=0.1;
           break ;
        default:
           break;
     }
     glutPostRedisplay() ;
}


int main(int argc, char *argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(500,500);
    glutCreateWindow("Iluminacao");
    glutDisplayFunc(displayFunc);
    glutSpecialFunc(translacoes);
    init();
    glutMainLoop();
    return 0;
}