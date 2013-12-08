//OBJ loader from http://openglsamples.sourceforge.net/
//Modified for color

#include <fstream>
#include <iostream>
#include <sstream>
#include <fstream>
#include <GL/glut.h>

class Model_OBJ
{
  public: 
    Model_OBJ();			
    float* Model_OBJ::calculateNormal(float* coord1,float* coord2,float* coord3 );
    int Model_OBJ::Load(std::string);	// Loads the model
    void Model_OBJ::Draw();					// Draws the model on the screen
    void Model_OBJ::Release();				// Release the model
 
    float* normals;							// Stores the normals
    float* Faces_Triangles;					// Stores the triangles
    float* vertexBuffer;					// Stores the points which make the object
    long TotalConnectedPoints;				// Stores the total number of connected verteces
    long TotalConnectedTriangles;			// Stores the total number of connected triangles
    float color[3];
 
};
 
 
#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9
using namespace std;




