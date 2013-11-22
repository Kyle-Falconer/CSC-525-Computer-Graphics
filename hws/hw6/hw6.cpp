/*===================================================================================
PROGRAMMER:			Brett Story,	Kyle Falconer
FOLDERS:				Brett322,		Falconer1
BRETT'S TASKS:			FIXME
KYLE'S TASKS:			FIXME
COURSE:				CSC 525/625
LAST MODIFIED DATE:	Nov. 21 2013
DESCRIPTION:			FIXME
NOTE:					FIXME

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


const int teapotCount = 100;
float teapot_pos[teapotCount][3];
float teapot_color[teapotCount][3];
float teapot_rot[teapotCount][4];
float teapot_scale[teapotCount];
void setTeapotValues(){
	srand ( time(NULL) );
	for (int i = 0; i < teapotCount; i++){
		int posNeg = teapotCount/2 > 1 ? -1 : 1;
		teapot_pos[i][0] = rand() % 10 + 1 ;
		teapot_pos[i][1] = rand() % 10 + 1;
		teapot_pos[i][2] = rand() % 10 + 1;

		teapot_rot[i][0] = rand() % 360 + 1;
		teapot_rot[i][1] = rand() % 10 + 1;
		teapot_rot[i][2] = rand() % 10 + 1;
		teapot_rot[i][3] = rand() % 10 + 1;

		teapot_color[i][0] = posNeg * ((float) rand() / (RAND_MAX)) + 1;
		teapot_color[i][1] = posNeg * ((float) rand() / (RAND_MAX)) + 1;
		teapot_color[i][2] = posNeg * ((float) rand() / (RAND_MAX)) + 1;

		teapot_scale[i] = posNeg * ((float) rand() / (RAND_MAX)) + 1;
	}
	cout << "done making the teapot values"<<endl;
}

void display() 
{
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


void keyboard ( unsigned char key, int mousePositionX, int mousePositionY )		
{ 
	switch (key) 
	{
	case KEY_ESCAPE:        
		exit ( 0 );   
		break;      

	default:      
		break;
	}
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
	default:      
		break;
	}
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
	glutInit(&argc, argv);                                      // GLUT initialization
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );  // Display Mode
	glutInitWindowSize(win.width,win.height);				// set window size
	glutCreateWindow(win.title);					// create Window
	glutDisplayFunc(display);						// register Display Function
	glutIdleFunc(display);						// register Idle Function
	glutKeyboardFunc(keyboard);						// register Keyboard Handler
	glutSpecialFunc(keyboardMovement);
	initialize();
	glutMainLoop();							// run GLUT mainloop
	return 0;
}