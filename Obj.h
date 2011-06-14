/*
*
* Demonstrates how to load and display an Wavefront OBJ file. 
* Using triangles and normals as static object. No texture mapping.
*
* OBJ files must be triangulated!!!
* Non triangulated objects wont work!
* You can use Blender to triangulate
*
*/

#include "Model.h"

namespace Model {
    class Obj : public Model {
    public: 
        bool Obj::load(char *filename);   // Loads the model
        void Obj::release();              // Release the model
    };
}

#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9
