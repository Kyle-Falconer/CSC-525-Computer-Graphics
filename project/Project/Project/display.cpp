#include "display.h"

display::display() {
	initRenders();
}

void display::initRenders() {
	sceneObjects[0][0].Load("scenes/0home/couch");
	sceneObjects[0][1].Load("scenes/0home/floor");
	sceneObjects[0][2].Load("scenes/0home/walls");
	sceneObjects[0][3].Load("scenes/0home/ceiling");
	sceneObjects[0][4].Load("scenes/0home/trim");
	sceneObjects[0][5].Load("scenes/0home/tv01");
	sceneObjects[0][6].Load("scenes/0home/tv02");
	sceneObjects[0][7].Load("scenes/0home/tv03");
	sceneObjects[0][8].Load("scenes/0home/tvstand");

	sceneObjects[1][0].Load("scenes/4window/leaves");
	sceneObjects[1][1].Load("scenes/4window/exterior");
	sceneObjects[1][2].Load("scenes/4window/trees");
	sceneObjects[1][3].Load("scenes/4window/windows");
	sceneObjects[1][4].Load("scenes/4window/lamppost");
	sceneObjects[1][5].Load("scenes/4window/ground");

	sceneObjects[7][0].Load("scenes/7stairs/stairs");
	sceneObjects[7][1].Load("scenes/7stairs/floors");
	sceneObjects[7][2].Load("scenes/7stairs/railings");
	sceneObjects[7][3].Load("scenes/7stairs/walls");
}

//Desk
void display::render9() {

}

//Third floor
void display::render8() {

}

// Stairs
void display::render7() {
	// Define a viewing transformation
	gluLookAt(1,3,0.5, -3,0,0, 0,1,0);	

	// Push and pop the current matrix stack. 
	// This causes that translations and rotations on this matrix wont influence others.

	glPushMatrix();										
	glTranslatef(0,0,0);							
	glScalef(0.25, 0.25, 0.25);

	sceneObjects[7][0].Draw();
	sceneObjects[7][1].Draw();
	sceneObjects[7][2].Draw();
	sceneObjects[7][3].Draw();
}

// Food Court
void display::render6() {

}

// Second floor
void display::render5() {

}

// Window
void display::render4() {
	glClearColor(0.2, 0.4, 0.8, 1);			// specify a background
	// Define a viewing transformation
	gluLookAt(2,1,0, 0,-2 ,0, 0,1,0);

	// Push and pop the current matrix stack. 
	// This causes that translations and rotations on this matrix wont influence others.

	glPushMatrix();										
	glTranslatef(0,0,0);
	glScalef(0.25, 0.25, 0.25);

	sceneObjects[1][0].Draw();
	sceneObjects[1][1].Draw();
	sceneObjects[1][2].Draw();
	sceneObjects[1][3].Draw();
	sceneObjects[1][4].Draw();
	sceneObjects[1][5].Draw();
}

// Human resources
void display::render3() {

}

// Secretary
void display::render2() {

}

// Doors
void display::render1() {
	glClearColor(0.2, 0.4, 0.8, 1);			// specify a background
	// Define a viewing transformation
	gluLookAt(.5,0.25,1.5, 2,0,1, 0,1,0);	

	// Push and pop the current matrix stack. 
	// This causes that translations and rotations on this matrix wont influence others.

	glPushMatrix();										
	glTranslatef(0,0,0);
	glScalef(0.25, 0.25, 0.25);

	sceneObjects[1][0].Draw();
	sceneObjects[1][1].Draw();
	sceneObjects[1][2].Draw();
	sceneObjects[1][3].Draw();
	sceneObjects[1][4].Draw();
	sceneObjects[1][5].Draw();
}

// Home
void display::render0() {
	// Define a viewing transformation
	gluLookAt(4,3,0, 0,2,0, 0,1,0);	

	// Push and pop the current matrix stack. 
	// This causes that translations and rotations on this matrix wont influence others.

	glPushMatrix();										
	glTranslatef(0,0,0);							
	glScalef(0.25, 0.25, 0.25);

	sceneObjects[0][0].Draw();
	sceneObjects[0][1].Draw();
	sceneObjects[0][2].Draw();
	sceneObjects[0][3].Draw();
	sceneObjects[0][4].Draw();
	sceneObjects[0][5].Draw();
	sceneObjects[0][6].Draw();
	sceneObjects[0][7].Draw();
	sceneObjects[0][8].Draw();
}