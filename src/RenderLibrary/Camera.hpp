#pragma once

namespace ShaderPlayground {
    class Camera {
    private:
        Timer _time;

        XMMATRIX _viewMatrix;

        XMFLOAT3 _pos;
        XMFLOAT3 _rot;

        float _frameTime;

        float _forwardSpeed, _backwardSpeed;
        float _upwardSpeed, _downwardSpeed;
        float _leftTurnSpeed, _rightTurnSpeed;
        float _leftSpeed, _rightSpeed;
        float _lookUpSpeed, _lookDownSpeed;

    public:
        Camera();
        virtual ~Camera();

        void Render();

        void MoveForward(bool keydown);
        void MoveBackward(bool keydown);
        void MoveLeft(bool keydown);
        void MoveRight(bool keydown);

        void MoveUpward(bool keydown);
        void MoveDownward(bool keydown);

        void RotateLeft(bool keydown);
        void RotateRight(bool keydown);

        void LookUpward(bool keydown);
        void LookDownward(bool keydown);

        void SetPos(float x, float y, float z);
        void SetRot(float x, float y, float z);

        XMFLOAT3 GetPos() {
            return _pos;
        }

        XMFLOAT3 GetRot() {
            return _rot;
        }

        CXMMATRIX GetViewMatrix();
    };
}
