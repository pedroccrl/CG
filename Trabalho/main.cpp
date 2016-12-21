#include <windows.h>
#include <iostream>
#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glext.h>
#include <stdio.h>
#include <math.h>
#include "texura.h"
#include "objeto.h"
#include "base.h"


float anguloz = 1, anguloy = 90, ang_esfera = 0;
float frentex=0, frentez=0, frentey;
int espaco = 30;
float anda = 0;
Objeto aviao, trofeu, paredes, sofa, tv, chao, escr, ventilador, telhado;
GLuint textura, TEXTURAS[10];
int NUM_TEXTURA = 0;

int tempo_animacao = 100;
void Animacao(int tempo_atual){
    ang_esfera += 1;
    glutTimerFunc(tempo_atual,Animacao,tempo_animacao);
    glutPostRedisplay();
}

int angYFog = 0;
float XFog = 0;
float YFog = 0;
const float DEG2RAD = 3.14159/180;
void RotacionaFoguete(int t)
{
    angYFog++;
    int radius = 60;
    if (angYFog == 360) angYFog = 0;
    float degInRad = angYFog*DEG2RAD;
    XFog = cos(degInRad)*radius;
    YFog = sin(degInRad)*radius;
    glutTimerFunc(5, RotacionaFoguete, 0);
    glutPostRedisplay();
}
int angZTrof = 0;
void RotacionaTrofeu(int t)
{
    angZTrof += 1;
    glutTimerFunc(5, RotacionaTrofeu, 0);
    glutPostRedisplay();
}

float controle = 0.0;
void AnimacaoLuz(int id){
    //Não utilizado
    controle += 0.1;
    GLfloat posicaoLuz[4]={controle, controle, controle, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    glutTimerFunc(100,AnimacaoLuz,1);
    glutPostRedisplay();
}

void Desenha(void)
{
    glClearColor(0, 0.5f, 0.5f, 1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(anguloy,0,1,0);
    glRotatef(anguloz,1,0,0);
    glTranslatef(frentex, frentey, frentez);

    glPushMatrix();
        glColor3f(0.9, 0.9, 0.9);
        DesenhaObj(paredes);
    glPopMatrix();

    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, textura);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTranslatef(0, -1, 25);
        glBegin(GL_QUADS);

            glColor3f(0.9,0.9,0.9);
            glTexCoord2d(0,0);  glVertex3f(10, -8, 10);
            glTexCoord2d(0,1); glVertex3f(-10, -8, 10);
            glTexCoord2d(1,1); glVertex3f(-10, -8, -10);
            glTexCoord2d(1,0); glVertex3f(10, -8, -10);
        glEnd();
    glPopMatrix();

    if (frentey < -15)
    {
        glPushMatrix();
            glColor3f(0.5,0.5,0.5);
            glTranslatef(XFog,20,YFog);
            glRotatef(angYFog, 0, 1, 0);
            glRotatef(-90,1,0,0);
            glScalef(1.3, 1.3, 1.3);
    //        glScalef(0.1,0.1,0.1);
            DesenhaObj(aviao);
        glPopMatrix();
    }

    glPushMatrix();
        glColor3f(0.5,0.2,0.2);
        glTranslatef(0,-5,0);
        glRotatef(270,1,0,0);
        glRotatef(angZTrof, 0, 0, 1);
        glScalef(0.01,0.01,0.01);
        DesenhaObj(trofeu);
    glPopMatrix();

    glPushMatrix();
        glColor3f(.8f, .8f, .8f);
        glTranslatef(0,-10,20);
        glScalef(2, 2, 2);
        DesenhaObj(sofa);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.9f, 0.9f, 0.9f);
        glTranslatef(0, -5, 35);
        glRotatef(180, 0, 1, 0);
        glScalef(0.3, 0.3, 0.3);
        DesenhaObj(tv);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0, 5, 25);
        glPushMatrix();
            glColor3f(0.1f, 0.9f, 0.1f);
            glRotatef(angZTrof, 0, 1, 0);
            glScalef(0.12, 0.12, 0.12);
            DesenhaObj(ventilador);
        glPopMatrix();
    glPopMatrix();

    glPushMatrix();
        glColor3f(1, 1, 1);
        DesenhaObj(chao);
    glPopMatrix();

    glPushMatrix();
        glColor3f(1, 1, 1);
        glScalef(2.2, 2, 2.2);
        glTranslatef(0, 5, 0);
        glRotatef(-90, 1, 0, 0);
        DesenhaObj(telhado);
    glPopMatrix();

    Esferas(ang_esfera);
    Mesa();
    glFlush();
    glutSwapBuffers();
}

float controle_luz = 0.7;

void LuzAmbiente(int id){
    if(id == 1 && controle_luz < 1){
        controle_luz += 0.1;
    }
    else if(id == 0 && controle_luz > 0){
        controle_luz -= 0.1;
    }
	GLfloat luzAmbiente[4]={controle_luz,controle_luz,controle_luz,1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
}

void Teclado(unsigned char key, int x, int y)
{
    float var = 0.5;
    float var_ang = 1.2;
    switch (key)
    {
    case '+':
        anda += 1;
        break;
        case '1': anguloz = 0;
                  anguloy = 0;
                  frentex = 0;
                  frentey = 0;
                  frentez = 0;
                  tempo_animacao = 100;
                  controle_luz = 0.6; LuzAmbiente(1);
                  break;
        case '<': LuzAmbiente(0); //Diminui
                break;
        case '>': LuzAmbiente(1); //Aumenta
                break;
        case '[': if(tempo_animacao < 150) tempo_animacao += 1;
                break;
        case ']': if(tempo_animacao > 1) tempo_animacao -= 1;
                break;
        case 'q': anguloy -= var_ang;
                break;
        case 'e': anguloy += var_ang;
                break;
        case 'r': anguloz -= var_ang;
                break;
        case 'f': anguloz += var_ang;
                break;
        case 'w': frentez += var;
                break;
        case 's': frentez -= var;
                break;
        case 'a': frentex += var;
                break;
        case 'd': frentex -= var;
                break;
        case 'z': frentey += var;
                break;
        case 'x': frentey -= var;
                break;
        case 27: exit(1);

    }
//    printf("Frente:\t x:%.2f\ty:%.2f\tz:%.2f\n",frentex,frentey,frentez);
//    printf("Angulo:\t x:%.2f\ty:%.2f\n",frentex,anguloy);
//    printf("Tempo Animacao:%d\n\n",tempo_animacao);
    glutPostRedisplay();
}

void Inicializar()
{
	GLfloat luzAmbiente[4]={0.2, 0.2, 0.2, 1.0}; //Cor emitida
	GLfloat luzDifusa[4]={0.6, 0.6, 0.6, 1.0};	   // "cor"
	GLfloat luzEspecular[4]={0.6, 0.6, 0.6, 1.0};// "brilho"
	GLfloat posicaoLuz[4]={0.0, 20.0, 0.0, 1.0};
	GLfloat material_ambiente[4] = {0.7, 0.7, 0.7, 1.0};
	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;
    // Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);
	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambiente);
	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
    // Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);

	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);
	// Ativa o uso da luz ambienteglLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    //glEnable(GL_CULL_FACE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    gluPerspective(70, 1, 0.1, 500);
    gluLookAt(0,0,1, /// observador
              0,0,0, /// centro
              0,1,0); /// topo


        /* load an image file directly as a new OpenGL texture */
    textura = SOIL_load_OGL_texture
        (
            "C:\\Users\\pedro\\Documents\\GitHub\\CG\\Trabalho\\Imagens\\tapete2.jpg",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        );
    /* check for an error during the load process */
    if( 0 == textura )
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
    else
    {
        printf("Textura carregada com sucesso!\n");
    }
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(1024, 640);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Aplicação OpenGL");
    glutDisplayFunc(Desenha);
    glutKeyboardFunc(Teclado);



    Inicializar();

    paredes = LoadObj("C:\\Users\\pedro\\Documents\\GitHub\\CG\\Trabalho\\Objetos\\paredes.obj");
    sofa = LoadObj("C:\\Users\\pedro\\Documents\\GitHub\\CG\\Trabalho\\Objetos\\Couch.obj");
    aviao = LoadObj("C:\\Users\\pedro\\Documents\\GitHub\\CG\\Trabalho\\Objetos\\Caca.obj");
    trofeu = LoadObj("C:\\Users\\pedro\\Documents\\GitHub\\CG\\Trabalho\\Objetos\\trofeu.obj");
    chao = LoadObj("C:\\Users\\pedro\\Documents\\GitHub\\CG\\Trabalho\\Objetos\\chao.obj");
    tv = LoadObj("C:\\Users\\pedro\\Documents\\GitHub\\CG\\Trabalho\\Objetos\\televisao.obj");
    ventilador = LoadObj("C:\\Users\\pedro\\Documents\\GitHub\\CG\\Trabalho\\Objetos\\ventilador.obj");
    telhado = LoadObj("C:\\Users\\pedro\\Documents\\GitHub\\CG\\Trabalho\\Objetos\\telhado.obj");
    //escr = LoadObj("C:\\Users\\pedro\\Documents\\GitHub\\CG\\Trabalho\\Objetos\\escrivaninha.obj");

    glutTimerFunc(tempo_animacao,Animacao,tempo_animacao);
    glutTimerFunc(300, RotacionaFoguete, 0);
    glutTimerFunc(25, RotacionaTrofeu, 0);
    glutMainLoop();
    return 0;
}
