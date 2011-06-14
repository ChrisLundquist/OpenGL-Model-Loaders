#include "Model.h"
namespace Model {
    Model::Model(){
        totalConnectedTriangles = 0;
        totalConnectedPoints = 0;

        vertices = new std::vector<float>();
        triangles = new std::vector<float>();
        normals = new std::vector<float>();
        textureCoordinates = new std::vector<float>();
    }

    float* Model::calculateNormal(float* coord1, float* coord2, float* coord3){
        /* calculate Vector1 and Vector2 */
        float va[3], vb[3], vr[3], val;
        va[0] = coord1[0] - coord2[0];
        va[1] = coord1[1] - coord2[1];
        va[2] = coord1[2] - coord2[2];

        vb[0] = coord1[0] - coord3[0];
        vb[1] = coord1[1] - coord3[1];
        vb[2] = coord1[2] - coord3[2];

        /* cross product */
        vr[0] = va[1] * vb[2] - vb[1] * va[2];
        vr[1] = vb[0] * va[2] - va[0] * vb[2];
        vr[2] = va[0] * vb[1] - vb[0] * va[1];

        /* normalization factor */
        val = sqrt( vr[0]*vr[0] + vr[1]*vr[1] + vr[2]*vr[2] );

        float norm[3];
        norm[0] = vr[0]/val;
        norm[1] = vr[1]/val;
        norm[2] = vr[2]/val;

        return norm;
    }
}
