#ifndef Model_h__
#define Model_h__


#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
namespace Model {
#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9
#define KEY_ESCAPE 27
    class Model {
        public: 
            Model();            
            float* Model::calculateNormal(float* coord1,float* coord2,float* coord3 );
            virtual bool Model::load(char *filename) = 0;
            virtual void Model::release() = 0;

            float* normals;
            float* triangles;
            float* vertices;
            float* textures;
            long totalConnectedPoints;
            long totalConnectedTriangles;
    };
}

#endif // Model_h__
