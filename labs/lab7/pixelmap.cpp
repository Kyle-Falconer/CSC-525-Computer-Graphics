/*===================================================================================
PROGRAMMER:				Yang Wang
COURSE:					CSC 525/625
MODIFIED BY:			Kyle Falconer
LAST MODIFIED DATE:		Sept. 23, 2013
DESCRIPTION:			Demo: pixel map rendering
NOTE:					N/A
FILES:					pixelmap.cpp, (labProject.sln, ...)
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


GLfloat*** pixels;



void drawPoints()
{

	glLineWidth(1);
	glPointSize(1);	

	glColor3f(1.0, 0.0, 0.0);
	
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glRasterPos2i(-256, 256);
	glDrawPixels(512, 512,   GL_RGB, GL_FLOAT,  (GLfloat*) (&pixels[0][0][0]) );   



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


bool parsePixelMapFile(string filename){

	ifstream input (filename);
	if(input.is_open()) {
		cout << "loading...\n";
		std::string line;
		GLfloat temp;

		
		pixels = new GLfloat**[512];
		

		for (int x = 0; x < 512; x++){ // rows
			pixels[x] = new GLfloat*[512];

			if (!std::getline (input, line)){
				cout << "error while reading file\n";
				break;
			}
			std::stringstream parse(line);
			
			for (int y = 0; y < 512; y+=3){ // columns
				pixels[x][y] = new GLfloat[3];
				//cout << "(";
				for (int c = 0; c < 3; c++){ // color: {r, g, b}
					parse >> temp;
					pixels[x][y][c] = temp;
					//cout << pixels[x][y][c] << " ";
				}	
				//cout << "), ";
			}
			//cout << endl;
		}

	} else {
		cout << "could not open file: " << filename << endl;
		return false;
	}
	return true;
}

void menuPrompt(){
	parsePixelMapFile("C:\\TEMP\\autumn.txt");
	/*
	string filename;
	cout << "Enter the name of the file to be read:";
	cin >> filename;
	while (!parsePixelMapFile(filename)) {
		cout << "Enter the name of the file to be read:";
		cin >> filename;
	}
	*/
}



//***********************************************************************************
void myInit()
{
	
	glClearColor(1, 1, 1, 0);			// specify a background clor: white 
	gluOrtho2D(-300, 300, -300, 300);  // specify a viewing area
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
	glutInit(& argc, argv);

	glutInitWindowSize(600, 600);				// specify a window size
	glutInitWindowPosition(100, 0);			// specify a window position
	glutCreateWindow("Simple Bitmap Drawing");	// create a titled window

	myInit();									// setting up

	glutDisplayFunc(myDisplayCallback);		// register a callback

	glutMainLoop();							// get into an infinite loop
}
