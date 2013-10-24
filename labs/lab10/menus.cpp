/*===================================================================================
PROGRAMMER:				Yang Wang
COURSE:					CSC 525/625
MODIFIED BY:			Kyle Falconer
LAST MODIFIED DATE:		Oct. 14, 2013
DESCRIPTION:			Demo: using menus and submenus with OpenGL
NOTE:					N/A
FILES:					menus.cpp, (labProject.sln, ...)
IDE/COMPILER:			Microsoft Visual Studio 2012
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Double click on labProject.sln	to OPEN the project
2.		Press Ctrl+F7					to COMPILE
3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
4.		Press Ctrl+F5					to EXECUTE
===================================================================================*/

#include <iostream>
#include <GL/glut.h>				// include GLUT library
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

string readTextFromFile(string filename);
int readValidInt();
void menuPrompt();

GLenum  polyMode;
int point_1[2];


// Assign a default value
void * font = GLUT_BITMAP_8_BY_13;
float text_color[3] = {0, 0, 0};

enum Menu_Option {
	glut_red,
	glut_green,
	glut_8_BY_13,
	glut_9_BY_15, 
	glut_TIMES_ROMAN_10,
	glut_TIMES_ROMAN_24,
	glut_HELVETICA_10,
	glut_HELVETICA_12,
	glut_HELVETICA_18,
	exit_program
};


// Menu handling function declaration
void menu(int);

//***********************************************************************************
void drawPoints()
{

	glLineWidth(1);
	glPointSize(1);	

	glColor3f(text_color[0], text_color[1], text_color[2]);
	glRasterPos2i(point_1[0], point_1[1]);
	string s = readTextFromFile("\\\\eccentric\\class\\csc525-625\\001\\_download\\Labs\\lab10\\greeting.txt");
	for (string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}


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


void menu_init(){





	int menu_main, submenu_colors, submenu_fonts;

	submenu_colors =  glutCreateMenu(menu);
	glutAddMenuEntry("Red", glut_red);
	glutAddMenuEntry("Green", glut_green);

	submenu_fonts =  glutCreateMenu(menu);
	glutAddMenuEntry("GLUT_BITMAP_8_BY_13", glut_8_BY_13);
	glutAddMenuEntry("GLUT_BITMAP_9_BY_15", glut_9_BY_15);
	glutAddMenuEntry("GLUT_BITMAP_TIMES_ROMAN_10", glut_TIMES_ROMAN_10);
	glutAddMenuEntry("GLUT_BITMAP_TIMES_ROMAN_24", glut_TIMES_ROMAN_24);
	glutAddMenuEntry("GLUT_BITMAP_HELVETICA_10", glut_HELVETICA_10);
	glutAddMenuEntry("GLUT_BITMAP_HELVETICA_12", glut_HELVETICA_12);
	glutAddMenuEntry("GLUT_BITMAP_HELVETICA_18", glut_HELVETICA_18);

	menu_main = glutCreateMenu(menu);
	glutAddSubMenu("Colors", submenu_colors);
	glutAddSubMenu("Fonts", submenu_fonts);
	glutAddMenuEntry("EXIT", exit_program);

	// Associate a mouse button with menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

// Menu handling function definition
void menu(int item)
{
	switch (item)
	{

	case glut_red:
		{
			text_color[0] = 1.0;
			text_color[1] = 0.0;
			text_color[2] = 0.0;
		}
		break;
	case glut_green:
		{
			text_color[0] = 0.0;
			text_color[1] = 1.0;
			text_color[2] = 0.0;
		}
		break;
	case glut_8_BY_13:
		{
			font = GLUT_BITMAP_8_BY_13;
		}
		break;
	case glut_9_BY_15:
		{
			font = GLUT_BITMAP_9_BY_15;
		}
		break;
	case glut_TIMES_ROMAN_10:
		{
			font = GLUT_BITMAP_TIMES_ROMAN_10;
		}
		break;
	case glut_TIMES_ROMAN_24:

		{
			font = GLUT_BITMAP_TIMES_ROMAN_24;
		}
		break;

	case glut_HELVETICA_10:
		{
			font = GLUT_BITMAP_HELVETICA_10;
		}
		break;
	case glut_HELVETICA_12:
		{
			font = GLUT_BITMAP_HELVETICA_12;
		}
		break;

	case glut_HELVETICA_18:
		{
			font = GLUT_BITMAP_HELVETICA_18;
		}
		break;

	case exit_program:
		{
			exit(0);
		}
		break;
	default:
		{
			font =  GLUT_BITMAP_8_BY_13;
		}
		break;
	}

	glutPostRedisplay();

	return;
}

int readValidInt(){
	string user_input;
	int result;
	while (true) {
		getline(cin, user_input);

		// This code converts from string to number safely.
		stringstream myStream(user_input);
		if (myStream >>  result && ( result >= -200 && result <= 200))
			break;

		cout << "Given number is invalid or out of range; please enter a number in the range [-200, 200]" << endl;
	}
	return result;
}

string readTextFromFile(string filename){
	ifstream f_in(filename);
	string read_lines = "";

	if (f_in.is_open()){
		string temp_line = "";
		while (getline(f_in, temp_line)){
			cout << read_lines << endl;
			read_lines.append(temp_line);
		}
		f_in.close();
	} else {
		cout << "could not open file: " << filename << endl;
	}
	return read_lines;
}



//***********************************************************************************
void myInit()
{
	point_1[0] = -50;
	point_1[1] = 50;
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

	// cout << selectedPattern << endl;
	glutInit(& argc, argv);


	glutInitWindowSize(400, 400);				// specify a window size
	glutInitWindowPosition(100, 0);			// specify a window position
	glutCreateWindow("Menu Demonstration");	// create a titled window
	menu_init();
	myInit();									// setting up

	glutDisplayFunc(myDisplayCallback);		// register a callback

	glutMainLoop();							// get into an infinite loop
}
