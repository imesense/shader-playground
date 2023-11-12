#pragma once
#include "Timer/Timer.h"

namespace Camera
{
	class Camera
	{
	public:
		Camera();

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

		DirectX::XMFLOAT3 GetPos() { return m_pos; }
		DirectX::XMFLOAT3 GetRot() { return m_rot; }

		DirectX::CXMMATRIX GetViewMatrix();

	private:
		Timer::Timer m_time;
		DirectX::XMMATRIX m_viewMatrix;
		DirectX::XMFLOAT3 m_pos;
		DirectX::XMFLOAT3 m_rot;

		float m_frameTime;

		float m_forwardSpeed, m_backwardSpeed;
		float m_upwardSpeed, m_downwardSpeed;
		float m_leftTurnSpeed, m_rightTurnSpeed;
		float m_leftSpeed, m_rightSpeed;
		float m_lookUpSpeed, m_lookDownSpeed;
	};
}