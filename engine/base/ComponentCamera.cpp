#include "ComponentCamera.h"

#include "math\MathUtil.h"
#include "base\Entity.h"
#include "components\ComponentTransform.h"

// TODO (JIN) : Delete it
#define CAMERA_ROT_VEL 30.f

gi::CameraComponent::CameraComponent(Entity* pOwner) : Component(pOwner)
{
}

gi::CameraComponent::~CameraComponent()
{
}

Mat4 gi::CameraComponent::GetViewMat()
{

	auto pTransform = m_pOwner->GetComponentContainer().GetComponent<ComponentTransform>();

	if (pTransform == nullptr) // TODO (JIN) : ASSERT
		return GetLookAt(Vec3(), m_front, m_up);

	return GetLookAt(pTransform->GetPositionVec()/*pos*/, m_front, m_up);
}

void gi::CameraComponent::ProcessKeyboard(Movement dir, float dt)
{
	float vel = m_movementSpeed * dt;

	auto pTransform = m_pOwner->GetComponentContainer().GetComponent<ComponentTransform>();

	if (pTransform == nullptr) // TODO (JIN) : ASSERT
		return;

	switch(dir)
	{
		case FORWARD:
		{
			pTransform->Translate(m_front * vel);
		}break;
		case BACKWARD:
		{
			pTransform->Translate(-m_front * vel);
		}break;
		case LEFT:
		{
			pTransform->Translate(-m_right * vel);
		}break;
		case RIGHT:
		{
			pTransform->Translate(m_right * vel);
		}break;
		case PITCH_UP:
		{
			m_pitch += CAMERA_ROT_VEL * vel;
			UpdateCameraVec();
		}break;
		case PITCH_DOWN:
		{
			m_pitch -= CAMERA_ROT_VEL * vel;
			UpdateCameraVec();
		}break;
		case YAW_UP:
		{
			m_yaw += CAMERA_ROT_VEL * vel;
			UpdateCameraVec();
		}break;
		case YAW_DOWN:
		{
			m_yaw -= CAMERA_ROT_VEL * vel;
			UpdateCameraVec();
		}break;
	}

	if (m_pitch > 89.f)
		m_pitch = 89.f;
	else if (m_pitch < -89.f)
		m_pitch = -89.f;
}

void gi::CameraComponent::ProcessMouseMov(float xOffset, float yOffset, bool constrainPitch)
{
	xOffset *= m_mouseSensitivity;
	yOffset *= m_mouseSensitivity;

	m_yaw += xOffset;
	m_pitch += yOffset;

	// DONGHO : Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (m_pitch > 89.f)
		m_pitch = 89.f;
	else if (m_pitch < -89.f)
		m_pitch = -89.f;

	// Update Front, Right and Up Vectors using the updated Eular angles
	UpdateCameraVec();
}

void gi::CameraComponent::ProcessMouseScroll(float yOffset)
{
	if (m_zoom >= 1.0f && m_zoom <= 45.0f)
		m_zoom -= yOffset;
	if (m_zoom <= 1.0f)
		m_zoom = 1.0f;
	if (m_zoom >= 45.0f)
		m_zoom = 45.0f;
}

void gi::CameraComponent::UpdateCameraVec()
{
	// Calculate the new Front vector
	float degYaw = DegreeToRadian(m_yaw);
	float degPitch = DegreeToRadian(m_pitch);

	m_front.x = cos(degYaw) * cos(DegreeToRadian(degPitch));
	m_front.y = sin(DegreeToRadian(degPitch));
	m_front.z = sin(degYaw) * cos(DegreeToRadian(degPitch));
	m_front.Normalize();
	// Also re-calculate the Right and Up vector
	m_right = (m_front.CrossProduct(Vec3(0.f, 1.f, 0.f))).Normalize();
	// Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	m_up = (m_right.CrossProduct(m_front)).Normalize();
}
