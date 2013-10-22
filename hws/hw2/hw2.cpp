/*===================================================================================
PROGRAMMER:			Kyle Falconer
ECCENTRIC FOLDER:	falconer1
COURSE:				CSC 525/625
ASSIGNMENT:			Homework 2
LAST MODIFIED DATE:	Sept. 22, 2013
DESCRIPTION:			Demonstration of the scan-line algorithm.
NOTE:					N/A
FILES:					hw2.cpp, (hwProject.sln, ...)
IDE/COMPILER:			Microsoft Visual Studio 2012
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Double click on hwProject.sln	to OPEN the project
2.		Press Ctrl+F7					to COMPILE
3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
4.		Press Ctrl+F5					to EXECUTE
===================================================================================*/

#include "hw2.h"

int vertexCount = 0;
float** vertices;
float** vert_colors;
std::map<int, std::vector<int>> edge_table;


void fillPolygon(){

	edge_table = map<int, std::vector<int>>();
	map<int, std::vector<int>>::iterator edge_iterator;

	float tempVertex[2] = { vertices[0][0], vertices[0][1] };

	for (int i = 1; i < vertexCount+1; i++){
		int temp_i = i;
		if (i == vertexCount)
			temp_i = 0;

		glColor3f(vert_colors[temp_i][0], vert_colors[temp_i][1], vert_colors[temp_i][2]);

		lineCoords(
			tempVertex[0],			// x1
			tempVertex[1],			// y1
			vertices[temp_i][0],	//x2
			vertices[temp_i][1]);	//y2

		tempVertex[0] = vertices[temp_i][0];
		tempVertex[1] = vertices[temp_i][1];
	}

#if DEBUG > 0
	cout << "coordinates:\n";
	for (edge_iterator = edge_table.begin(); edge_iterator != edge_table.end(); ++edge_iterator) {

		int y_coord = edge_iterator->first;
		std::vector<int> pairs = edge_iterator->second;
		cout << y_coord << " -> ";
		for (unsigned i = 0; i < pairs.size(); i++){
			cout << pairs[i];
			if (i != pairs.size()-1){
				cout << ", ";
			}
		}	
		cout << endl;
	}
#endif

	for (edge_iterator = edge_table.begin(); edge_iterator != edge_table.end(); ++edge_iterator) {
		int y_coord = edge_iterator->first;
		std::vector<int> pairs = edge_iterator->second;
		glLineWidth(1);
		glBegin(GL_LINES);

		std::sort (pairs.begin(), pairs.end(), intCompare);
		// draw a line on even parity
		for (unsigned i = 1; i < pairs.size(); i+=2){
			glVertex2i(pairs[i-1], y_coord);
			glVertex2i(pairs[i], y_coord);
		}
		glEnd();
	}

}


void drawAxes(int x_min, int y_min){
	// X-Y axis
	glPointSize(1);		// change point size back to 1
	glBegin(GL_POINTS);	// use points to form X-/Y-axes
	glColor3f(0, 0, 0);
	for (int x=-x_min; x<=x_min; x++) // draw X-axis
		glVertex2i(x, 0);
	for (int y=-y_min; y<=y_min; y++) // draw Y-axis
		glVertex2i(0, y);
	glEnd();

	void * font = GLUT_BITMAP_8_BY_13;
	glRasterPos2i(x_min, -10);
	glutBitmapCharacter(font, 'x');
	glRasterPos2i(-10, y_min);
	glutBitmapCharacter(font, 'y');
}


float slope(float x1, float y1, float x2, float y2){
	float dx = (x2 - x1);
	float dy = (y2 - y1);
	return (dx == 0) ? 1 : dy / dx;
}


void lineCoords(float x1, float y1, float x2, float y2){
	lineCoords(
		pseudoRoundf(x1),
		pseudoRoundf(y1),
		pseudoRoundf(x2),
		pseudoRoundf(y2));
}


void lineCoords(int x1, int y1, int x2, int y2){

	glPointSize(1);	
	glBegin(GL_POINTS);

	if ((x1 == x2) && (y1 == y2)){
		// single point
		glVertex2i(x1, y1);

	}  else if (x2 == x1){
		// vertical line
		if (y2 < y1){
			int temp = x1;
			x1 = x2;
			x2 = temp;
			temp = y1;
			y1 = y2;
			y2 = temp;
		}

		for (int y = y1; y < y2; y++){
			glVertex2i(x1, y);
			addEdgePair(x1, y);
		}

	} else {
		// diagonal line
		float m =  slope(x1, y1, x2, y2);

		// b = y - mx
		float y_intercept  = y1 - (m*x1);

		if (m <= 1 && m >= 0){
			if (x2 < x1){
				int temp = x1;
				x1 = x2;
				x2 = temp;
				temp = y1;
				y1 = y2;
				y2 = temp;
			}

			for (int x = x1; x < x2; x++){
				// y = mx+b
				int y = (m*x) + y_intercept;
				glVertex2i(x, y);
				if (m != 0)
					addEdgePair(x, y);
			}

		} else {
			if (y2 < y1){
				int temp = x1;
				x1 = x2;
				x2 = temp;
				temp = y1;
				y1 = y2;
				y2 = temp;
			}

			for (int y = y1; y < y2; y++){
				// x = (y-b)/m 
				int x = (y - y_intercept )/m;
				glVertex2i(x, y);
				addEdgePair(x, y);
			}
		}
	}
	glEnd();
}


int pseudoRoundf(float value){
	return floor(value + 0.5);
}

bool intCompare (int i,int j) {
	return (i<j);
}

void addEdgePair(int x, int y){
	map<int, std::vector<int>>::iterator edge_iterator = edge_table.find(y);
	std::vector<int> xy_pair;
	if(edge_iterator != edge_table.end()){
		//element found;
		edge_table[y].push_back(x);

	} else {
		// element not found
		xy_pair = std::vector<int>();
		xy_pair.push_back(x);
		edge_table.insert(std::pair<int, vector<int>>(y, xy_pair));
	}
}

bool parsePolygonFile(string filename){

	ifstream input (filename);
	if(input.is_open()) {
		std::string line;
		float temp;

		std::getline (input, line);
		std::stringstream parse(line);
		parse >> vertexCount;

		vertices = new float*[vertexCount];
		vert_colors = new float*[vertexCount];

		int v_index = 0;

		while (std::getline (input, line)) {
			std::stringstream parse(line);

			// coordinates
			vertices[v_index] = new float[2];
			parse >> temp;
			vertices[v_index][0] = temp;
			parse >> temp;
			vertices[v_index][1] = temp;

			// colors
			vert_colors[v_index] = new float[3];
			parse >> temp;
			vert_colors[v_index][0] = temp;
			parse >> temp;
			vert_colors[v_index][1] = temp;
			parse >> temp;
			vert_colors[v_index][2] = temp;
			v_index++;
		}
	} else {
		cout << "could not open file: " << filename << endl;
		return false;
	}
	return true;
}


void menuPrompt(){

#ifdef testFile
	parsePolygonFile(testFile);
#else
	string filename;
	cout << "Enter the name of the file to be read:";
	cin >> filename;
	while (!parsePolygonFile(filename)) {
		cout << "Enter the name of the file to be read:";
		cin >> filename;
	}
#endif
}


void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background

	fillPolygon();
	drawAxes(150, 150);

	glFlush(); // flush out the buffer contents
}


void main(int argc, char ** argv)
{
	menuPrompt();
	glutInit(& argc, argv);

	glutInitWindowSize(400, 400);					// specify a window size
	glutInitWindowPosition(100, 0);					// specify a window position
	glutCreateWindow("scan-line demonstration");	// create a titled window

	glClearColor(1, 1, 1, 0);						// specify a background color: white 
	gluOrtho2D(-200, 200, -200, 200);				// specify a viewing area

	glutDisplayFunc(myDisplayCallback);				// register a callback

	glutMainLoop();									// get into an infinite loop
}
