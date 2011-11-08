#include "Obj.h"
#include "Tokenizer.h"

namespace Model {

    void Obj::draw(){
        glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object
        //glDrawArrays(GL_TRIANGLES, 0, triangles->size()); // Draw our square
        glDrawElements(GL_TRIANGLES,triangles.size(),GL_UNSIGNED_INT,0);
        glBindVertexArray(0); // Unbind our Vertex Array Object
    }

    bool Obj::load(char* filename) {
        std::string line;
        std::ifstream objFile(filename);    
        if (objFile.is_open() == false) 
            return false;

        //objFile.seekg (0, std::ios::end);                          
        //long fileSize = objFile.tellg();                           
        //objFile.seekg (0, std::ios::beg);                          

        // TODO make a better guess
        vertices.reserve(512);
        normals.reserve(512);
        triangles.reserve(512);

        int triangle_index = 0;                                          
        int normal_index = 0;

        while (! objFile.eof() ) {
            // Get the next line
            getline(objFile,line);

            // Split on space characters
            Tokenizer tokenizer(line," ");
            // while we have tokens on this line
            while(tokenizer.NextToken()){
                std::string lineType = tokenizer.GetToken();
                if(lineType == "v"){
                    // Line is a vertex
                    parseVertex(tokenizer,vertices);
                } else if(lineType == "f"){
                    // Line is a face
                    /**********************************************************
                    The following is a portion of a sample file for a four-sided face
                    element:

                    f 1/1/1 2/2/2 3/3/3 4/4/4

                    Using v, vt, and vn to represent geometric vertices, texture vertices,
                    and vertex normals, the statement would read:

                    f v/vt/vn v/vt/vn v/vt/vn v/vt/vn

                    If there are only vertices and vertex normals for a face element (no
                    texture vertices), you would enter two slashes (//). For example, to
                    specify only the vertex and vertex normal reference numbers, you would
                    enter:

                    f 1//1 2//2 3//3 4//4

                    When you are using a series of triplets, you must be consistent in the
                    way you reference the vertex data. For example, it is illegal to give
                    vertex normals for some vertices, but not all.

                    The following is an example of an illegal statement.

                    f 1/1/1 2/2/2 3//3 4//4
                    ***********************************************************/
                    parseFace(tokenizer);
                } else if(lineType == "#") {
                    // Line is a comment
                    break;
                } else if(lineType == "vn"){ //   vn      0.000000       0.000000       1.000000
                    // Line is a vertex normal
                    parseVertex(tokenizer,normals);
                } else if(lineType == "vt"){ //   vt     -5.000000      -5.000000       0.000000
                    // Line is a texture vertex
                    parseVertex(tokenizer,uvs);
                } else if(lineType == "g"){
                    // Line is for group names
                    break;
                } else if(lineType == "o"){
                    // Line is for object name
                    break;
                }
                else {
                    std::cout << "Unhandled line: " << line << std::endl;
                    break;
                }
            }
        }

        objFile.close();
        triangles.resize(triangles.size());
        normals.resize(normals.size());
        uvs.resize(uvs.size());


        glGenVertexArrays(1, &vaoID[0]); // Create our Vertex Array Object
        glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object so we can use it
        glGenBuffers(1, vboID); // Generate our Vertex Buffer Object

        glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Bind our Vertex Buffer Object
        // We have to use &triangles.front() otherwise we get vector house keeping garbage
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);
        glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer


        glGenBuffers(1,&indexBufferId);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferId);
        // We have to use &triangles.front() otherwise we get vector house keeping garbage
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(triangles[0]), &triangles[0], GL_STATIC_DRAW); 
        glEnableVertexAttribArray(0); // Disable our Vertex Array Object
        glBindVertexArray(0); // Disable our Vertex Buffer Object
        return true;
    }

    void Obj::parseVertex(Tokenizer& tokenizer, std::vector<glm::vec3>& collection){
        float f[3];
        for(int i = 0; i < 3 && tokenizer.NextToken(); i++){
            if(! from_string<float>(f[i],tokenizer.GetToken(),std::dec)) // Print an error if we can't parse it into a float
                std::cerr << "Error parsing token into vertex component: " << tokenizer.GetToken() << std::endl;
        }
        collection.push_back(glm::vec3(f[0],f[1],f[2]));
    }

    void Obj::parseFace(Tokenizer& tokenizer){
        // The index of the vertex to build this face. This will be over written N times
        // once for each vertex in the face
        int vertexNumber;

        while(tokenizer.NextToken()){
            if(from_string<int>(vertexNumber,tokenizer.GetToken(),std::dec)){
                // -1 because OBJ spec counts from 1
                triangles.push_back(vertexNumber - 1);
            }
            else
                std::cerr << "Error parsing token into face component: " << tokenizer.GetToken() << std::endl;
        }
    }

    void Obj::release() {
    }
}
