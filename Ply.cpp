/* Demonstrates how to load Ply files
* Needs some refactoring.
*
* Model needs to be triangulated
* Use blender
*
* Just the class for loading Ply files. 
* 
*/ 

#include "Ply.h"

namespace Model { 
    Ply::Ply() {
        totalConnectedQuads = 0;
        totalFaces = 0;
    }


    bool Ply::load(char* filename) {

        char* pch = strstr(filename,".ply");

        if (pch != NULL) {
            FILE* file = fopen(filename,"r");

            if(file == NULL)
                return false;

            fseek(file,0,SEEK_END);
            long fileSize = ftell(file);

            try {
                vertices = (float*) malloc (ftell(file));
            }
            catch (char* ) {
                return false;
            }
            if (vertices == NULL) return -1;
            fseek(file,0,SEEK_SET); 

            triangles = (float*) malloc(fileSize*sizeof(float));
            normals  = (float*) malloc(fileSize*sizeof(float));

                int i = 0;   
                int temp = 0;
                int quads_index = 0;
                int triangle_index = 0;
                int normal_index = 0;
                char buffer[1000];


                fgets(buffer,300,file);            // ply


                // READ HEADER
                // -----------------

                // Find number of vertexes
                while (  strncmp( "element vertex", buffer,strlen("element vertex")) != 0  )
                {
                    fgets(buffer,300,file);            // format
                }
                strcpy(buffer, buffer+strlen("element vertex"));
                sscanf(buffer,"%i", &this->totalConnectedPoints);


                // Find number of vertexes
                fseek(file,0,SEEK_SET);
                while (  strncmp( "element face", buffer,strlen("element face")) != 0  )
                {
                    fgets(buffer,300,file);            // format
                }
                strcpy(buffer, buffer+strlen("element face"));
                sscanf(buffer,"%i", &totalFaces);


                // go to end_header
                while (  strncmp( "end_header", buffer,strlen("end_header")) != 0  )
                {
                    fgets(buffer,300,file);            // format
                }

                //----------------------


                // read verteces
                i =0;
                for (int iterator = 0; iterator < this->totalConnectedPoints; iterator++)
                {
                    fgets(buffer,300,file);

                    sscanf(buffer,"%f %f %f", &vertices[i], &vertices[i+1], &vertices[i+2]);
                    i += 3;
                }

                // read faces
                i =0;
                for (int iterator = 0; iterator < totalFaces; iterator++)
                {
                    fgets(buffer,300,file);

                    if (buffer[0] == '3')
                    {

                        int vertex1 = 0, vertex2 = 0, vertex3 = 0;
                        //sscanf(buffer,"%i%i%i\n", vertex1,vertex2,vertex3 );
                        buffer[0] = ' ';
                        sscanf(buffer,"%i%i%i", &vertex1,&vertex2,&vertex3 );
                        /*vertex1 -= 1;
                        vertex2 -= 1;
                        vertex3 -= 1;
                        */
                        //  vertex == punt van vertex lijst
                        // vertex_buffer -> xyz xyz xyz xyz
                        //printf("%f %f %f ", vertices[3*vertex1], vertices[3*vertex1+1], vertices[3*vertex1+2]);

                        triangles[triangle_index] = vertices[3*vertex1];
                        triangles[triangle_index+1] = vertices[3*vertex1+1];
                        triangles[triangle_index+2] = vertices[3*vertex1+2];
                        triangles[triangle_index+3] = vertices[3*vertex2];
                        triangles[triangle_index+4] = vertices[3*vertex2+1];
                        triangles[triangle_index+5] = vertices[3*vertex2+2];
                        triangles[triangle_index+6] = vertices[3*vertex3];
                        triangles[triangle_index+7] = vertices[3*vertex3+1];
                        triangles[triangle_index+8] = vertices[3*vertex3+2];

                        float coord1[3] = { triangles[triangle_index], triangles[triangle_index+1],triangles[triangle_index+2]};
                        float coord2[3] = {triangles[triangle_index+3],triangles[triangle_index+4],triangles[triangle_index+5]};
                        float coord3[3] = {triangles[triangle_index+6],triangles[triangle_index+7],triangles[triangle_index+8]};
                        float *norm = this->calculateNormal( coord1, coord2, coord3 );

                        normals[normal_index] = norm[0];
                        normals[normal_index+1] = norm[1];
                        normals[normal_index+2] = norm[2];
                        normals[normal_index+3] = norm[0];
                        normals[normal_index+4] = norm[1];
                        normals[normal_index+5] = norm[2];
                        normals[normal_index+6] = norm[0];
                        normals[normal_index+7] = norm[1];
                        normals[normal_index+8] = norm[2];

                        normal_index += 9;

                        triangle_index += 9;
                        totalConnectedTriangles += 3;
                    }


                    i += 3;
                }
                fclose(file);
        } else {
            std::cerr << "File does not have a .Ply extension. " << std::endl;
        }   
        return 0;
    }
}
