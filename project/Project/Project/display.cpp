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
}

void display::render9() {

}

void display::render8() {

}

void display::render7() {

}

void display::render6() {

}

void display::render5() {

}

void display::render4() {

}

void display::render3() {

}

void display::render2() {

}

void display::render1() {

}

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