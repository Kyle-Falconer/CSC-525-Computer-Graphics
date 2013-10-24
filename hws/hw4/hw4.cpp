/*===================================================================================
 PROGRAMMER:			Brett Story,	Kyle Falconer
 FOLDERS:				Brett322,		Falconer1
 BRETT'S TASKS:			(Contribution: 50%)
 KYLE'S TASKS:			(Contribution: 50%)
 COURSE:				CSC 525/625
 MODIFIED BY:			N/A
 LAST MODIFIED DATE:	Oct. 25, 2013
 DESCRIPTION:			A simple text editor.

 FILES:					h4.cpp, (hwProject.sln, ...)
 IDE/COMPILER:			MicroSoft Visual Studio 2012
 INSTRUCTION FOR COMPILATION AND EXECUTION:
	1.		Double click on labProject.sln	to OPEN the project
	2.		Press Ctrl+F7					to COMPILE
	3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
	4.		Press Ctrl+F5					to EXECUTE
===================================================================================*/

#define _USE_MATH_DEFINES
#include <iostream>
#include <GL/glut.h>				// include GLUT library
#include <cmath>					// include math library
#include <string>
using namespace std;

// To allow file reading
#include <fstream>
using std::ifstream;

// To exit if the file doesn't exist
#include <cstdlib>

int mainWindow;		// id for the main window
int infoWindow;		// id for the help window
int editorWindow;	// id for the editor subwindow
int menuWindow;		// id for menu subwindow

int rowHeight = 18;	// Rows will be 18 world units, leaving 45 units worth of buffer
int row[30][2];		// There are 30 rows with 2 parameters each: Y-Position and an array of characters
// Each character inside of the character array will have 5 parameters, R, G, B, Font, and char
int xRowPosition = 285;

void drawEditor()
{
	glutSetWindow(editorWindow);	// Sets window to editor

	int drawLinePosition = 250; //accounting for menu at top and 25 unit buffer

	glColor3f(.9, .9, .9);
	glPointSize(1);

	for (int i = 0; i < 30; i ++)
	{
		glBegin(GL_LINES);
			glVertex2i(-xRowPosition, drawLinePosition);
			glVertex2i(xRowPosition, drawLinePosition);
		glEnd();
		row[i][0] = drawLinePosition;			// Defines row heights while drawing lines
		drawLinePosition -= rowHeight;
	}
}

void drawMenu()
{
	glutSetWindow(menuWindow);		// Sets window to menu
}

void drawInfo()
{
	glutSetWindow(infoWindow);  
}

void mainInit()
{
	glClearColor(1, 1, 1, 0);			// specify a background
	gluOrtho2D(-300, 300, -300, 300);  // specify a viewing area
}

void editorInit()
{
	glClearColor(1, 1, 1, 0);			// specify a background
	gluOrtho2D(-300, 300, -300, 275);  // specify a viewing area
	glutSetCursor(GLUT_CURSOR_TEXT);
}

void menuInit()
{
	glClearColor(.75, .75, .75, 0);			// specify a background
	gluOrtho2D(-300, 300, -19, 0);  // specify a viewing area
}

void infoInit()
{
	glClearColor(1, 1, 1, 0);			// specify a background
	gluOrtho2D(-200, 200, -300, 300);  // specify a viewing area
}

//***********************************************************************************
void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background

	drawEditor();
	drawMenu();
	drawInfo();

	glFlush(); // flush out the buffer contents
}

//***********************************************************************************
void main(int argc, char ** argv)
{
	glutInit(& argc, argv);

	glutInitWindowSize(768, 768);							// specify a window size
	glutInitWindowPosition(500, 50);							// specify a window position
	mainWindow = glutCreateWindow("Simple Text Editor");	// create a titled window

	mainInit();									// setting up
	glutDisplayFunc(myDisplayCallback);		// register a callback

	editorWindow = glutCreateSubWindow(mainWindow, 0, 32, 768, 736);
	editorInit();
	glutDisplayFunc(myDisplayCallback);

	menuWindow = glutCreateSubWindow(mainWindow, 0, 0, 768, 32);
	menuInit();
	glutDisplayFunc(myDisplayCallback);

	glutInitWindowSize(384, 576);							// specify a window size
	glutInitWindowPosition(50, 50);							// specify a window position

	infoWindow = glutCreateWindow("Info/Help");
	infoInit();
	glutDisplayFunc(myDisplayCallback);

	glutMainLoop();							// get into an infinite loop
	
}