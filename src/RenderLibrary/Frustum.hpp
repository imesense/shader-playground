#pragma once

namespace ShaderPlayground {
    class RENDERLIBRARY_API Frustum {
    private:
        XMVECTOR _planes[6];

    public:
        void ConstructFrustum(float screenDepth, CXMMATRIX projectionMatrix, CXMMATRIX viewMatrix);

        bool CheckPoint(float x, float y, float z);
        bool CheckCube(float xCenter, float yCenter, float zCenter, float size);
        bool CheckSphere(float xCenter, float yCenter, float zCenter, float radius);
        bool CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize);
    };
}