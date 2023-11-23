#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Eduardo Augusto Saito
// Tales Miguel

typedef struct BMPImagem
{
    int   width;
    int   height;
    char *data;
}BMPImage;

/* Qtd máxima de texturas a serem usadas no programa */
#define MAX_NO_TEXTURES 6

/* vetor com os números das texturas */
GLuint texture_id[MAX_NO_TEXTURES];

char* filenameArray[MAX_NO_TEXTURES] = {
        "bmp_24.bmp",
        "weird.bmp",
        "weird.bmp",
        "weird.bmp",
        "weird.bmp",
        "weird.bmp"
};

float thetaX = 0.0;
float thetaY = 0.0;
float theta = 0.0;
int subindo = 0;

//-----------------------------------------------------------------------------
// Name: getBitmapImageData()
// Desc: Simply image loader for 24 bit BMP files.
//-----------------------------------------------------------------------------
void getBitmapImageData( char *pFileName, BMPImage *pImage )
{
    FILE *pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
    int i;

    if( (pFile = fopen(pFileName, "rb") ) == NULL )
        printf("ERROR: getBitmapImageData - %s not found.\n", pFileName);

    // Seek forward to width and height info
    fseek( pFile, 18, SEEK_CUR );

    if( (i = fread(&pImage->width, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read width from %s.\n ", pFileName);

    if( (i = fread(&pImage->height, 4, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read height from %s.\n ", pFileName);

    if( (fread(&nNumPlanes, 2, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read plane count from %s.\n", pFileName);

    if( nNumPlanes != 1 )
        printf("ERROR: getBitmapImageData - Plane count from %s.\n ", pFileName);

    if( (i = fread(&nNumBPP, 2, 1, pFile)) != 1 )
        printf( "ERROR: getBitmapImageData - Couldn't read BPP from %s.\n ", pFileName);

    if( nNumBPP != 24 )
        printf("ERROR: getBitmapImageData - BPP from %s.\n ", pFileName);

    // Seek forward to image data
    fseek( pFile, 24, SEEK_CUR );

    // Calculate the image's total size in bytes. Note how we multiply the
    // result of (width * height) by 3. This is becuase a 24 bit color BMP
    // file will give you 3 bytes per pixel.
    int nTotalImagesize = (pImage->width * pImage->height) * 3;

    pImage->data = (char*) malloc( nTotalImagesize );

    if( (i = fread(pImage->data, nTotalImagesize, 1, pFile) ) != 1 )
        printf("ERROR: getBitmapImageData - Couldn't read image data from %s.\n ", pFileName);

    //
    // Finally, rearrange BGR to RGB
    //

    char charTemp;
    for( i = 0; i < nTotalImagesize; i += 3 )
    {
        charTemp = pImage->data[i];
        pImage->data[i] = pImage->data[i+2];
        pImage->data[i+2] = charTemp;
    }
}


/*Função para Carregar uma imagem .BMP */
void CarregaTexturas()
{
    BMPImage textura;

    /* Define quantas texturas serão usadas no programa  */
    glGenTextures(MAX_NO_TEXTURES, texture_id); /* 1 = uma textura; */
                                /* texture_id = vetor que guardas os números das texturas */

    int i;
    for ( i=0; i<MAX_NO_TEXTURES; i++ ) {
        getBitmapImageData( filenameArray[i], &textura);
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textura.width, textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    }
}

/* **********************************************************************
  void initTexture(void)
        Define a textura a ser usada

 ********************************************************************** */
void initTexture (void)
{

    /* Habilita o uso de textura bidimensional  */
    glEnable ( GL_TEXTURE_2D );
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    /*Carrega os arquivos de textura */
  //  CarregaTextura("tunnelTexture.bmp");
    //CarregaTextura("tex2.bmp");
    CarregaTexturas();

}

void cubo(){
     float size = 1.0;
     GLfloat n[6][3] =
     {
        {-1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0},
        {0.0, 0.0, -1.0}
     };
     GLint faces[6][4] =
     {
        {0, 1, 2, 3},
        {3, 2, 6, 7},
        {7, 6, 5, 4},
        {4, 5, 1, 0},
        {5, 6, 2, 1},
        {7, 4, 0, 3}
     };
     GLfloat v[8][3];
     GLint i;

     v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 9;
     v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 9;
     v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 9;
     v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 9;
     v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 9;
     v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 9;

     for (i = 5; i >= 0; i--) {
         glBindTexture(GL_TEXTURE_2D, texture_id[i]);
         glBegin(GL_QUADS);
            glNormal3fv(&n[i][0]);
            glTexCoord2f(0.0f,0.0f);
            glVertex3fv(&v[faces[i][0]][0]);
            glTexCoord2f(1.0f,0.0f);
            glVertex3fv(&v[faces[i][1]][0]);
            glTexCoord2f(1.0f,1.0f);
            glVertex3fv(&v[faces[i][2]][0]);
            glTexCoord2f(0.0f,1.0f);
            glVertex3fv(&v[faces[i][3]][0]);
         glEnd();
     }
}

void desenhaMembro(float scaleX, float scaleY, float scaleZ, float  tX, float tY, float tZ, float rX, float rY, float rZ){
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(thetaX, 1.0, 0.0, 0.0);
    glRotatef(thetaY, 0.0, 1.0, 0.0);
    glRotatef(theta, rX, rY, rZ);
    glScalef(scaleX, scaleY, scaleZ);
    glTranslatef(tX, tY, tZ);
    cubo();
    glPopMatrix();
}

void desenha()
{
    glClearColor(0, 0, 0, 0); // Preto
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Cabeça
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(thetaX, 1.0, 0.0, 0.0);
    glRotatef(thetaY, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 0.5, 0.0);
    cubo();
    glPopMatrix();

    // Corpo
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glRotatef(thetaX, 1.0, 0.0, 0.0);
    glRotatef(thetaY, 0.0, 1.0, 0.0);
    glScalef(1.5, 2.0, 1.5);
    glTranslatef(0.0, 0.05, 0.0);
    cubo();
    glPopMatrix();

    // Perna 1 L1
    desenhaMembro(0.5, 1.5, 0.5, -0.2, -0.2, 0.0, 1.0, 0.0, 0.0);

    // Perna 1 L2
    desenhaMembro(0.5, 1.5, 0.5, -0.2, -0.45, 0.0, 1.0, 0.0, 0.0);

    // Perna 2 R1
    desenhaMembro(0.5, 1.5, 0.5, 0.2, -0.2, 0.0, -1.0, 0.0, 0.0);

    // Perna 2 R2
    desenhaMembro(0.5, 1.5, 0.5, 0.2, -0.45, 0.0, -1.0, 0.0, 0.0);

    // Braço Esquerdo L1
    desenhaMembro(1.5, 0.5, 0.5, 0.1, 0.3, 0.0, 0.0, 0.0, -1.0);

    // Braço Esquerdo L2
    desenhaMembro(1.5, 0.5, 0.5, 0.35, 0.3, 0.0, 0.0, 0.0, -1.0);

    // Braço Direito L1
    desenhaMembro(1.5, 0.5, 0.5, -0.1, 0.3, 0.0, 0.0, 0.0, 1.0);

    // Braço Direito L2
    desenhaMembro(1.5, 0.5, 0.5, -0.35, 0.3, 0.0, 0.0, 0.0, 1.0);


    glFlush();
}

void lighting(){
    GLfloat light0_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
    GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0,GL_POSITION,light0_pos);
    glLightfv(GL_LIGHT0,GL_AMBIENT,black);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white);
    glLightfv(GL_LIGHT0,GL_SPECULAR,white);

    //Atenuação radial
    //glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5f);   //define a0
    //glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.15f);    //define a1
    //glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1f);  //define a2

    //Fonte de Luz Direcional - Efeito de Holofote
    GLfloat light1_pos[] = {-2.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT1,GL_POSITION,light1_pos);
    glLightfv(GL_LIGHT1,GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1,GL_SPECULAR, white);
    GLfloat direction[] = {1.0f, 0.0f, 0.0f};
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,direction);       //vetor direção
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,45.0f);               //espalhamento angular
    glLightf(GL_LIGHT1,GL_SPOT_EXPONENT,0.1f);              //atenuação angular

    //Parâmetros definidos globalmente
    //GLfloat global_ambient[] = {0.9f, 0.9f, 0.9f, 1.0f};
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
    ////Reflexão especular definida como a posição de visão corrente
    //glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    ////Habilitar cálculos de iluminação para ambas as faces dos polígonos
    //glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
}

void timerFunc() {
    if (theta == 45.0) {
        subindo = -1;
    } else if (theta == -50.0)
    {
        subindo = 1;
    }
    
    if (subindo == 1) {
        theta += 1.0;
    } else {
        theta -= 1.0;
    }

    glutPostRedisplay();
    glutTimerFunc(100, timerFunc, 0);
}

void tecladoEspecial(int tecla, int x, int y)
{
    switch (tecla)
    {
    case GLUT_KEY_RIGHT:
        thetaY += 2;
        break;
    case GLUT_KEY_LEFT:
        thetaY -= 2;
        break;
    case GLUT_KEY_UP:
        thetaX += 2;
        break;
    case GLUT_KEY_DOWN:
        thetaX -= 2;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void init()
{
    glEnable ( GL_COLOR_MATERIAL );
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade

    //glShadeModel(GL_FLAT);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(4.0, 2.0, 1.0,   //posição da câmera
              0.0, 0.0, 0.0,   //para onde a câmera aponta
              0.0, 1.0, 0.0);  //vetor view-up

    glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
    glLoadIdentity(); //carrega a matrix de identidade
    //glOrtho(-2.0, 2.0, -2.0, 2.0, 2.0, 8.0); //define uma projeção ortogonal
    //gluPerspective(45.0, 1.0, 2.0, 8.0); //define uma projeção perspectiva
    //glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 8.0); //define uma projeção perspectiva simétrica
    //glFrustum(-2.0, 1.0, -1.0, 2.0, 2.0, 8.0); //define uma projeção perspectiva obliqua
    glViewport(0, 0, 500, 500);

    lighting();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cubo");
    init();
    initTexture();
    glutDisplayFunc(desenha);
    glutSpecialFunc(tecladoEspecial);
    glutTimerFunc(100, timerFunc, 0);
    glutMainLoop();
    return 0;
}