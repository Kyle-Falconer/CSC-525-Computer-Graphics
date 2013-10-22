/*===================================================================================
PROGRAMMER:			Yang Wang
COURSE:				CSC 525/625
MODIFIED BY:			Kyle Falconer
LAST MODIFIED DATE:	Aug. 30, 2013
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

#include <GL/glut.h>				// include GLUT library
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int point1[] = {-150, 25};
int point2[] = {150, -25};

GLushort selectedPattern;
GLushort pattern0 = 0xFFFF;
GLushort pattern1 = 0x0300;
GLushort pattern2 = 0x2E81;


//***********************************************************************************
void drawPoints()
{

	glLineWidth(5);
	glLineStipple(1, selectedPattern);
	glEnable(GL_LINE_STIPPLE);	
	glBegin(GL_LINES);

	glColor3f(1.0, 0, 0);
	glVertex2i(point1[0], point1[1]);
	glVertex2i(point2[0], point2[1]);

	glEnd();
	glDisable(GL_LINE_STIPPLE);

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
	cout << "Choose a stipple:" << endl;
	cout << "1: no stipple" << endl;
	cout << "2: ______--________" << endl;
	cout << "3: __-_---_-______-" << endl;
	
	int selectedStipple = 0;
	cin >> selectedStipple;

	
	while (selectedStipple >3 || selectedStipple < 1) {
		cout << "Invalid number, please try again" << endl;
		cin >> selectedStipple;
	}
	
	
	if (selectedStipple == 1){
		selectedPattern = pattern0;
	} else if (selectedStipple == 2){
		selectedPattern = pattern1;
	} else if (selectedStipple == 3){
		selectedPattern = pattern2;
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
