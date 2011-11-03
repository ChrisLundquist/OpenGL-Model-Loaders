/*
 * Just the class to load Blender .RAW files in OpenGL/GLUT.
 * Needs refactoring
 *
 * RAW files are static objects, stored in ASCII
 * No animation, texture mapping or normals
 */

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

class Model_RAW
{
  public: 
	Model_RAW();
    int Model_RAW::Load(char *filename);
	void Model_RAW::Draw();

	float* Normals;
    float* Faces_Triangles;
	float* Vertex_Buffer; 
	long TotalConnectedPoints;
	long TotalConnectedTriangles;	

};


Model_RAW::Model_RAW()
{

}

int Model_RAW::Load(char* filename)
{
	for (int i = 0; i < TotalConnectedTriangles; i++){  Faces_Triangles[i] = 0x00; }
    this->TotalConnectedTriangles = 0; 

    char* pch = strstr(filename,".raw");

    if (pch != NULL)
    {
	   FILE* file = fopen(filename,"r");
    
		fseek(file,0,SEEK_END);
		long fileSize = ftell(file);

		try
		{
		Vertex_Buffer = (float*) malloc (ftell(file)*3);
		}
		catch (char* )
		{
			return -1;
		}
		if (Vertex_Buffer == NULL) return -1;
		fseek(file,0,SEEK_SET); 

	   Faces_Triangles = (float*) malloc(fileSize*sizeof(float));
	   Normals  = (float*) malloc(fileSize*sizeof(float));

	   // start reading the data
       if (file)
       {
        int i = 0;    
		int quads_index = 0;
		int normal_index = 0;
		char buffer[1000];

		// read file
        while (!feof(file))
        {

			fgets(buffer,1000,file);

				sscanf(buffer,"%f %f %f %f %f %f %f %f %f ", &Faces_Triangles[i], &Faces_Triangles[i+1], &Faces_Triangles[i+2],
														     &Faces_Triangles[i+3], &Faces_Triangles[i+4], &Faces_Triangles[i+5], 
														     &Faces_Triangles[i+6], &Faces_Triangles[i+7], &Faces_Triangles[i+8]);



				float coord1[3] = { Faces_Triangles[i], Faces_Triangles[i+1],Faces_Triangles[i+2]};
				float coord2[3] = {Faces_Triangles[i+3],Faces_Triangles[i+4],Faces_Triangles[i+5]};
				float coord3[3] = {Faces_Triangles[i+6],Faces_Triangles[i+7],Faces_Triangles[i+8]};

				i += 9;
                TotalConnectedTriangles+=9;
        }              
        printf("Opened \n");
      }
      else { printf("File can't be opened\n");  }
    } else {
      printf("File does not have a .raw extension. ");    
    }   
	return 0;
}

void Model_RAW::Draw()
{
 	glEnableClientState(GL_VERTEX_ARRAY);	
 	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3,GL_FLOAT,	0,Faces_Triangles);	
	glNormalPointer(GL_FLOAT, 0, Normals);
	glDrawArrays(GL_TRIANGLES, 0, TotalConnectedTriangles);	
	glDisableClientState(GL_VERTEX_ARRAY);    
	glDisableClientState(GL_NORMAL_ARRAY); 
}