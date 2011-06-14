#include "Obj.h"

namespace Model {
    bool Obj::load(char* filename) {
        std::string line;
        std::ifstream objFile (filename);    
        if (objFile.is_open() == false) // we could not open the file
            return false;

        objFile.seekg (0, std::ios::end);                                        // Go to end of the file, 
        long fileSize = objFile.tellg();                                    // get file size
        objFile.seekg (0, std::ios::beg);                                        // we'll use this to register memory for our 3d model

        vertices = new float[fileSize];                            // Allocate memory for the vertices
        triangles = new float[fileSize];            // Allocate memory for the triangles
        normals  = new float[fileSize];                    // Allocate memory for the normals

        int triangle_index = 0;                                                // Set triangle index to zero
        int normal_index = 0;                                                // Set normal index to zero

        while (! objFile.eof() )                                            // Start reading file data
        {        
            getline (objFile,line);                                            // Get line from file

            if (line.c_str()[0] == 'v')                                        // The first character is a v: on this line is a vertex stored.
            {
                line[0] = ' ';                                                // Set first character to 0. This will allow us to use sscanf

                sscanf(line.c_str(),"%f %f %f ",                            // Read floats from the line: v X Y Z
                    &vertices[totalConnectedPoints],
                    &vertices[totalConnectedPoints+1], 
                    &vertices[totalConnectedPoints+2]);

                totalConnectedPoints += POINTS_PER_VERTEX;                    // Add 3 to the total connected points
            }
            else if (line.c_str()[0] == 'f')                                        // The first character is an 'f': on this line is a point stored
            {
                line[0] = ' ';                                                // Set first character to 0. This will allow us to use sscanf

                int vertexNumber[4] = { 0, 0, 0 };
                sscanf(line.c_str(),"%i%i%i",                                // Read integers from the line:  f 1 2 3
                    &vertexNumber[0],                                        // First point of our triangle. This is an 
                    &vertexNumber[1],                                        // pointer to our vertices list
                    &vertexNumber[2] );                                        // each point represents an X,Y,Z.

                vertexNumber[0] -= 1;                                        // OBJ file starts counting from 1
                vertexNumber[1] -= 1;                                        // OBJ file starts counting from 1
                vertexNumber[2] -= 1;                                        // OBJ file starts counting from 1


                /********************************************************************
                * Create triangles (f 1 2 3) from points: (v X Y Z) (v X Y Z) (v X Y Z). 
                * The vertices contains all verteces
                * The triangles will be created using the verteces we read previously
                */

                int tCounter = 0;
                for (int i = 0; i < POINTS_PER_VERTEX; i++)                     {
                    triangles[triangle_index + tCounter   ] = vertices[3*vertexNumber[i] ];
                    triangles[triangle_index + tCounter +1 ] = vertices[3*vertexNumber[i]+1 ];
                    triangles[triangle_index + tCounter +2 ] = vertices[3*vertexNumber[i]+2 ];
                    tCounter += POINTS_PER_VERTEX;
                }

                /*********************************************************************
                * Calculate all normals, used for lighting
                */ 
                float coord1[3] = { triangles[triangle_index], triangles[triangle_index+1],triangles[triangle_index+2]};
                float coord2[3] = {triangles[triangle_index+3],triangles[triangle_index+4],triangles[triangle_index+5]};
                float coord3[3] = {triangles[triangle_index+6],triangles[triangle_index+7],triangles[triangle_index+8]};
                float *norm = calculateNormal( coord1, coord2, coord3 );

                tCounter = 0;
                for (int i = 0; i < POINTS_PER_VERTEX; i++) {
                    normals[normal_index + tCounter ] = norm[0];
                    normals[normal_index + tCounter +1] = norm[1];
                    normals[normal_index + tCounter +2] = norm[2];
                    tCounter += POINTS_PER_VERTEX;
                }

                triangle_index += TOTAL_FLOATS_IN_TRIANGLE;
                normal_index += TOTAL_FLOATS_IN_TRIANGLE;
                totalConnectedTriangles += TOTAL_FLOATS_IN_TRIANGLE;            
            } else {
                    std::cout << "Unhandled line: " << line << std::endl;
            }
        }
        objFile.close();                                        // Close OBJ file

        return true;
    }

    void Obj::release() {
        delete[] triangles;
        delete[] normals;
        delete[] vertices;
    }
}