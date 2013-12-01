/*===================================================================================
PROGRAMMER:			Brett Story,	Kyle Falconer
FOLDERS:				Brett322,		Falconer1
BRETT'S TASKS:			FIXME
KYLE'S TASKS:			FIXME
COURSE:				CSC 525/625
LAST MODIFIED DATE:	Oct. 5, 2013
DESCRIPTION:			FIXME
NOTE:					FIXME

FILES:					Main.cpp, (Project.sln, ...)
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
#include "OBJLoader.h"
#include "states.h"

#define KEY_ESCAPE 27

int mainWindow;
int viewWindow;
int bottomWindow;
int mapWindow;

Model_OBJ obj;
FSM* statemachine;

typedef struct {
	int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

glutWindow win;
glutWindow view;
glutWindow bottom;
glutWindow bottomMap;

float g_rotation = 0;
float g_rotation_speed = 0.2f;

void drawWindowBox(glutWindow cur) {
	glLineWidth(4);
	glBegin(GL_LINE_STRIP);
		glColor3f(1, 1, 1);
		glVertex2f((cur.width / 2) - 8, (cur.height / 2) - 8);
		glVertex2f((cur.width / 2) - 8, -(cur.height / 2) + 8);
		glVertex2f(-(cur.width / 2) + 8, -(cur.height / 2) + 8);
		glVertex2f(-(cur.width / 2) + 8, (cur.height / 2) - 8);
		glVertex2f((cur.width / 2) - 8, (cur.height / 2) - 8);
	glEnd();
}

void mainDisplay() {
	glutSetWindow(mainWindow);
	glClear(GL_COLOR_BUFFER_BIT);
	glutSwapBuffers();
}

void viewDisplay() 
{
	glutSetWindow(viewWindow);
	// Clear Screen and Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     
	glLoadIdentity();

	// Define a viewing transformation
	gluLookAt( 4,2,0, 0,0,0, 0,1,0);					  

	// Push and pop the current matrix stack. 
	// This causes that translations and rotations on this matrix wont influence others.

	glPushMatrix();										
	glColor3f(1,0,0);
	glTranslatef(0,0,0);							
	glRotatef(g_rotation,0,1,0);
	glRotatef(90,0,1,0);

	// Draw the teapot
	//glutSolidTeapot(1);
	obj.Draw();
	glPopMatrix();										  

	/*
	NS_OBJLOADER::MESH coffee_cup_mesh;
	map<string, NS_OBJLOADER::MATERIAL> MyMaterials;
	if (LoadOBJFile ("Project\\Meshes\\coffee_cup.obj", coffee_cup_mesh, MyMaterials, "Project\\Textures\\"))
	{
		//
	}
	*/

	g_rotation += g_rotation_speed;
	glutSwapBuffers();
}

void drawText(int win, float x, float y, float r, float g, float b, float scale, std::string text){
	glutSetWindow(win);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2i(x,y);
	void * font = 	GLUT_BITMAP_9_BY_15;
	for (string::iterator i = text.begin(); i != text.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
}

void bottomDisplay() {
	glutSetWindow(bottomWindow);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawWindowBox(bottom);

	const std::string* transitionLabels = statemachine->getAvailableTransitionNames();
	drawText(bottomWindow, -bottom.width / 2 + 50, bottom.height / 2 - 70, 1, 1, 1, 2,  "1 - " + transitionLabels[0]);
	drawText(bottomWindow, -bottom.width / 2 + 50, -bottom.height / 2 + 70, 1, 1, 1, 2,  "2 - " + transitionLabels[1]);

	glutSwapBuffers();
}

void mapDisplay() {
	glutSetWindow(mapWindow);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLineWidth(4);
	
	drawWindowBox(bottomMap);

	glutSwapBuffers();
}

void displayCallback() {
	viewDisplay();
	bottomDisplay();
	mapDisplay();
}

void initialize () 
{
	// select projection matrix
	glMatrixMode(GL_PROJECTION);												

	// set the viewport
	glViewport(0, 0, view.width, view.height);									

	// set matrix mode
	glMatrixMode(GL_PROJECTION);												

	// reset projection matrix
	glLoadIdentity();															
	GLfloat aspect = (GLfloat) view.width / (view.height);

	// set up a perspective projection matrix
	gluPerspective(view.field_of_view_angle, aspect, view.z_near, view.z_far);		

	// specify which matrix is the current matrix
	glMatrixMode(GL_MODELVIEW);													
	glShadeModel( GL_SMOOTH );

	// specify the clear value for the depth buffer
	glClearDepth( 1.0f );														
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );

	// specify implementation-specific hints
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );						

	GLfloat amb_light[] = { 0.1, 0.1, 0.1, 1.0 };
	GLfloat diffuse[] = { 0.6, 0.6, 0.6, 1 };
	GLfloat specular[] = { 0.7, 0.7, 0.3, 1 };
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, amb_light );
	glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
	glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
	glEnable( GL_LIGHT0 );
	glEnable( GL_COLOR_MATERIAL );
	glShadeModel( GL_SMOOTH );
	glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
	glDepthFunc( GL_LEQUAL );
	glEnable( GL_DEPTH_TEST );
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); 
	glClearColor(1, 1, 1, 0);
}

void keyboard ( unsigned char key, int mousePositionX, int mousePositionY )		
{ 
	switch ( key ) 
	{
	case KEY_ESCAPE:    
		exit(0);   
		break;      

	case '1':
		statemachine->chooseFirstTransition();
		break;

	case '2':
		statemachine->chooseSecondTransition();
		break;

	default:      
		break;
	}
}
void mapInit() {
	bottomMap.width = 256;
	bottomMap.height = bottom.height;
	mapWindow = glutCreateSubWindow(mainWindow, bottom.width, view.height, bottomMap.width, bottomMap.height);
	glutDisplayFunc(mapDisplay);
	glClearColor(0, 0, 0, 1);
	glutKeyboardFunc(keyboard);						// register Keyboard Handler
	gluOrtho2D(-bottomMap.width / 2, bottomMap.width / 2, -bottomMap.height / 2, bottomMap.height / 2);  // specify a viewing area
}

void bottomInit() {
	// set window values
	bottom.width = 768;
	bottom.height = 192;

	bottomWindow = glutCreateSubWindow(mainWindow, 0, view.height, bottom.width, bottom.height);
	glutDisplayFunc(bottomDisplay);
	glutKeyboardFunc(keyboard);						// register Keyboard Handler
	glClearColor(0, 0, 0, 1);			// specify a background
	gluOrtho2D(-bottom.width / 2, bottom.width / 2, -bottom.height / 2, bottom.height / 2);  // specify a viewing area
}

void viewInit() {
	// set window values
	view.width = 1024;
	view.height = 576;
	view.field_of_view_angle = 45;
	view.z_near = 1.0f;
	view.z_far = 500.0f;

	viewWindow = glutCreateSubWindow(mainWindow, 0, 0, view.width, view.height);		// create Window
	glutDisplayFunc(viewDisplay);							// register Display Function
	glutKeyboardFunc(keyboard);						// register Keyboard Handler
	initialize();
}

void mainInit() {
	// set window values
	win.width = 1024;
	win.height = 768;
	win.title = "Finite State Machine Game (working title)";

	glutInitWindowSize(win.width, win.height);
	mainWindow = glutCreateWindow(win.title);
	glutDisplayFunc(mainDisplay);
	glutIdleFunc(displayCallback);					// register Idle Function
	glutKeyboardFunc(keyboard);						// register Keyboard Handler
	glClearColor(0, 0, 0, 0);
}



void main(int argc, char **argv) 
{
	// initialize and run program
	glutInit(&argc, argv);                                      // GLUT initialization
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // Display Mode
	mainInit();
	viewInit();
	bottomInit();
	mapInit();
	statemachine = new FSM();
	obj.Load("meshes/untitled");
	glutMainLoop();												// run GLUT mainloop
}