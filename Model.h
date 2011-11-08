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
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
namespace Model {
    class Model {
        public: 
            Model();
			Model(char* filename);
            virtual ~Model();
			
			// calculates the normal of a triangle
            float* calculateNormal(float coord1[3],float coord2[3],float coord3[3] );
            virtual bool load(char *filename) = 0;
            virtual void release() = 0;
			virtual void draw() = 0;

            std::vector<glm::vec3> normals;
            std::vector<unsigned> triangles;
            std::vector<glm::vec3> vertices;
            std::vector<glm::vec3> uvs;
			unsigned vaoID[1];
			unsigned vboID[1];
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
