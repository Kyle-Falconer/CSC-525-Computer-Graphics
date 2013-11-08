/*===================================================================================
PROGRAMMER:			Kyle Falconer
FOLDERS:			Falconer1
COURSE:				CSC 525/625
MODIFIED BY:			N/A
LAST MODIFIED DATE:	Nov. 8, 2013
DESCRIPTION:		Demonstration of 2D transformations.
NOTES:				Use the right mouse button to activate the menu.
					Click and hold the left mouse button, then move the mouse
					left or right to adjust the value for that transformation.

FILES:					h5.cpp, (hwProject.sln, ...)
IDE/COMPILER:			MicroSoft Visual Studio 2012
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Double click on hwProject.sln	to OPEN the project
2.		Press Ctrl+F7					to COMPILE
3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
4.		Press Ctrl+F5					to EXECUTE
===================================================================================*/

#include "glut.h"
#include <cmath>
#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision


enum Menu_Option {
	translate_x,
	translate_y,
	rotate_o,
	scale_x,
	scale_y,
	exit_program
};

Menu_Option selected_transformation = scale_y;

void textMenu();
void menu_handler(int); // Menu handling function declaration

void translateX();
void translateY();
void rotateDegrees();
void scaleX();
void scaleY();


const int window_size[2] = {600, 600};

int last_mouseX = 0;
int last_mouseY = 0;
int mousedown_x = 0;
int mousedown_y = 0;

const int numVertices = 4;
const int numDimensions = 2;
const float orig_poly[numVertices][numDimensions] = {
	{100, 100},
	{-100, 100},
	{-100, -100},
	{100, -100}
};

float poly[numVertices][numDimensions] = {
	{100, 100},
	{-100, 100},
	{-100, -100},
	{100, -100}
};

float poly_colors[4][3] = {
	{1.0, 0.0, 0.0},
	{0.0, 1.0, 0.0},
	{0.0, 0.0, 1.0},
	{1.0, 1.0, 0.0}
};

void drawAxis(){

	int axis_width_x = window_size[0]/2 -20;
	int axis_width_y = window_size[1]/2 -20;

	// X-Y axis
	glPointSize(1);		// change point size back to 1
	glBegin(GL_POINTS);	// use points to form X-/Y-axes
	glColor3f(0, 0, 0);			 // change drawing color to black
	for (int x=-axis_width_x; x<=axis_width_x; x++) // draw X-axis
		glVertex2i(x, 0);
	for (int y=-axis_width_y; y<=axis_width_y; y++) // draw Y-axis
		glVertex2i(0, y);
	glEnd();

	glRasterPos2i(axis_width_x, -10);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'x');

	glRasterPos2i(-10, axis_width_y);
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'y');

}


void textMenu(){

	glutCreateMenu(menu_handler);
	glutAddMenuEntry("translate_x", translate_x);
	glutAddMenuEntry("translate_y", translate_y);
	glutAddMenuEntry("rotate", rotate_o);
	glutAddMenuEntry("scale_x", scale_x);
	glutAddMenuEntry("scale_y", scale_y);
	glutAddMenuEntry("EXIT", exit_program);

	// Associate a mouse button with menu
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}

// Menu handling function definition
void menu_handler(int item)
{
	switch (item)
	{

	case translate_x:
		selected_transformation = translate_x;
		break;

	case translate_y:
		selected_transformation = translate_y;
		break;

	case rotate_o:
		selected_transformation = rotate_o;
		break;

	case scale_x:
		selected_transformation = scale_x;
		break;

	case scale_y:
		selected_transformation = scale_y;
		break;

	case exit_program:
		exit(0);
		break;

	}

	glutPostRedisplay();
	return;
}



void translateX(float offset){
	for (int i = 0; i < numVertices; i++){
		poly[i][0] = poly[i][0] + offset;
	}
}

void translateY(float offset){
	for (int i = 0; i < numVertices; i++){
		poly[i][1] = poly[i][1] + offset;
	}
}

void rotateDegrees(float degrees){
	float theta = degrees/180;
	for (int i = 0; i < numVertices; i++){
		poly[i][0] = poly[i][0] * cos(theta) +  poly[i][1] * sin(theta);
		poly[i][1] = -poly[i][0] * sin(theta) +  poly[i][1] * cos(theta);
	}
}

void scaleX(float scale){
	scale = scale == 0 ? 0.1 : scale;
	scale = (scale/(window_size[0]/2))*100;
	cout << "scale: "<< setprecision(3) << scale << endl;
	for (int i = 0; i < numVertices; i++){
		poly[i][0] = orig_poly[i][0] * scale;
	}
}

void scaleY(float scale){
	scale = scale == 0 ? 0.1 : scale;
	scale = (scale/(window_size[1]/2))*100;
	cout << "scale: "<< setprecision(3) << scale << endl;
	for (int i = 0; i < numVertices; i++){
		poly[i][1] = orig_poly[i][1] * scale;
	}
}

void drawPolygon() {

	glBegin(GL_POLYGON);
	glColor3f(poly_colors[0][0], poly_colors[0][1], poly_colors[0][2]);
	glVertex2i(poly[0][0], poly[0][1]);

	glColor3f(poly_colors[1][0], poly_colors[1][1], poly_colors[1][2]);
	glVertex2i(poly[1][0], poly[1][1]);

	glColor3f(poly_colors[2][0], poly_colors[2][1], poly_colors[2][2]);
	glVertex2i(poly[2][0], poly[2][1]);

	glColor3f(poly_colors[3][0], poly_colors[3][1], poly_colors[3][2]);
	glVertex2i(poly[3][0], poly[3][1]);
	glEnd();

}


void drawText(int win, float x, float y, float r, float g, float b, std::string text){
	glutSetWindow(win);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2i(x,y);
	void * font = GLUT_BITMAP_8_BY_13;
	for (string::iterator i = text.begin(); i != text.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
}

void mainInit() {
	glClearColor(1, 1, 1, 0);			// specify a background
	gluOrtho2D(-300, 300, -300, 300);  // specify a viewing area

}



void menuInit() {
	glClearColor(.75, .75, .75, 0);			// specify a background
	gluOrtho2D(-10, 300,-10, 19);  // specify a viewing area

	textMenu();
}



//***********************************************************************************
void myDisplayCallback() {
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background

	drawAxis();

	drawPolygon();

	glFlush(); // flush out the buffer contents
}

void mouseClick(int button, int state, int x, int y){

	if (state == GLUT_DOWN){
		mousedown_x = x -  (window_size[0]/2);
		mousedown_y = (window_size[1]/2) -  y;
	}

	myDisplayCallback();
}

void mouseMove(int x, int y){
	int window_x =  x -  (window_size[0]/2);
	int window_y =  (window_size[1]/2) -  y;
	int delta_x = window_x -  last_mouseX;
	int delta_y = window_y -  last_mouseY;

	last_mouseX = window_x;
	last_mouseY = window_y;

	switch (selected_transformation)
	{

	case translate_x:
		translateX(delta_x);
		break;

	case translate_y:
		translateY(delta_y);
		break;

	case rotate_o:
		rotateDegrees(delta_x);
		break;

	case scale_x:
		scaleX(mousedown_x - window_x);
		break;

	case scale_y:
		scaleY(mousedown_y - window_y);
		break;
	}

	myDisplayCallback();
}


//***********************************************************************************
void main(int argc, char ** argv) {
	glutInit(& argc, argv);

	glutInitWindowSize(window_size[0], window_size[1]);		// specify a window size
	glutInitWindowPosition(500, 50);						// specify a window position
	glutCreateWindow("2D Transformations");					// create a titled window
	mainInit();												// setting up
	glutDisplayFunc(myDisplayCallback);						//register a callback
	textMenu();

	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMove);

	glutMainLoop();
}