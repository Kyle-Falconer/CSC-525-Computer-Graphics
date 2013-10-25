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

#include "glut.h"
#include "glChar.h"
#include "text_menu.h"



// To allow file reading
#include <fstream>
using std::ifstream;

// To exit if the file doesn't exist
#include <cstdlib>

int mainWindow;		// id for the main window
int infoWindow;		// id for the help window
int editorWindow;	// id for the editor subwindow
int menuWindow;		// id for menu subwindow

bool hasTyped = false;


std::vector<glChar> text;

void letterInput(unsigned char key, int xMouse, int yMouse) {
	glChar tmp;
	tmp.setValues(key, selected_text_color[0], selected_text_color[1], selected_text_color[2], selected_font);
	text.push_back(tmp);
	switch (key)
	{
		case 8:
			if (text.size() > 0) {
				text.pop_back();
				glutPostRedisplay();
			}
			break;
		case 13:
			glChar enter;
			enter.setValues('\n', selected_text_color[0], selected_text_color[1], selected_text_color[2], selected_font);
			text.push_back(enter);
			break;
		default:
			glChar tmp;
			tmp.setValues(key, selected_text_color[0], selected_text_color[1], selected_text_color[2], selected_font);
			text.push_back(tmp);
			break;
	}
	hasTyped = true;
	glutPostRedisplay();
}

void mouseInput(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && hasTyped == false) {
		int yWorld = y/1.28 - 300;
		for (int i = 0; i < 0; i++) {
			if (typingPositionY - i*rowHeight >= yWorld)
			{
				curRow = i;
			}
		}
		glutPostRedisplay();
	}
}

void drawEditor() {
	glutSetWindow(editorWindow);	// Sets window to editor

	int drawLinePosition = 250; //accounting for menu at top and 25 unit buffer

	glPointSize(1);

	for (int i = 0; i < 30; i ++)
	{
		glBegin(GL_LINES);
		glColor3f(.9, .9, .9);
		glVertex2i(-xRowPosition, drawLinePosition);
		glVertex2i(xRowPosition, drawLinePosition);
		glEnd();
		drawLinePosition -= rowHeight;
	}

	glRasterPos2i(typingPositionX, typingPositionY - curRow*rowHeight + 3);

	// Iterates over text vector and displays all current text
	for(auto i : text) {
		i.display();
	}
	if (hasTyped) {
		GLfloat pos[4];
		glGetFloatv(GL_CURRENT_RASTER_POSITION, pos);
		float xPosition = pos[0]/1.28 - 300;
		float yPosition = pos[1]/1.28 - 300;

		glBegin(GL_LINE_STRIP);
			glColor3f(selected_text_color[0], selected_text_color[1], selected_text_color[2]);
			glVertex2i(xPosition + 5, yPosition);
			glVertex2i(xPosition + 10, yPosition);
			glVertex2i(xPosition + 10, yPosition + 10);
			glVertex2i(xPosition + 5, yPosition + 10);
			glVertex2i(xPosition + 5, yPosition);
		glEnd();
	}
	else
	{
		glBegin(GL_LINE_STRIP);
			glColor3f(selected_text_color[0], selected_text_color[1], selected_text_color[2]);
			glVertex2i(-typingPositionX, typingPositionY - curRow*rowHeight - 15);
			glVertex2i(-typingPositionX + 5, typingPositionY - curRow*rowHeight - 15);
			glVertex2i(-typingPositionX + 5, typingPositionY - curRow*rowHeight - 5);
			glVertex2i(-typingPositionX, typingPositionY - curRow*rowHeight - 5);
			glVertex2i(-typingPositionX, typingPositionY - curRow*rowHeight - 15);
		glEnd();
	}
}

void drawMenu() {
	glutSetWindow(menuWindow);		// Sets window to menu
}

void drawInfo() {
	glutSetWindow(infoWindow);  
}

void mainInit() {
	glClearColor(1, 1, 1, 0);			// specify a background
	gluOrtho2D(-300, 300, -300, 300);  // specify a viewing area

}

void editorInit() {
	glClearColor(1, 1, 1, 0);			// specify a background
	gluOrtho2D(-300, 300, -300, 275);  // specify a viewing area
	glutSetCursor(GLUT_CURSOR_TEXT);
	glutMouseFunc(mouseInput);
	glutKeyboardFunc(letterInput);
}

void menuInit() {
	glClearColor(.75, .75, .75, 0);			// specify a background
	gluOrtho2D(-300, 300, -19, 0);  // specify a viewing area
}

void infoInit() {
	glClearColor(1, 1, 1, 0);			// specify a background
	gluOrtho2D(-200, 200, -300, 300);  // specify a viewing area
}

//***********************************************************************************
void myDisplayCallback() {
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background

	drawEditor();
	drawMenu();
	drawInfo();

	glFlush(); // flush out the buffer contents
}

//***********************************************************************************
void main(int argc, char ** argv) {
	glutInit(& argc, argv);

	glutInitWindowSize(384, 576);							// specify a window size
	glutInitWindowPosition(50, 50);							// specify a window position
	infoWindow = glutCreateWindow("Info/Help");
	infoInit();
	glutDisplayFunc(myDisplayCallback);

	glutInitWindowSize(768, 768);							// specify a window size
	glutInitWindowPosition(500, 50);							// specify a window position
	mainWindow = glutCreateWindow("Simple Text Editor");	// create a titled window
	mainInit();									// setting up
	glutDisplayFunc(myDisplayCallback);		// register a callback

	menuWindow = glutCreateSubWindow(mainWindow, 0, 0, 768, 32);
	menuInit();
	glutDisplayFunc(myDisplayCallback);

	// Initialize editor window last so that user can begin typing
	editorWindow = glutCreateSubWindow(mainWindow, 0, 32, 768, 736);
	editorInit();
	glutDisplayFunc(myDisplayCallback);

	glutMainLoop();							// get into an infinite loop

}
