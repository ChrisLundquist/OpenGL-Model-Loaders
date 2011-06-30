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
#include <vector>
namespace Model {
#define POINTS_PER_VERTEX 3
#define TOTAL_FLOATS_IN_TRIANGLE 9
#define KEY_ESCAPE 27
    class Model {
        public: 
            Model();
            virtual ~Model();

            float* calculateNormal(float* coord1,float* coord2,float* coord3 );
            virtual bool load(char *filename) = 0;
            virtual void release() = 0;

            std::vector<float>* normals;
            std::vector<float>* triangles;
            std::vector<float>* vertices;
            std::vector<float>* textureCoordinates;
            long totalConnectedPoints;
            long totalConnectedTriangles;
    };
    template <class T>

    bool from_string(T& t, 
        const std::string& s, 
        std::ios_base& (*f)(std::ios_base&)) {
        std::istringstream iss(s);
        return !(iss >> f >> t).fail();
    }
}

#endif // Model_h__
