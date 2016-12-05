#include <windows.h>
#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include "objetos.h"

float anguloz = 1, anguloy = 1, ang_esfera = 0;
float frentex=0, frentez=0, frentey;
int espaco = 30;
float anda = 0;


TTriangle Vaca[6000];
TTriangle Tree[19000];
int NFacesVaca, NFacesTree;


void Animacao(int id){
    ang_esfera += 1;
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
    //Chão
    glPushMatrix();
        glBegin(GL_QUADS);
            glColor3f(0.5,0.5,0.5);
            glVertex3f(20, -8, 20);
            glVertex3f(-20, -8, 20);
            glVertex3f(-20, -8, -20);
            glVertex3f(20, -8, -20);
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,3,20);
        glScalef(0.3,0.3,0);
        //glRotatef(anda,1,0,0);
        ExibeObjeto(Vaca,NFacesVaca);
    glPopMatrix();

    ExibeObjeto(Tree,NFacesTree);
    Sofa();
    Esferas(ang_esfera);
    Mesa();
    Paredes();
    glFlush();
    glutSwapBuffers();
    glutTimerFunc(100,Animacao,1);
}

float controle_luz = 0.7;
void LuzAmbiente(int aumenta){
    if(aumenta && controle_luz < 1){
        controle_luz += 0.1;
    }
    else if(controle_luz > 0){
        controle_luz -= 0.1;
    }
	GLfloat luzAmbiente[4]={controle_luz,controle_luz,controle_luz,1.0};
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
}

void Teclado(unsigned char key, int x, int y)
{
    float var = 0.5;
    float var_ang = 0.8;
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
                  controle_luz = 0.6; LuzAmbiente(1);
                  break;
        case '<': LuzAmbiente(0); //Diminui
                break;
        case '>': LuzAmbiente(1); //Aumenta
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
    printf("Frente:\n x:%.2f\ty:%.2f\tz:%.2f\n",frentex,frentey,frentez);
    printf("Angulo:\n x:%.2f\ty:%.2f\n",frentex,anguloy);
    glutPostRedisplay();
}

void Inicializar()
{
	GLfloat luzAmbiente[4]={0.7,0.7,0.7,1.0};
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor"
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho"
	GLfloat posicaoLuz[4]={0.0, 10.0, 0.0, 1.0};
	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;
    // Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);
	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
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
	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    //glEnable(GL_CULL_FACE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    gluPerspective(70, 1, 0.1, 500);
    gluLookAt(0,0,0, /// observador
              0,0,1, /// centro
              0,10,0); /// topo
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
	LeObjeto("C:\\Users\\Victor\\OneDrive - id.uff.br\\Faculdade\\2016.2\\CG\\Trabalho\\Objetos\\Vaca.tri", Vaca, NFacesVaca);
    //LeObjeto("C:\\Users\\Victor\\OneDrive - id.uff.br\\Faculdade\\2016.2\\CG\\Trabalho\\Objetos\\dog_meu.tri", Tree, NFacesTree);
    Inicializar();

    glutMainLoop();
    glutTimerFunc(100,Animacao,1);
    return 0;
}
