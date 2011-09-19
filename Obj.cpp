#include "Obj.h"
#include "Tokenizer.h"

namespace Model {
    bool Obj::load(char* filename) {
        std::string line;
        std::ifstream objFile(filename);    
        if (objFile.is_open() == false) 
            return false;

        objFile.seekg (0, std::ios::end);                          
        long fileSize = objFile.tellg();                           
        objFile.seekg (0, std::ios::beg);                          

        // TODO make a better guess
        vertices->reserve(fileSize);
        normals->reserve(fileSize);
        triangles->reserve(fileSize);

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
                    parseVertex(tokenizer);
                } else if (lineType == "f"){
                    // Line is a face
                    parseFace(tokenizer);
                } else if (lineType == "#") {
                    break;
                } else {
                    std::cout << "Unhandled line: " << line << std::endl;
                    break;
                }
            }
        }

        objFile.close();
        triangles->resize(triangles->size());
        normals->resize(normals->size());
        textureCoordinates->resize(textureCoordinates->size());

        return true;
    }

    void Obj::parseVertex(Tokenizer& tokenizer){
        float f;
        while(tokenizer.NextToken()){
            if(from_string<float>(f,tokenizer.GetToken(),std::dec))
                vertices->push_back(f);
            else
                std::cerr << "Error parsing token into vertex component: " << tokenizer.GetToken() << std::endl;
        }
    }

    void Obj::parseFace(Tokenizer& tokenizer){
        // The index of the vertex to build this face. This will be over written N times
        // once for each vertex in the face
        int vertexNumber;

        while(tokenizer.NextToken()){
            if(from_string<int>(vertexNumber,tokenizer.GetToken(),std::dec)){
                // -1 because OBJ spec counts from 1
                triangles->push_back(vertices->at( vertexNumber - 1));
            }
            else
                std::cerr << "Error parsing token into face component: " << tokenizer.GetToken() << std::endl;
        }
    }

    void Obj::release() {
        delete[] triangles;
        delete[] normals;
        delete[] vertices;
    }
}
