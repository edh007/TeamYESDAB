#pragma once

#include "Component.h"
#include "math\Matrix4.h"

namespace gi
{
	class Entity;

	class CameraComponent : public Component
	{
		enum Movement {
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT,
			PITCH_UP,
			PITCH_DOWN,
			YAW_DOWN,
			YAW_UP
		};

	public:
		CameraComponent(Entity* pOwner);
		~CameraComponent();

		Mat4 GetViewMat();
		void ProcessKeyboard(Movement dir, float dt);
		void ProcessMouseMov(float xOffset, float yOffset, bool constrainPitch = true);
		void ProcessMouseScroll(float yOffset);

		void UpdateCameraVec();


	private:
		// Camera Attributes
		Vec3 m_front;
		Vec3 m_up;
		Vec3 m_right;
		//Vec3 m_worldUp; // ??

		// Angle
		float m_yaw;
		float m_pitch;

		// options
		float m_zoom;
		float m_movementSpeed;
		float m_mouseSensitivity;

		Mat4 m_viewMat;
		Mat4 m_projMat;
	};

}