/*===================================================================================
PROGRAMMER:			Yang Wang
COURSE:				CSC 525/625
MODIFIED BY:			Kyle Falconer
LAST MODIFIED DATE:	Sept. 9, 2013
DESCRIPTION:			Demo: drawing polygons.
NOTE:					N/A
FILES:					polygons.cpp, (labProject.sln, ...)
IDE/COMPILER:			Microsoft Visual Studio 2012
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Double click on labProject.sln	to OPEN the project
2.		Press Ctrl+F7					to COMPILE
3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
4.		Press Ctrl+F5					to EXECUTE
===================================================================================*/

#include <GL/glut.h>				// include GLUT library
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

GLenum  polyMode;

bool polyStipple = false;
GLubyte letter_F [] = {
	0x00, 0x00, 0x00, 0x00, // line 1
	0x00, 0x00, 0x00, 0x00, // line 2
	0x00, 0x00, 0x00, 0x00, // line 3
	0x0f, 0x00, 0x00, 0x00, // line 4
	0x0f, 0x00, 0x00, 0x00, // line 5
	0x0f, 0x00, 0x00, 0x00, // line 6
	0x0f, 0x00, 0x00, 0x00, // line 7
	0x0f, 0x00, 0x00, 0x00, // line 8
	0x0f, 0x00, 0x00, 0x00, // line 9
	0x0f, 0x00, 0x00, 0x00, // line 10
	0x0f, 0x00, 0x00, 0x00, // line 11
	0x0f, 0x00, 0x00, 0x00, // line 12
	0x0f, 0x00, 0x00, 0x00, // line 13
	0x0f, 0x00, 0x00, 0x00, // line 14
	0x0f, 0x00, 0x00, 0x00, // line 15
	0x0f, 0x00, 0x00, 0x00, // line 16
	0x0f, 0x00, 0x00, 0x00, // line 17
	0x0f, 0x00, 0x00, 0x00, // line 18
	0x0f, 0x00, 0x00, 0x00, // line 19
	0x0f, 0xff, 0xff, 0x00, // line 20
	0x0f, 0xff, 0xff, 0x00, // line 21
	0x0f, 0xff, 0xff, 0x00, // line 22
	0x0f, 0x00, 0x00, 0x00, // line 23
	0x0f, 0x00, 0x00, 0x00, // line 24
	0x0f, 0x00, 0x00, 0x00, // line 25
	0x0f, 0x00, 0x00, 0x00, // line 26
	0x0f, 0xff, 0xff, 0x00, // line 27
	0x0f, 0xff, 0xff, 0x00, // line 28
	0x0f, 0xff, 0xff, 0x00, // line 29
	0x00, 0x00, 0x00, 0x00, // line 30
	0x00, 0x00, 0x00, 0x00, // line 31
	0x00, 0x00, 0x00, 0x00, // line 32
};

//***********************************************************************************
void drawPoints()
{

	glLineWidth(2);
	glPointSize(5);	
	
	if (polyStipple)
		glPolygonStipple(letter_F);

	glEnable(GL_POLYGON_STIPPLE);
	glPolygonMode(GL_FRONT_AND_BACK, polyMode);

	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex2i(0, 80);
	glColor3f(0.0, 1.0, 0.0);
	glVertex2i(-70, 0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex2i(-30, -60);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2i(30, -60);
	glColor3f(0.0, 1.0, 1.0);
	glVertex2i(70, 0);
	glEnd();
	glDisable(GL_POLYGON_STIPPLE);
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



void menuPrompt(){
	string input = "";
	cout << "Choose a display mode:" << endl;
	cout << "1: GL_FILL" << endl;
	cout << "2: GL_LINE" << endl;
	cout << "3: GL_POINT" << endl;
	cout << "4: Fill with a pattern" << endl;
	
	int selectedMode = 0;
	cin >> selectedMode;

	
	while (selectedMode >4 || selectedMode < 1) {
		cout << "Invalid number, please try again" << endl;
		cin >> selectedMode;
	}
	
	
	if (selectedMode == 1){
		polyMode = GL_FILL;
	} else if (selectedMode == 2){
		polyMode = GL_LINE;
	} else if (selectedMode == 3){
		polyMode = GL_POINT;
	} else if (selectedMode == 4){
		polyMode = GL_FILL;
		polyStipple = true;
	}
	// cout << selectedStipple << endl;


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
	menuPrompt();
	// cout << selectedPattern << endl;
	glutInit(& argc, argv);


	glutInitWindowSize(400, 400);				// specify a window size
	glutInitWindowPosition(100, 0);			// specify a window position
	glutCreateWindow("Simple Point Drawing");	// create a titled window

	myInit();									// setting up

	glutDisplayFunc(myDisplayCallback);		// register a callback

	glutMainLoop();							// get into an infinite loop
}
