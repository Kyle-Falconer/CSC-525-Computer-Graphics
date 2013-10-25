#ifndef TEXTMENU_H
#define TEXTMENU_H

#include "glut.h"
#include "glChar.h"

enum Menu_Option {
	save_content,
	glut_red,
	glut_green,
	glut_8_BY_13,
	glut_9_BY_15, 
	glut_TIMES_ROMAN_10,
	glut_TIMES_ROMAN_24,
	glut_HELVETICA_10,
	glut_HELVETICA_12,
	glut_HELVETICA_18,
	exit_program
};





void textMenu();
void menu_handler(int); // Menu handling function declaration

#endif