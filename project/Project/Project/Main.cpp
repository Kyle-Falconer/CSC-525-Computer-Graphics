/*===================================================================================
PROGRAMMER:			Brett Story,	Kyle Falconer
FOLDERS:				Brett322,		Falconer1

BRETT'S TASKS:			* Researching and getting a .obj file loader to work
						* Cleaning up 3D models in Blender.
						* Exporting models from Blender into seperate object and
						  color files to allow the models to work with the .obj
						  loader.
						* Camera and lighting positions for each scene.
						* Wrote half of the info messages.

KYLE'S TASKS:			* Sourcing 3D models from 3D Warehouse
						* Implementation of the Info window.
						* Implementation of the Finite State Machine.
						* Implementation of game logic.
						* Writing the transition messages and half of the info
						  messages.

COURSE:				CSC 525/625
LAST MODIFIED DATE:	Dec. 8, 2013
DESCRIPTION:			A Finite State Machine Game, used to demonstrate a FSM
						and also talk about the benefits of being a Computer
						Scientist.

NOTE:					Usage should be self-explanitory. Instructions are given
						in the info window the program runs.
						
					If using a .exe to run the program, make sure the scenes
					folder is in the same directory as the .exe

FILES:					Main.cpp, FSM.cpp, OBJLoader.cpp,
					display.cpp, project.sln, and headers.
IDE/COMPILER:			MicroSoft Visual Studio 2012
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Double click on project.sln	to OPEN the project
2.		Press Ctrl+F7					to COMPILE
3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
4.		Press Ctrl+F5					to EXECUTE
===================================================================================*/

#define _USE_MATH_DEFINES
#include <iostream>
#include <GL/glut.h>				// include GLUT library
#include <cmath>					// include math library
#include <string>
#include "states.h"
#include "display.h"

#define KEY_ESCAPE 27

int mainWindow;
int infoWindow;
int viewWindow;
int bottomWindow;
int mapWindow;


Model_OBJ obj[9];
FSM* statemachine;
display displayer;

void drawText(int win, float x, float y, float r, float g, float b, std::string text);

typedef struct {
	int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

glutWindow win;
glutWindow info;
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

void infoDisplay(){
	glutSetWindow(infoWindow);
	glClear(GL_COLOR_BUFFER_BIT);

	int start_x = -((info.width-20)/2);
	int start_y = ((info.height-40)/2);


	const std::string* lines = statemachine->getCurrentInfo();


	for (int i = 0; i < NUM_INFO_LINES; i++){
		drawText(infoWindow, start_x, start_y, 1.0, 1.0, 1.0,  lines[i]);
		start_x = start_x;
		start_y = start_y-20;
	}

	// TODO:
	// Add general usability info here to be displayed at each scene in the game
	// like, the controls and the meta keys.
	start_y = start_y - 60;
	drawText(infoWindow, start_x, start_y, 1.0, 1.0, 1.0,  "Options");
	start_y = start_y - 10;
	drawText(infoWindow, start_x, start_y, 1.0, 1.0, 1.0,  "=====================================");
	start_y = start_y - 20;
	drawText(infoWindow, start_x, start_y, 1.0, 1.0, 1.0,  "F5  - Restart game");
	start_y = start_y - 20;
	drawText(infoWindow, start_x, start_y, 1.0, 1.0, 1.0,  "Esc - Quit program");


	glPopMatrix();										  
	glutSwapBuffers();
}

void viewDisplay() 
{
	glutSetWindow(viewWindow);
	// Clear Screen and Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
	glLoadIdentity();

	switch (statemachine->getCurrentState())
	{
	case 0:
		displayer.render0();
		break;
	case 1:
		displayer.render1();
		break;
	case 2:
		displayer.render2();
		break;
	case 3:
		displayer.render3();
		break;
	case 4:
		displayer.render4();
		break;
	case 5:
		displayer.render5();
		break;
	case 6:
		displayer.render6();
		break;
	case 7:
		displayer.render7();
		break;
	case 8:
		displayer.render8();
		break;
	case 9:
		displayer.render9();
		break;
	default:
		break;
	}

	glPopMatrix();										  
	glutSwapBuffers();
}

void drawText(int win, float x, float y, float r, float g, float b, std::string text){
	glutSetWindow(win);
	glColor3f(r, g, b);
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
	drawText(bottomWindow, -bottom.width / 2 + 50, ( bottom.height / 2 )  -60, 1, 1, 1,  transitionLabels[0]);
	drawText(bottomWindow, -bottom.width / 2 + 70, ( bottom.height / 2 ) -100, 1, 1, 1,  transitionLabels[1]);
	drawText(bottomWindow, -bottom.width / 2 + 70, ( bottom.height / 2) - 140, 1, 1, 1,  transitionLabels[2]);

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
	infoDisplay();
	bottomDisplay();
	mapDisplay();
}

void initialize () 
{
	glMatrixMode(GL_PROJECTION);												
	glViewport(0, 0, view.width, view.height);									
	glMatrixMode(GL_PROJECTION);												
	glLoadIdentity();															
	GLfloat aspect = (GLfloat) view.width / (view.height);
	gluPerspective(view.field_of_view_angle, aspect, view.z_near, view.z_far);		
	glMatrixMode(GL_MODELVIEW);													
	glShadeModel( GL_SMOOTH );
	glClearDepth( 1.0f );														
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );						
	GLfloat amb_light[] = { 0.1, 0.1, 0.1, 0.5 };
	GLfloat diffuse[] = { 0.3, 0.3, 0.3, 1};
	GLfloat specular[] = { 0.1, 0.1, 0.1, 0.5};
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


void showInfoWindow(){
	// show info
	cout << "showing info window"<<endl;
	glutSetWindow(infoWindow);
	glutShowWindow();
	glClearColor(.5, .5, .5, 0);
	gluOrtho2D(-(info.width/2), (info.width/2), -(info.height/2), (info.height/2));
	glutSetWindow(mainWindow);	
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


void keyboard_special (int key, int x, int y)		
{ 
	switch ( key ) 
	{
	case GLUT_KEY_F5:
		statemachine->setCurrentState(1);
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
	glutSpecialFunc(keyboard_special);
	gluOrtho2D(-bottomMap.width / 2, bottomMap.width / 2, -bottomMap.height / 2, bottomMap.height / 2);  // specify a viewing area
}

void bottomInit() {
	// set window values
	bottom.width = 768;
	bottom.height = 192;

	bottomWindow = glutCreateSubWindow(mainWindow, 0, view.height, bottom.width, bottom.height);
	glutDisplayFunc(bottomDisplay);
	glutKeyboardFunc(keyboard);						// register Keyboard Handler
	glutSpecialFunc(keyboard_special);
	glClearColor(0, 0, 0, 1);			// specify a background
	gluOrtho2D(-bottom.width / 2, bottom.width / 2, -bottom.height / 2, bottom.height / 2);  // specify a viewing area
}

void viewInit() {
	// set window values
	view.width = 1024;
	view.height = 576;
	view.field_of_view_angle = 45;
	view.z_near = 0.1f;
	view.z_far = 500.0f;

	viewWindow = glutCreateSubWindow(mainWindow, 0, 0, view.width, view.height);		// create Window
	glutDisplayFunc(viewDisplay);							// register Display Function
	glutKeyboardFunc(keyboard);						// register Keyboard Handler
	glutSpecialFunc(keyboard_special);
	initialize();
}

void mainInit() {

	// set window values
	win.width = 1024;
	win.height = 768;
	win.title = "Finite State Machine Game";

	glutInitWindowSize(win.width, win.height);
	mainWindow = glutCreateWindow(win.title);
	glutDisplayFunc(mainDisplay);
	glutIdleFunc(displayCallback);					// register Idle Function
	glutKeyboardFunc(keyboard);						// register Keyboard Handler
	glutSpecialFunc(keyboard_special);
	glClearColor(0, 0, 0, 0);
}

void infoInit(){
	
	// set window values
	info.width = 360;
	info.height = win.height/2;
	info.title = "Info/Help";

	glutInitWindowSize(info.width, info.height);
	glutInitWindowPosition(win.width+20, 0);				
	infoWindow = glutCreateWindow(info.title);
	glutDisplayFunc(infoDisplay);
	glutIdleFunc(displayCallback);					// register Idle Function
	glutKeyboardFunc(keyboard);						// register Keyboard Handler
	glutSpecialFunc(keyboard_special);
	glClearColor(0, 0, 0, 0);
}



void main(int argc, char **argv) 
{
	
	// initialize and run program
	glutInit(&argc, argv);                                      // GLUT initialization
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);  // Display Mode

	
	mainInit();
	infoInit();
	showInfoWindow();
	viewInit();
	bottomInit();
	mapInit();
	statemachine = new FSM();

	glutMainLoop();												// run GLUT mainloop
}
