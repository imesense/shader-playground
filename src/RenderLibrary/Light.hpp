#pragma once

namespace ShaderPlayground {
    class RENDERLIBRARY_API Light {
    private:
        XMMATRIX _viewMatrix;
        XMMATRIX _projectionMatrix;

        XMFLOAT4 _ambientColor;
        XMFLOAT4 _diffuseColor;
        XMFLOAT3 _position;
        XMFLOAT3 _lookAt;

    public:
        void SetAmbientColor(float, float, float, float);
        void SetDiffuseColor(float, float, float, float);
        void SetPosition(float, float, float);
        void SetLookAt(float, float, float);

        XMFLOAT4 GetAmbientColor();
        XMFLOAT4 GetDiffuseColor();
        XMFLOAT3 GetPosition();

        void GenerateViewMatrix();
        void GenerateProjectionMatrix(float, float);

        XMMATRIX GetViewMatrix();
        XMMATRIX GetProjectionMatrix();
    };
}
