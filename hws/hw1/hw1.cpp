/*===================================================================================
PROGRAMMER:			Kyle Falconer
ECCENTRIC FOLDER:	falconer1
COURSE:				CSC 525/625
ASSIGNMENT:			Homework 1
LAST MODIFIED DATE:	Sept. 13, 2013
DESCRIPTION:			Demonstration of algorithms used for plotting line segments.
NOTE:					N/A
FILES:					hw1.cpp, (hwProject.sln, ...)
IDE/COMPILER:			Microsoft Visual Studio 2012
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Double click on hwProject.sln	to OPEN the project
2.		Press Ctrl+F7					to COMPILE
3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
4.		Press Ctrl+F5					to EXECUTE
===================================================================================*/


#include <stdlib.h>     
#include <GL/glut.h> 
#include <iostream>
#include <string>
#include <sstream>
using namespace std;



int point_1[2];
int point_2[2];

void plotLine(int* p_1, int* p_2){

	if ((p_1[0] == p_2[0]) && (p_1[1] == p_2[1])){
		// single point
		glVertex2i(p_1[0], p_1[1]);

	} else if (p_2[0] == p_1[0]){
		// vertical line
		if (p_2[1] < p_1[1]){
			int temp = p_1[0];
			p_1[0] = p_2[0];
			p_2[0] = temp;
			temp = p_1[1];
			p_1[1] = p_2[1];
			p_2[1] = temp;
		}

		for (int y = p_1[1]; y < p_2[1]; y++){
			glVertex2i(p_1[0], y);
		}

	} else {
		// diagonal line
		
		float dy = (p_2[1] - p_1[1]);
		float dx = (p_2[0] - p_1[0]);

		
		// m = (y2-y1)/(x2-x1)
		float slope =  dy / dx;

		cout << slope << endl;

		// b = y - mx
		float y_intercept  = p_1[1] - (slope*p_1[0]);

		if (slope <= 1 && slope > 0){
			if (p_2[0] < p_1[0]){
				int temp = p_1[0];
				p_1[0] = p_2[0];
				p_2[0] = temp;
				temp = p_1[1];
				p_1[1] = p_2[1];
				p_2[1] = temp;
			}

			
			for (int x = p_1[0]; x < p_2[0]; x++){
				// y = mx+b
				int y = (slope*x) + y_intercept;
				glVertex2i(x, y);
			}

		} else {
			if (p_2[1] < p_1[1]){
				int temp = p_1[0];
				p_1[0] = p_2[0];
				p_2[0] = temp;
				temp = p_1[1];
				p_1[1] = p_2[1];
				p_2[1] = temp;
			}
			
			for (int y = p_1[1]; y < p_2[1]; y++){
				// x = (y-b)/m 
				int x = (y - y_intercept )/slope;
				glVertex2i(x, y);
			}

		}
	}
}

void drawPoints()
{
	glPointSize(1);	
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 0.0);

	plotLine(point_1, point_2);

	glEnd();

	// X-Y axis
	glPointSize(1);		// change point size back to 1
	glBegin(GL_POINTS);	// use points to form X-/Y-axes
	glColor3f(0.45F, 0.45F, 0.45F);			 // change drawing color to black
	for (int x=-150; x<=150; x++) // draw X-axis
		glVertex2i(x, 0);
	for (int y=-150; y<=150; y++) // draw Y-axis
		glVertex2i(0, y);
	glEnd();
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

void menuPrompt(){

	point_1[0] = 0;
	point_1[1] = 0;
	point_2[0] = 0;
	point_2[1] = 0;
	string user_input;

	cout << "Enter the x-coordinate for the first point" << endl;
	cout << "x1 = ";
	point_1[0] = readValidInt();

	cout << "Enter the y-coordinate for the first point" << endl;
	cout << "y1 = ";
	point_1[1] = readValidInt();


	cout << "Enter the x-coordinate for the second point" << endl;
	cout << "x2 = ";
	point_2[0] = readValidInt();

	cout << "Enter the y-coordinate for the second point" << endl;
	cout << "y2 = ";
	point_2[1] = readValidInt();

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
