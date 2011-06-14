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
            getline (objFile,line);      
            Tokenizer tokenizer(line," ");
            while(tokenizer.NextToken()){
                std::string lineType = tokenizer.GetToken();
                if(lineType == "v"){
                    parseVertex(tokenizer);
                } else if (lineType == "f"){
                    parseFace(tokenizer);
                    totalConnectedTriangles++;
                } else if (lineType == "#") {
                    // Line is a comment
                } else {
                    std::cout << "Unhandled line: " << line << std::endl;
                }

                break;
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
        totalConnectedPoints += POINTS_PER_VERTEX;   
    }

    void Obj::parseFace(Tokenizer& tokenizer){
        int vertexNumber[3] = { 0, 0, 0 };
        
        for(int i = 0; i < 3; ++i){
            tokenizer.NextToken();
            if(from_string<int>(vertexNumber[i],tokenizer.GetToken(),std::dec)){
                triangles->push_back(vertices->at( vertexNumber[i]- 1));
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