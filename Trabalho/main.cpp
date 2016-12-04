#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>

float anguloz = 1, anguloy = 1, ang_esfera = 0;
float frentex=0, frentez=0, frentey;
int espaco = 30;

void Animacao(int id){
    ang_esfera += 1;
    glutPostRedisplay();
}

void Paredes(){
    float altura = 8.0;
    glBegin(GL_QUADS);
        glColor3f(0.6f, 0.0f, 0.0f); //PAREDE ATRÁS DA TV
        glVertex3f(20, altura, 20);
        glVertex3f(20, -altura, 20);
        glVertex3f(-20, -altura, 20);
        glVertex3f(-20, altura, 20);

        glColor3f(0.65f, 0.0f, 0.0f); //PAREDE DA PORTA
        glVertex3f(20, altura, -20);
        glVertex3f(20, -altura, -20);
        glVertex3f(-20, -altura, -20);
        glVertex3f(-20, altura, -20);

        glColor3f(0.7f, 0.0f, 0.0f); //PAREDE MAIS PRÓXIMA DA PORTA
        glVertex3f(20, altura, -20);
        glVertex3f(20, -altura, -20);
        glVertex3f(20, -altura, 20);
        glVertex3f(20, altura, 20);

        glColor3f(0.75f, 0.0f, 0.0f); //PAREDE DA BANDEIRA
        glVertex3f(-20, altura, 20);
        glVertex3f(-20, -altura, 20);
        glVertex3f(-20, -altura, -20);
        glVertex3f(-20, altura, -20);
    glEnd();
}

void Mesa(){
    glPushMatrix();
    //Mesa
        glBegin(GL_QUADS);
            //Tampos
            glVertex3f(10.0f,0,10.0f);
            glVertex3f(10.0f,0,7.5f);
            glVertex3f(7.5f,0,7.5f);
            glVertex3f(7.5f,0,10.0f);

            glVertex3f(10.0f,0.5,10.0f);
            glVertex3f(10.0f,0.5,7.5f);
            glVertex3f(7.5f,0.5,7.5f);
            glVertex3f(7.5f,0.5,10.0f);
            //Partes laterais
            glColor3f(0,1,0);
            glVertex3f(10,0,10);
            glVertex3f(10,0.5,10);
            glVertex3f(10,0.5,7.5);
            glVertex3f(10,0,7.5);

            glColor3f(1,0,1);
            glVertex3f(10,0,7.5);
            glVertex3f(10,0.5,7.5);
            glVertex3f(7.5,0.5,7.5);
            glVertex3f(7.5,0,7.5);

            glColor3f(0,1,1);
            glVertex3f(7.5,0,10);
            glVertex3f(7.5,0.5,10);
            glVertex3f(7.5,0.5,7.5);
            glVertex3f(7.5,0,7.5);

            glColor3f(1,1,0);
            glVertex3f(10,0,10);
            glVertex3f(10,0.5,10);
            glVertex3f(7.5,0.5,10);
            glVertex3f(7.5,0,10);
            //Pés
            glColor3f(1,1,1);
            glVertex3f(10,0,10);
            glVertex3f(10,-8,10);
            glVertex3f(10,-8,7.5);
            glVertex3f(10,0,7.5);

            glVertex3f(7.5,0,10);
            glVertex3f(7.5,-8,10);
            glVertex3f(7.5,-8,7.5);
            glVertex3f(7.5,0,7.5);


        glEnd();
    glPopMatrix();
}

void Esferas(){
    glPushMatrix();
        glTranslatef(0,5,0);
        glColor3f(1.0f, 0.0f, 1.0f);
        glRotatef(ang_esfera,0,1,0);
        glutWireSphere(2, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,5,0);
        glColor3f(0.0f, 1.0f, 1.0f);
        glRotatef(ang_esfera,1,0,0);
        glutWireSphere(1.5, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0,5,0);
        glColor3f(0.2f, 0.2f, 0.2f);
        glRotatef(ang_esfera,0,0,1);
        glutSolidSphere(1, 16, 16);
    glPopMatrix();
}

void Sofa(){
    glPushMatrix();

    glBegin(GL_QUADS); //DESENHA APOIO DO SOFÁ
    glColor3f(0.59f,0.29f,0.0f);
    // Tampos do apoio
    glVertex3f(13, -5, 0);
    glVertex3f(5, -5, 0);
    glVertex3f(5, -0.5, 0);
    glVertex3f(13, -0.5, 0);

    glVertex3f(13, -5, -0.5);
    glVertex3f(5, -5, -0.5);
    glVertex3f(5, -0.5, -0.5);
    glVertex3f(13, -0.5, -0.5);

    glVertex3f(13, -5, 0);
    glVertex3f(13, -5, -0.5);
    glVertex3f(13, -0.5, -0.5);
    glVertex3f(13, -0.5, 0);

    glVertex3f(5, -5, 0);
    glVertex3f(5, -5, -0.5);
    glVertex3f(5, -0.5, -0.5);
    glVertex3f(5, -0.5, 0);

    glVertex3f(13, -0.5, 0);
    glVertex3f(13, -0.5, -0.5);
    glVertex3f(5, -0.5, -0.5);
    glVertex3f(5, -0.5, 0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.55f,0.27f,0.07f);
    glVertex3f(5, -4.99, 0.01);
    glVertex3f(6, -4.99, 0.01);
    glVertex3f(6, -4.99, 2);
    glVertex3f(5, -4.99, 2);

    glVertex3f(5, -2.5, 2);
    glVertex3f(5, -2.5, 0.01);
    glVertex3f(6, -2.5, 0.01);
    glVertex3f(6, -2.5, 2);

    glVertex3f(5, -2.5, 2);
    glVertex3f(5, -4.99, 2);
    glVertex3f(6, -4.99, 2);
    glVertex3f(6, -2.5, 2);

    glVertex3f(5, -2.5, 2);
    glVertex3f(5, -4.99, 2);
    glVertex3f(5, -4.99, 0.01);
    glVertex3f(5, -2.5, 0.01);//DESENHA LATERAL 1 DO SOFÁ

    glVertex3f(6, -2.5, 2);
    glVertex3f(6, -4.99, 2);
    glVertex3f(6, -4.99, 0.01);
    glVertex3f(6, -2.5, 0.01); //DESENHA CABECEIRA 1

    glVertex3f(12, -2.5, 2);
    glVertex3f(12, -2.5, 0.01);
    glVertex3f(13, -2.5, 0.01);
    glVertex3f(13, -2.5, 2);

    glVertex3f(12, -2.5, 2);
    glVertex3f(12, -4.99, 2);
    glVertex3f(13, -4.99, 2);
    glVertex3f(13, -2.5, 2);

    glVertex3f(12, -2.5, 2);
    glVertex3f(12, -4.99, 2);
    glVertex3f(12, -4.99, 0.01);
    glVertex3f(12, -2.5, 0.01);

    glVertex3f(13, -2.5, 2);
    glVertex3f(13, -4.99, 2);
    glVertex3f(13, -4.99, 0.01);
    glVertex3f(13, -2.5, 0.01); //desenha cabeceira 2

    glColor3f(0.43f,0.21f, 0.1f);
    glVertex3f(6, -4.99, 0.01);
    glVertex3f(6, -4.99, 2);
    glVertex3f(12, -4.99, 2);
    glVertex3f(12, -4.99, 0.01); //DESENHA BASE DO SOFÁ NO CHÃO

    glVertex3f(6, -3.75, 0.01);
    glVertex3f(6, -3.75, 2);
    glVertex3f(12, -3.75, 2);
    glVertex3f(12, -3.75, 0.01); //DESENHA BASE DO SOFÁ NO ALTO

    glVertex3f(6, -3.75, 2);
    glVertex3f(6, -4.99, 2);
    glVertex3f(12, -4.99, 2);
    glVertex3f(12, -3.75, 2); //COMPLETA BASE DO SOFÁ

    glEnd();
    glPopMatrix();
}

void Desenha(void)
{
    glClearColor(0, 0.5f, 0.5f, 1);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(anguloy,0,1,0);
    glRotatef(anguloz,0,0,1);
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


    Sofa();
    Esferas();
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
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	//glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
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

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

    gluPerspective(70, 1, 0.1, 500);
    gluLookAt(2,0,2, /// observador
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

    Inicializar();

    glutMainLoop();
    glutTimerFunc(100,Animacao,1);
    return 0;
}
