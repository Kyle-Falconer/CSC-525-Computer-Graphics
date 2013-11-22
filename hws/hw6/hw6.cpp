/*===================================================================================
PROGRAMMER:			Brett Story,	Kyle Falconer
FOLDERS:				Brett322,		Falconer1
BRETT'S TASKS:			Creation of 3D world and camera/perspective controls
KYLE'S TASKS:			Creation and placement of teapots
COURSE:				CSC 525/625
LAST MODIFIED DATE:	Nov. 21 2013
DESCRIPTION:			A demonstration of camera controls and object placement

FILES:					hw6.cpp, (hwProject.sln, ...)
IDE/COMPILER:			MicroSoft Visual Studio 2012
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Double click on hwProject.sln	to OPEN the project
2.		Press Ctrl+F7					to COMPILE
3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
4.		Press Ctrl+F5					to EXECUTE
===================================================================================*/
#define _USE_MATH_DEFINES
#include <iostream>
#include <GL/glut.h>				// include GLUT library
#include <cmath>					// include math library
#include <string>
#include <time.h>
using namespace std;

#define KEY_ESCAPE 27
#define PI 3.141592653589793 

const int teapotCount = 100;
float teapot_pos[teapotCount][3];
float teapot_color[teapotCount][3];
float teapot_rot[teapotCount][4];
float teapot_scale[teapotCount];

int infoWindow, teapotWindow;


typedef struct {
	int width;
	int height;
	char* title;

	float field_of_view_angle;
	float z_near;
	float z_far;
} glutWindow;

glutWindow win;

float rotAngle = 0;

typedef struct {
	float radius;
	float height;
	float rotation[3];
} cameraPos;

cameraPos cam;

float g_rotation = 0;
float g_rotation_speed = 0.2f;

void rotateLeft() {
	rotAngle -= (30 * PI / 180);
	if (rotAngle <= -180)
		rotAngle += 180;
}


void rotateRight() {
	rotAngle += (30 * PI / 180);
	if (rotAngle >= 180)
		rotAngle -= 180;
}

float random(float min, float max){
	if (max == 1 && min == 0){
		return ((double) rand() / (RAND_MAX));
	}
	return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}

void setTeapotValues(){
	int min = -10;
	int max = 10;
	srand ( time(NULL) );
	for (int i = 0; i < teapotCount; i++){
		teapot_pos[i][0] = random(min, max);
		teapot_pos[i][1] = random(min, max);
		teapot_pos[i][2] = random(min, max);

		teapot_rot[i][0] = random(0, 360);
		teapot_rot[i][1] = random(min, max);
		teapot_rot[i][2] = random(min, max);
		teapot_rot[i][3] = random(min, max);

		teapot_color[i][0] = random(0, 1);
		teapot_color[i][1] = random(0, 1);
		teapot_color[i][2] = random(0, 1);

		teapot_scale[i] = random(0, 1);
	}

	cout << "done making the teapot values"<<endl;
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


void drawInfo() {
	drawText(infoWindow, -190, 260, 1.0, 0.0, 0.0,  "Right-click anywhere and choose an option.");
	drawText(infoWindow, -190, 240, 1.0, 0.0, 0.0,  "                   -or-                   ");
	drawText(infoWindow, -190, 220, 1.0, 0.0, 0.0,  "Press one of the following keys:");

	drawText(infoWindow, -190, 200, 1.0, 0.0, 0.0,  "[left arrow] : rotate camera left");
	drawText(infoWindow, -190, 180, 1.0, 0.0, 0.0,  "[right arrow] : rotate camera right");
	drawText(infoWindow, -190, 160, 1.0, 0.0, 0.0,  "[up arrow] : zoom camera in");
	drawText(infoWindow, -190, 140, 1.0, 0.0, 0.0,  "[down arrow] : zoom camera out");
	drawText(infoWindow, -190, 120, 1.0, 0.0, 0.0,  "[PgUp] : rotate camera up");
	drawText(infoWindow, -190, 100, 1.0, 0.0, 0.0,  "[PgDn] : rotate camera down");
	drawText(infoWindow, -190, 80, 1.0, 0.0, 0.0,  "[Esc] : Exit program");
}

void display() 
{
	drawInfo(); // FIXME 

	glutSetWindow(teapotWindow);
	// Clear Screen and Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		     
	glLoadIdentity();

	cam.rotation[0] = sin(rotAngle);
	cam.rotation[2] = cos(rotAngle);

	// Define a viewing transformation
	gluLookAt( cam.radius * cam.rotation[0],cam.height,cam.radius*cam.rotation[2], 0,0,0, 0,1,0);					  


	// Push and pop the current matrix stack. 
	// This causes that translations and rotations on this matrix wont influence others.

	glPushMatrix();	

	// teapot #1
	glColor3f(1,0,0);
	glRotatef(90,0,1,0);	
	glutSolidTeapot(1);


	for (int i = 0; i < teapotCount; i++){
		glTranslatef(teapot_pos[i][0], teapot_pos[i][1], teapot_pos[i][2]);
		glRotatef(teapot_rot[i][0], teapot_rot[i][1], teapot_rot[i][2], teapot_rot[i][3]);
		glColor3f(teapot_color[i][0], teapot_color[i][1], teapot_color[i][2]);
		glutSolidTeapot(teapot_scale[i]);
	}


	glPopMatrix();										  

	g_rotation += g_rotation_speed;
	glutSwapBuffers();
}


void initialize () 
{
	// select projection matrix
	glMatrixMode(GL_PROJECTION);												

	// set the viewport
	glViewport(0, 0, win.width, win.height);									

	// set matrix mode
	glMatrixMode(GL_PROJECTION);												

	// reset projection matrix
	glLoadIdentity();															
	GLfloat aspect = (GLfloat) win.width / win.height;

	// set up a perspective projection matrix
	gluPerspective(win.field_of_view_angle, aspect, win.z_near, win.z_far);		

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
	glClearColor(0.0, 0.0, 0.0, 1.0);
}


void keyboardMovement (int key, int x, int y) {
	switch (key) 
	{
	case GLUT_KEY_LEFT:   
		rotateLeft();
		break;      
	case GLUT_KEY_RIGHT:  
		rotateRight();
		break;      
	case GLUT_KEY_UP:
		if (cam.radius > 1)
			cam.radius -= 1;
		break;      
	case GLUT_KEY_DOWN:        
		cam.radius += 1;
		glutSwapBuffers();
		break;      
	case GLUT_KEY_PAGE_UP:
		cam.height += 1;
		break;
	case GLUT_KEY_PAGE_DOWN:
		cam.height -= 1;
		break;
	case 27:
		exit ( 0 );   
		break;
	default:      
		break;
	}
}

void menuListener(int value)
{
	keyboardMovement((unsigned char)value, 0, 0);
}

void menuInit(){
	glutCreateMenu(menuListener);
	glutAddMenuEntry("Rotate left [left arrow]", GLUT_KEY_LEFT);
	glutAddMenuEntry("Rotate right [right arrow]", GLUT_KEY_RIGHT);
	glutAddMenuEntry("Zoom in [up arrow]", GLUT_KEY_UP);
	glutAddMenuEntry("Zoom out [down arrow]", GLUT_KEY_DOWN);
	glutAddMenuEntry("Rotate up [PgUp]", GLUT_KEY_PAGE_UP);
	glutAddMenuEntry("Rotdate down [PgDn]", GLUT_KEY_PAGE_DOWN);
	glutAddMenuEntry("Exit [Esc]", 27);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void infoInit() {
	glClearColor(.40, .40, .40, 0);			// specify a background
	gluOrtho2D(-200, 200, -300, 300);  // specify a viewing area
}

int main(int argc, char **argv) 
{
	// set window values
	win.width = 640;
	win.height = 480;
	win.title = "Homework 6";
	win.field_of_view_angle = 45;
	win.z_near = 1.0f;
	win.z_far = 500.0f;

	cam.radius = 4;
	cam.height = 0;

	cam.rotation[0] = 1;
	cam.rotation[1] = 0;
	cam.rotation[2] = 0;

	setTeapotValues();

	// initialize and run program
	glutInit(&argc, argv);          // GLUT initialization

	/*	THIS CRASHES THE PROGRAM - also see line 136 */
	glutInitWindowSize(384, 576);							// specify a window size
	glutInitWindowPosition(50, 50);							// specify a window position
	infoWindow = glutCreateWindow("Info/Help");
	infoInit();

				
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // Display Mode
	glutInitWindowSize(win.width,win.height);				// set window size
	teapotWindow = glutCreateWindow(win.title);					// create Window
	glutDisplayFunc(display);						// register Display Function
	glutIdleFunc(display);						// register Idle Function
	glutSpecialFunc(keyboardMovement);
	initialize();
	menuInit();
	glutMainLoop();							// run GLUT mainloop

	return 0;
}