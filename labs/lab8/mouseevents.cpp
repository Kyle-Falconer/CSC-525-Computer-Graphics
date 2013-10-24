/*===================================================================================
PROGRAMMER:				Yang Wang
COURSE:					CSC 525/625
MODIFIED BY:			Kyle Falconer
LAST MODIFIED DATE:		Sept. 30, 2013
DESCRIPTION:			Demo: mouse event handling with OpenGL
NOTE:					N/A
FILES:					mouseevents.cpp, (labProject.sln, ...)
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
int mButton = -1;

//***********************************************************************************
void drawPoints()
{

	glLineWidth(1);
	glPointSize(1);	

	if (mButton >= 0){

		if (mButton == 0){// left mouse button
			glColor3f(1.0, 0.0, 0.0);
		} else if (mButton == 2){ // right mouse button
			glColor3f(0.0, 1.0, 0.0);
		} else {
			glColor3f(0.0, 0.0, 0.0);
		}

		glRasterPos2i(point_1[0], point_1[1]);
		string s = readTextFromFile("\\\\eccentric\\class\\csc525-625\\001\\_download\\Labs\\lab8\\greeting.txt");
		void * font = GLUT_BITMAP_8_BY_13;
		for (string::iterator i = s.begin(); i != s.end(); ++i)
		{
			char c = *i;
			glutBitmapCharacter(font, c);
		}
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

void mouseClick(int button, int state, int x, int y){
	
		point_1[0] = x-200;
		point_1[1] = 200-y;
		mButton = button;
		myDisplayCallback();
		cout << x << ", " << y << " button: " << button << endl;		
	

}

void mouseMove(int x, int y){
		point_1[0] = x-200;
		point_1[1] = 200-y;
		myDisplayCallback();	
}

//***********************************************************************************
void main(int argc, char ** argv)
{

	// cout << selectedPattern << endl;
	glutInit(& argc, argv);



	glutInitWindowSize(400, 400);				// specify a window size
	glutInitWindowPosition(100, 0);			// specify a window position
	glutCreateWindow("Simple Point Drawing");	// create a titled window

	myInit();									// setting up

	glutMotionFunc(mouseMove);
	glutMouseFunc(mouseClick);
	glutDisplayFunc(myDisplayCallback);		// register a callback

	glutMainLoop();							// get into an infinite loop
}
