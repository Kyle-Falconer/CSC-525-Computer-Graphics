/*===================================================================================
PROGRAMMER:			Yang Wang
COURSE:				CSC 525/625
MODIFIED BY:			Kyle Falconer
LAST MODIFIED DATE:	Nov. 20, 2013
DESCRIPTION:			Demo: projections with OpenGL
NOTE:					N/A
FILES:					projections.cpp, (labProject.sln, ...)
IDE/COMPILER:			Microsoft Visual Studio 2012
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Double click on labProject.sln	to OPEN the project
2.		Press Ctrl+F7					to COMPILE
3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
4.		Press Ctrl+F5					to EXECUTE
===================================================================================*/

#include <iostream>
#include <GL/glut.h>				// include GLUT library
#include <string>
#include <sstream>
using namespace std;

const int windowWidth = 400;
const int windowHeight = 400;

enum ProjectionType {ORTHOGONAL, PERSPECTIVE};
ProjectionType selectedProjection;

const GLfloat threepipe[6][3] = {
	{60,  55, 40},
	{60, -50, 40},
	{65,  90, -70},
	{65,   0, -70},
	{-70,  70, 20},
	{-70, -20, 20}
};


//***********************************************************************************
void drawThreePipe()
{

	glBegin(GL_LINE_STRIP);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(threepipe[2][0], threepipe[2][1], threepipe[2][2]);
	glVertex3f(threepipe[4][0], threepipe[4][1], threepipe[4][2]);
	glVertex3f(threepipe[5][0], threepipe[5][1], threepipe[5][2]);
	glVertex3f(threepipe[3][0], threepipe[3][1], threepipe[3][2]);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(threepipe[4][0], threepipe[4][1], threepipe[4][2]);
	glVertex3f(threepipe[0][0], threepipe[0][1], threepipe[0][2]);
	glVertex3f(threepipe[1][0], threepipe[1][1], threepipe[1][2]);
	glVertex3f(threepipe[5][0], threepipe[5][1], threepipe[5][2]);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(threepipe[0][0], threepipe[0][1], threepipe[0][2]);
	glVertex3f(threepipe[2][0], threepipe[2][1], threepipe[2][2]);
	glVertex3f(threepipe[3][0], threepipe[3][1], threepipe[3][2]);
	glVertex3f(threepipe[1][0], threepipe[1][1], threepipe[1][2]);
	glEnd();

}


void drawAxis3i(){
	glPointSize(1);		// change point size back to 1
	glBegin(GL_POINTS);	// use points to form X-/Y-axes
	glColor3f(0, 0, 0);			 // change drawing color to black
	for (int x=-150; x<=150; x++) // draw X-axis
		glVertex3i(x, 0, 0);
	for (int y=-150; y<=150; y++) // draw Y-axis
		glVertex3i(0, y, 0);
	for (int z=-150; z<=150; z++) // draw Z-axis
		glVertex3i(0, 0, z);
	glEnd();
}


//***********************************************************************************
void init()
{
	glClearColor(1, 1, 1, 0);			// specify a background clor: white 
	glOrtho(-200, 200, -200, 200, -200, 200);  // specify a viewing area

	//glMatrixMode(GL_PROJECTION);
	//gluPerspective( /* field of view in degree */ 40.0,
	//	/* aspect ratio */ 1.0,
	//	/* Z near */ 1.0, /* Z far */ 10.0);

	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0,0,100, 0,0,0, 0,1,0);
}

//***********************************************************************************
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawAxis3i();
	drawThreePipe();

	glFlush();
	glutSwapBuffers();
}


void keyboardListener(unsigned char key,int x,int y){
	if (key == 27) exit(0);
	else if (key == 'o' || key == 'O') selectedProjection = ORTHOGONAL ;
	else if (key == 'p' || key == 'P') selectedProjection = PERSPECTIVE ;
}

void menuListener(int value)
{
	keyboardListener((unsigned char)value, 0, 0);
}

void menuInit(){
	glutCreateMenu(menuListener);
	glutAddMenuEntry("Orthogonal [o]", 'o');
	glutAddMenuEntry("Perspective [p]", 'p');
	glutAddMenuEntry("Exit [Esc]", 27);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


//***********************************************************************************
void main(int argc, char ** argv)
{

	glutInit(& argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(windowWidth, windowHeight);				// specify a window size
	glutInitWindowPosition(100, 0);			// specify a window position
	glutCreateWindow("OpenGL Projections");	// create a titled window

	init();									
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardListener);
	menuInit();


	glutMainLoop();							// get into an infinite loop
}
