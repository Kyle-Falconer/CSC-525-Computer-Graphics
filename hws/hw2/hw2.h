#include <iostream>
#include <GL/glut.h>				// include GLUT library
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <iterator>
#include <array>
using namespace std;

#define DEBUG 0
// #define testFile "c:\\poly3.txt"


float slope(float x1, float y1, float x2, float y2);
void lineCoords(int x1, int y1, int x2, int y2);
void lineCoords(float x1, float y1, float x2, float y2);
void drawAxes(int x_min, int y_min);
int pseudoRoundf(float num);
void addEdgePair(int x, int y);
bool intCompare (int i,int j);