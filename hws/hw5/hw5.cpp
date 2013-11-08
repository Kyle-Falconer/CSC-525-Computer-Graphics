/*===================================================================================
PROGRAMMER:			Kyle Falconer
FOLDERS:			Falconer1
COURSE:				CSC 525/625
MODIFIED BY:			N/A
LAST MODIFIED DATE:	Nov. 7, 2013
DESCRIPTION:		Demonstration of 2D transformations.
NOTES:				Use the right mouse button to activate the menu.
					Click and hold the left mouse button, then move the mouse
					left and right to adjust the value for that transformation.

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


// To allow file reading
#include <fstream>
using std::ifstream;

// To exit if the file doesn't exist
#include <cstdlib>

bool hasTyped = false;

enum Menu_Option {
	translate_x,
	translate_y,
	rotate_o,
	scale_x,
	scale_y,
	exit_program
};

Menu_Option selected_transformation = scale_y;


float transformation_scale = 1.0;
float cumulative_scale = 1.0;

void textMenu();
void menu_handler(int); // Menu handling function declaration
void saveContent();

void translateX();
void translateY();
void rotateDegrees();
void scaleX();
void scaleY();

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

const int window_size[2] = {600, 600};
int delta_x = 0;



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

void applySelectedTransformation(){
	switch (selected_transformation)
	{

	case translate_x:
		translateX();
		break;

	case translate_y:
		translateY();
		break;

	case rotate_o:
		rotateDegrees();
		break;

	case scale_x:
		scaleX();
		break;

	case scale_y:
		scaleY();
		break;
	}

}

void translateX(){
	for (int i = 0; i < sizeof poly; i++){
		poly[i][0] =poly[i][0] + transformation_scale;
	}
}

void translateY(){
	for (int i = 0; i < sizeof poly; i++){
		poly[i][1] =poly[i][1] + transformation_scale;
	}
}

void rotateDegrees(){
	float theta = cumulative_scale/180;
	for (int i = 0; i < sizeof poly; i++){
		poly[i][0] = orig_poly[i][0] * cos(theta) +  orig_poly[i][1] * sin(theta);
		poly[i][1] = -orig_poly[i][0] * sin(theta) +  orig_poly[i][1] * cos(theta);
	}
}

void scaleX(){
	float scale = cumulative_scale/window_size[0]*2;
	for (int i = 0; i < sizeof poly; i++){
		poly[i][0] = orig_poly[i][0] * scale;
	}
}

void scaleY(){
	float scale = cumulative_scale/window_size[0]*2;
	for (int i = 0; i < sizeof poly; i++){
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


void drawMenu() {
	// FIXME
	cout << "drawMenu" << endl;
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

	drawMenu();

	applySelectedTransformation();
	drawPolygon();

	glFlush(); // flush out the buffer contents
}

void mouseClick(int button, int state, int x, int y){


	myDisplayCallback();
}

void mouseMove(int x, int y){
	int window_x =  x -  (window_size[0]/2);

	cumulative_scale = cumulative_scale + window_x - delta_x; // for rotations and additive transformations
	transformation_scale =  window_x - delta_x; // for translations and moves
	delta_x = window_x ;

	myDisplayCallback();
	cout << "window_x : "<< window_x <<  ", cumulative_scale: "<< cumulative_scale <<", scale: "<< transformation_scale << endl;
}


//***********************************************************************************
void main(int argc, char ** argv) {
	glutInit(& argc, argv);

	glutInitWindowSize(window_size[0], window_size[1]);							// specify a window size
	glutInitWindowPosition(500, 50);							// specify a window position
	glutCreateWindow("2D Transformations");	// create a titled window
	mainInit();									// setting up
	glutDisplayFunc(myDisplayCallback);		// register a callback
	textMenu();

	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMove);

	glutMainLoop();							// get into an infinite loop

}
