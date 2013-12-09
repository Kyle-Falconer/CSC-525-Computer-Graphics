/*
  Copyright 2013 Brett Story and Kyle Falconer

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "display.h"

display::display() {
	initRenders();
}

void display::initRenders() {
	cout << "loading scenes..."<<endl;
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

	sceneObjects[2][0].Load("scenes/2secretary/brown");
	sceneObjects[2][1].Load("scenes/2secretary/black");
	sceneObjects[2][2].Load("scenes/2secretary/grey");
	sceneObjects[2][3].Load("scenes/2secretary/floor");
	sceneObjects[2][4].Load("scenes/2secretary/walls");

	sceneObjects[3][0].Load("scenes/3humanresources/blue");
	sceneObjects[3][1].Load("scenes/3humanresources/black");
	sceneObjects[3][2].Load("scenes/3humanresources/grey");
	sceneObjects[3][3].Load("scenes/3humanresources/walls");

	sceneObjects[5][0].Load("scenes/5secondfloor/brown");
	sceneObjects[5][1].Load("scenes/5secondfloor/green");
	sceneObjects[5][2].Load("scenes/5secondfloor/grey");
	sceneObjects[5][3].Load("scenes/5secondfloor/yellow");

	sceneObjects[6][0].Load("scenes/6foodcourt/brown");
	sceneObjects[6][1].Load("scenes/6foodcourt/black");
	sceneObjects[6][2].Load("scenes/6foodcourt/grey");
	sceneObjects[6][3].Load("scenes/6foodcourt/red");
	sceneObjects[6][4].Load("scenes/6foodcourt/white");

	sceneObjects[7][0].Load("scenes/7stairs/stairs");
	sceneObjects[7][1].Load("scenes/7stairs/floors");
	sceneObjects[7][2].Load("scenes/7stairs/railings");
	sceneObjects[7][3].Load("scenes/7stairs/walls");

	sceneObjects[8][0].Load("scenes/8thirdfloor/black");
	sceneObjects[8][1].Load("scenes/8thirdfloor/brown");
	sceneObjects[8][2].Load("scenes/8thirdfloor/floor");
	sceneObjects[8][3].Load("scenes/8thirdfloor/white");

	sceneObjects[9][0].Load("scenes/9desk/black");
	sceneObjects[9][1].Load("scenes/9desk/blue");
	sceneObjects[9][2].Load("scenes/9desk/brown");
	sceneObjects[9][3].Load("scenes/9desk/grey");
	sceneObjects[9][4].Load("scenes/9desk/white");
}

//Desk
void display::render9() {
	gluLookAt(2.5,2,-2, 0,1.5,0, 0,1,0);	

	glPushMatrix();										
	glTranslatef(0,0,0);							
	glScalef(0.25, 0.25, 0.25);

	sceneObjects[9][0].Draw();
	sceneObjects[9][1].Draw();
	sceneObjects[9][2].Draw();
	sceneObjects[9][3].Draw();
	sceneObjects[9][4].Draw();
}

//Third floor
void display::render8() {
	gluLookAt(2.3,1.0,-0.2, 0,0,0, 0,1,0);	

	glPushMatrix();										
	glTranslatef(0,0,0);							
	glScalef(0.25, 0.25, 0.25);

	sceneObjects[8][0].Draw();
	sceneObjects[8][1].Draw();
	sceneObjects[8][2].Draw();
	sceneObjects[8][3].Draw();
}

// Stairs
void display::render7() {
	gluLookAt(1,3,0.5, -3,0,0, 0,1,0);	

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
	gluLookAt(3,1,-1, 0,.5,-0.5, 0,1,0);	
	glPushMatrix();										
	glTranslatef(0,0,0);
	glScalef(0.25, 0.25, 0.25);

	sceneObjects[6][0].Draw();
	sceneObjects[6][1].Draw();
	sceneObjects[6][2].Draw();
	sceneObjects[6][3].Draw();
	sceneObjects[6][4].Draw();
}

// Second floor
void display::render5() {
	gluLookAt(4,5,-2, 0,4,-1, 0,1,0);	
	glPushMatrix();										
	glTranslatef(0,0,0);
	glScalef(0.25, 0.25, 0.25);

	sceneObjects[5][0].Draw();
	sceneObjects[5][1].Draw();
	sceneObjects[5][2].Draw();
	sceneObjects[5][3].Draw();
}

// Window
void display::render4() {
	glClearColor(0.2, 0.4, 0.8, 1);	
	gluLookAt(2,1,0, 1,1.5,2, 0,1,0);

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
	gluLookAt(1,1.25,1, 0,1.1,.5, 0,1,0);	
	glPushMatrix();										
	glTranslatef(0,0,0);
	glScalef(0.25, 0.25, 0.25);

	sceneObjects[3][0].Draw();
	sceneObjects[3][1].Draw();
	sceneObjects[3][2].Draw();
	sceneObjects[3][3].Draw();
}

// Secretary
void display::render2() {
	gluLookAt(-1.5,1.1,-1, -1,.5,1, 0,1,0);	
	glPushMatrix();										
	glTranslatef(0,0,0);
	glScalef(0.25, 0.25, 0.25);

	sceneObjects[2][0].Draw();
	sceneObjects[2][1].Draw();
	sceneObjects[2][2].Draw();
	sceneObjects[2][3].Draw();
	sceneObjects[2][4].Draw();
}

// Doors
void display::render1() {
	glClearColor(0.2, 0.4, 0.8, 1);	
	gluLookAt(.5,0.25,1.5, 2,0,1, 0,1,0);	

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
	gluLookAt(4,3,0, 0,2,0, 0,1,0);	

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