#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/glut.h>
#include "Model.h"
#include "Obj.h"

void usage(){
    std::cout << "Please specify paths to models" << std::endl;
}

void draw(Model::Model* model){
    //glEnable(GL_TEXTURE_2D);	
    //    glBindTexture(GL_TEXTURE_2D, texturen[0]);

//    glutSolidTeapot(1);
    glEnableClientState(GL_VERTEX_ARRAY);	
  //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
//    glNormalPointer(GL_FLOAT, 0, model->normals);

//    glTexCoordPointer(2,GL_FLOAT,0, model->textureCoordinates );
    glVertexPointer(3,GL_FLOAT,	0,model->triangles);	 
    glDrawArrays(GL_TRIANGLES, 0, model->totalConnectedTriangles);	

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);    
//    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    //glDisable(GL_TEXTURE_2D);
}

void reshape(GLint width, GLint height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (float)width / height, 1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y){

}
Model::Obj m = Model::Obj();
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 0, -6);
    glColor3f(1,1,1);
    draw(&m);
    glutSwapBuffers();
    int i;
    if(i = glGetError())
        std::cerr << "OpenGL Error" << std::endl;
}

int main(int argc, char** argv){
    glutInit (&argc, argv);
    glutInitWindowSize (800, 600);
    glutInitDisplayMode ( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow ("Model Loader Example");
    glutReshapeFunc (reshape);
    glutKeyboardFunc (keyboard);
    glutDisplayFunc (display);
    glShadeModel(GL_SMOOTH);                // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Black Background
    glClearDepth(1.0f);                     // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                 // The Type Of Depth Testing To Do
    /*
    //TODO, parse argv
    if(argc < 1){
        usage();
        return;
    }
    */
    m.load("cube.obj");
    glutMainLoop ();
}
