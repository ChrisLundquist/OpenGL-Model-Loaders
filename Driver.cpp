#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include "Model.h"
#include "Obj.h"

void usage(){
    std::cout << "Please specify paths to models" << std::endl;
}

void draw(Model::Model* model){
    glEnable(GL_TEXTURE_2D);	
    //    glBindTexture(GL_TEXTURE_2D, texturen[0]);

    glEnableClientState(GL_VERTEX_ARRAY);	
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, model->normals);

    glTexCoordPointer(2,GL_FLOAT,0, model->textures );
    glVertexPointer(3,GL_FLOAT,	0,model->triangles);	 
    glDrawArrays(GL_TRIANGLES, 0, model->totalConnectedTriangles);	

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);    
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glDisable(GL_TEXTURE_2D);
}

void main(int argc, char** argv){
    /*
    //TODO, parse argv
    if(argc < 1){
        usage();
        return;
    }
    */

    Model::Model* m = new Model::Obj();
    m->load("cube.obj");

}