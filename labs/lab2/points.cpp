/*===================================================================================
PROGRAMMER:			Yang Wang
COURSE:				CSC 525/625
MODIFIED BY:			Kyle Falconer
LAST MODIFIED DATE:	Aug. 26, 2013
DESCRIPTION:			Demo: drawing points.
NOTE:					N/A
FILES:					points.cpp, (myCPPproj.sln, ...)
IDE/COMPILER:			MicroSoft Visual Studio 2012
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Double click on myCPPproj.sln	to OPEN the project
2.		Press Ctrl+F7					to COMPILE
3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
4.		Press Ctrl+F5					to EXECUTE
===================================================================================*/
#define _USE_MATH_DEFINES
#include <GL/glut.h>				// include GLUT library
#include <cmath>
#include <math.h>

//***********************************************************************************
void drawPoints()
{

	// left eye
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(1.0, 0, 0);
	glVertex2i(-50, 50);
	glEnd();

	// right eye
	glPointSize(10);
	glBegin(GL_POINTS);
	glColor3f(0.5, 0.5, 0);
	glVertex2i(50, 50);
	glEnd();

	// head
	int radius = 130;
	int y_offset = 0;
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(0.75, 0.25, 0);
	for (int x=0; x<360; x++){
		float radians = x*(M_PI/180);
		glVertex2f(cos(radians)*radius, sin(radians)*radius+y_offset);
	}
	glEnd();

	// smile
	radius = 80;
	y_offset = -10;
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(0.75, 0.25, 0);
	for (int x=-180; x<0; x++){
		float radians = x*(M_PI/180);
		glVertex2f(cos(radians)*radius, sin(radians)*radius+y_offset);
	}
	glEnd();

	// X-Y axis
	glPointSize(1);		// change point size back to 1

	glBegin(GL_POINTS);	// use points to form X-/Y-axes
	glColor3f(0, 0, 0);			 // change drawing color to black
	for (int x=-150; x<=150; x++) // draw X-axis
		glVertex2i(x, 0);
	for (int y=-150; y<=150; y++) // draw Y-axis
		glVertex2i(0, y);
	glEnd();
}

//***********************************************************************************
void myInit()
{
	glClearColor(1, 1, 1, 0);			// specify a background clor: white 
	gluOrtho2D(-200, 200, -200, 200);  // specify a viewing area
}

//***********************************************************************************
void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background

	drawPoints();

	glFlush(); // flush out the buffer contents
}

//***********************************************************************************
void main(int argc, char ** argv)
{
	glutInit(& argc, argv);

	glutInitWindowSize(400, 400);				// specify a window size
	glutInitWindowPosition(100, 0);			// specify a window position
	glutCreateWindow("Simple Point Drawing");	// create a titled window

	myInit();									// setting up

	glutDisplayFunc(myDisplayCallback);		// register a callback

	glutMainLoop();							// get into an infinite loop
}
