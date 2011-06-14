#include "Model.h"
namespace Model { 
    class Ply : public Model {
        public:
            Ply();
            bool Ply::load(char *filename);

            float* quads;
            int totalConnectedQuads;
            int totalFaces;
    };
}
