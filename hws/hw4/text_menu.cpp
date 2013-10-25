#include "text_menu.h"


void textMenu(){

	glClearColor(.5, .5, .5, 0);			// specify a background clor: blueish-green
	gluOrtho2D(-400, 400, -19, 0);  // specify a viewing area

	int menu_main, submenu_colors, submenu_fonts;

	submenu_colors =  glutCreateMenu(menu_handler);
	glutAddMenuEntry("Red", glut_red);
	glutAddMenuEntry("Green", glut_green);

	submenu_fonts =  glutCreateMenu(menu_handler);
	glutAddMenuEntry("GLUT_BITMAP_8_BY_13", glut_8_BY_13);
	glutAddMenuEntry("GLUT_BITMAP_9_BY_15", glut_9_BY_15);
	glutAddMenuEntry("GLUT_BITMAP_TIMES_ROMAN_10", glut_TIMES_ROMAN_10);
	glutAddMenuEntry("GLUT_BITMAP_TIMES_ROMAN_24", glut_TIMES_ROMAN_24);
	glutAddMenuEntry("GLUT_BITMAP_HELVETICA_10", glut_HELVETICA_10);
	glutAddMenuEntry("GLUT_BITMAP_HELVETICA_12", glut_HELVETICA_12);
	glutAddMenuEntry("GLUT_BITMAP_HELVETICA_18", glut_HELVETICA_18);

	menu_main = glutCreateMenu(menu_handler);
	glutAddSubMenu("Save", save_content);
	glutAddSubMenu("Colors", submenu_colors);
	glutAddSubMenu("Fonts", submenu_fonts);
	glutAddMenuEntry("EXIT", exit_program);

	// Associate a mouse button with menu
	glutAttachMenu(GLUT_LEFT_BUTTON);

}

// Menu handling function definition
void menu_handler(int item)
{
	switch (item)
	{

	case save_content:
		{
			saveCallback();
		}
	case glut_red:
		{
			selected_text_color[0] = 1.0;
			selected_text_color[1] = 0.0;
			selected_text_color[2] = 0.0;
		}
		break;
	case glut_green:
		{
			selected_text_color[0] = 0.0;
			selected_text_color[1] = 1.0;
			selected_text_color[2] = 0.0;
		}
		break;
	case glut_8_BY_13:
		{
			selected_font = GLUT_BITMAP_8_BY_13;
		}
		break;
	case glut_9_BY_15:
		{
			selected_font = GLUT_BITMAP_9_BY_15;
		}
		break;
	case glut_TIMES_ROMAN_10:
		{
			selected_font = GLUT_BITMAP_TIMES_ROMAN_10;
		}
		break;
	case glut_TIMES_ROMAN_24:

		{
			selected_font = GLUT_BITMAP_TIMES_ROMAN_24;
		}
		break;

	case glut_HELVETICA_10:
		{
			selected_font = GLUT_BITMAP_HELVETICA_10;
		}
		break;
	case glut_HELVETICA_12:
		{
			selected_font = GLUT_BITMAP_HELVETICA_12;
		}
		break;

	case glut_HELVETICA_18:
		{
			selected_font = GLUT_BITMAP_HELVETICA_18;
		}
		break;

	case exit_program:
		{
			exit(0);
		}
		break;
	default:
		{
			selected_font =  GLUT_BITMAP_8_BY_13;
		}
		break;
	}

	glutPostRedisplay();
	cout << "color: " << selected_text_color[0] << " "<< selected_text_color[1] << " "<< selected_text_color[2] << endl;
			
	return;
}

