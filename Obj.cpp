#include "Obj.h"
#include "Tokenizer.h"

namespace Model {

	void Obj::draw(){
		glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object

		glDrawArrays(GL_TRIANGLES, 0, triangles->size()); // Draw our square

		glBindVertexArray(0); // Unbind our Vertex Array Object
	}

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
					// Line is a comment
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


		glGenVertexArrays(1, &vaoID[0]); // Create our Vertex Array Object
		glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object so we can use it
		glGenBuffers(1, vboID); // Generate our Vertex Buffer Object
		glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Bind our Vertex Buffer Object
		// We have to use &triangles[0] or &triangles.front() otherwise we get vector house keeping garbage
		glBufferData(GL_ARRAY_BUFFER, triangles->size() * sizeof(GLfloat), &triangles->front(), GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer

		glEnableVertexAttribArray(0); // Disable our Vertex Array Object
		glBindVertexArray(0); // Disable our Vertex Buffer Object
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
				int index = (vertexNumber - 1) * 3;
				triangles->push_back(vertices->at( index));
				triangles->push_back(vertices->at( index + 1));
				triangles->push_back(vertices->at( index + 2));
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
