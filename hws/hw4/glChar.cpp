#include "glChar.h"
#include "EditorProperties.h"

void glChar::setValues(const char curChar, float curRed, float curGreen, float curBlue, void *curFont) {
	this->character = curChar;
	this->red = curRed;
	this->green = curGreen;
	this->blue = curBlue;
	this->font = curFont;
}

void glChar::display() {
	GLfloat pos[4];
	glGetFloatv(GL_CURRENT_RASTER_POSITION, pos);

	// 1.28 is the scale from world to window
	float xPosition = pos[0]/1.28 - 300;
	float yPosition = pos[1]/1.28 - 300;

	glColor3f(selected_text_color[0], selected_text_color[1], selected_text_color[2]);

	if (this->character == '\n' || xPosition > xRowPosition - 5)
	{
		glRasterPos2f(-xRowPosition, yPosition - rowHeight);
	}
	else if (pos[1] <= 268 - 29*rowHeight)
	{
		return;
	}
	else
	{
		glRasterPos2f(xPosition, yPosition); //must declare rasterPos to change color
	}

	glutBitmapCharacter(selected_font, this->character);
}

