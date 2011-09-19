#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include "Model.h"
#include "Obj.h"

Model::Obj m = Model::Obj();


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

void printGLError() {
    GLenum fboStatus;
    fboStatus = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
    std::string error = "";
    if(fboStatus != GL_FRAMEBUFFER_COMPLETE) {
        switch (fboStatus) { 
            case GL_FRAMEBUFFER_UNDEFINED:
                // Oops, no window exists?
                error = "Framebuffer Undefined";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
                // Check the status of each attachment
                error = "Framebuffer Incomplete Attachment";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
                // Attach at least one buffer to the FBO
                error = "Framebuffer Incomplete Missing Attachment";
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
                error = "Framebuffer incomplete draw buffer";
                // Check that all attachments enabled via
                // glDrawBuffers exist in FBO case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
                // Check that the buffer specified via // glReadBuffer exists in FBO break;
                break;
            case GL_FRAMEBUFFER_UNSUPPORTED: 
                error  = "Framebuffer Unsupported";
                // Reconsider formats used for attached buffers break;
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: 
                error = "Framebuffer Incomplete Multisample";
                // Make sure the number of samples for each // attachment is the same break;
                break;
            case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS: 
                error = "Framebuffer Incomplete Layer Targets";
                
                // Make sure the number of layers for each // attachment is the same break;
                break;
            default:
                error = "Unknown Error";
                break;
        }
        std::cerr << error << std::endl;
    }
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
    printGLError();
    /*
    //TODO, parse argv to load a given model type then render it
    if(argc < 1){
    usage();
    return;
    }
    */
    m.load("cube_cube.obj");
    printGLError();
    glutMainLoop ();
}
