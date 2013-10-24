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

int infoWindow;		// id for the help window
int editorWindow;	// id for the main window
int menuWindow;		// id for subwindow with menus

void drawEditor()
{
	glutSetWindow(editorWindow);	// Sets window to editor

}

void drawMenu()
{
	glutSetWindow(menuWindow);		// Sets window to menu
}

void drawInfo()
{
	glutSetWindow(infoWindow);  
}

void editorInit()
{
	glClearColor(1, 1, 1, 0);			// specify a background clor: blueish-green
	gluOrtho2D(-400, 400, -300, 300);  // specify a viewing area
}

void menuInit()
{
	glClearColor(.5, .5, .5, 0);			// specify a background clor: blueish-green
	gluOrtho2D(-400, 400, -19, 0);  // specify a viewing area
}

void infoInit()
{
	glClearColor(.5, .5, .5, 0);			// specify a background clor: blueish-green
	gluOrtho2D(-200, 200, -400, 400);  // specify a viewing area
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

	glutInitWindowSize(1024, 768);							// specify a window size
	glutInitWindowPosition(500, 0);							// specify a window position
	editorWindow = glutCreateWindow("Simple Text Editor");	// create a titled window

	editorInit();									// setting up
	glutDisplayFunc(myDisplayCallback);		// register a callback

	menuWindow = glutCreateSubWindow(editorWindow, 0, 0, 1024, 24);
	menuInit();
	glutDisplayFunc(myDisplayCallback);


	glutInitWindowSize(384, 768);							// specify a window size
	glutInitWindowPosition(100, 0);							// specify a window position

	infoWindow = glutCreateWindow("Info/Help");
	infoInit();
	glutDisplayFunc(myDisplayCallback);

	glutMainLoop();							// get into an infinite loop
	
}