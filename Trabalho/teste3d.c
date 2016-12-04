// **********************************************************************
//	Basico.cpp
//  Programa de testes com OpenGL 3D
//	Marcio Sarroglia Pinho
//  pinho@pucrs.br
// **********************************************************************


//#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include <stdlib.h>


GLfloat ratio;


// **********************************************************************
//  void init(void)
//		Inicializa os parâmetros globais de OpenGL
//
// **********************************************************************
void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fundo de tela preto

	glShadeModel(GL_SMOOTH);
	glColorMaterial ( GL_FRONT, GL_AMBIENT_AND_DIFFUSE );
	glEnable(GL_DEPTH_TEST);
	glEnable ( GL_CULL_FACE );

}
// **********************************************************************
//  void PosicUser()
//
//
// **********************************************************************
void PosicUser()
{
	// Set the clipping volume
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,ratio,0.01,200);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 0,
		      0,0,-8,
			  0.0f,1.0f,0.0f);

}
// **********************************************************************
//  void reshape( int w, int h )
//		trata o redimensionamento da janela OpenGL
//
// **********************************************************************
void reshape( int w, int h )
{

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if(h == 0)
		h = 1;

	ratio = 1.0f * w / h;
	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);

	PosicUser();

}
// **********************************************************************
//  void DesenhaCubo()
//
//
// **********************************************************************
void DesenhaCubo()
{
	glBegin ( GL_QUADS );
		// Front Face
		glNormal3f(0,0,1);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glNormal3f(0,0,-1);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glNormal3f(0,1,0);
		glVertex3f(-1.0f,  1.0f, -1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glNormal3f(0,-1,0);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glNormal3f(1,0,0);
		glVertex3f( 1.0f, -1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f, -1.0f);
		glVertex3f( 1.0f,  1.0f,  1.0f);
		glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glNormal3f(-1,0,0);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f,  1.0f);
		glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
}
// **********************************************************************
//  void display( void )
//
//
// **********************************************************************
void display( void )
{
	static double angY = 0;

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	PosicUser();

	glMatrixMode(GL_MODELVIEW);


	glPushMatrix();
		glTranslatef ( 1.0f, 0.0f, -5.0f );
		glRotatef(angY,0,1,0);
		glColor3f(0.5f,0.3f,0.0f);
		DesenhaCubo();
	glPopMatrix();


	glPushMatrix();
		glTranslatef ( -1.0f, 2.0f, -8.0f );
		glRotatef(angY,0,1,0);
		glColor3f(0.5f,0.3f,0.0f);
		DesenhaCubo();
	glPopMatrix();

	angY ++;

	glutSwapBuffers();
}

// **********************************************************************
//  void keyboard ( unsigned char key, int x, int y )
//
//
// **********************************************************************
void keyboard ( unsigned char key, int x, int y )
{
	switch ( key )
	{
    case 27:        // Termina o programa qdo
      exit ( 0 );   // a tecla ESC for pressionada
      break;

    default:
      break;
  }
}

// **********************************************************************
//  void arrow_keys ( int a_keys, int x, int y )
//
//
// **********************************************************************
void arrow_keys ( int a_keys, int x, int y )
{
	switch ( a_keys )
	{
		case GLUT_KEY_UP:       // When Up Arrow Is Pressed...
			glutFullScreen ( ); // Go Into Full Screen Mode
			break;
	    case GLUT_KEY_DOWN:     // When Down Arrow Is Pressed...
			glutInitWindowSize  ( 700, 500 );
			break;
		default:
			break;
	}
}

// **********************************************************************
//  void main ( int argc, char** argv )
//
//
// **********************************************************************
int main ( int argc, char** argv )
{
	glutInit            ( &argc, argv );
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB );// | GLUT_STEREO);// | GLUT_DOUBLE | GLUT_RGBA );
	//glutInitDisplayMode (GLUT_RGB | GLUT_DEPTH | GLUT_STEREO);// | GLUT_DOUBLE | GLUT_RGBA );

	glutInitWindowPosition (0,0);
	glutInitWindowSize  ( 700, 500 );
	glutCreateWindow    ( "Computação Gráfica - Exemplo Básico 3D" );

	init ();

	glutDisplayFunc ( display );
	glutReshapeFunc ( reshape );
	glutKeyboardFunc ( keyboard );
	glutSpecialFunc ( arrow_keys );
	glutIdleFunc ( display );

	glutMainLoop ( );
	return 0;
}




