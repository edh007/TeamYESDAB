#include "ComponentTransform.h"
#include <imgui.h>

const std::string gi::ComponentTransform::COMPONENT_ID = "gi_cmp_transform";

gi::ComponentTransform::ComponentTransform(Entity* pObject)
    : Component(pObject), m_angle(0.f), m_originPosVec(NULL),
    m_dir(Vec3(0.f, 0.f, 1.f)), m_right(Vec3(1.f, 0.f, 0.f))
{

}

gi::ComponentTransform::~ComponentTransform()
{
	m_pOwner = nullptr;
}


void gi::ComponentTransform::Transform()
{
	Mat4 translation, rotation, scaling;

	translation.Translate(m_posVec);
    rotation.Rotate(m_rotVec * 0.0174532925f);// , MATH_DEG_TO_RAD(m_angle));
	scaling.Scale(m_scaleVec);

	m_transform.Transform(translation, rotation, scaling);

    m_dir = rotation.ToMatrix3() * Vec3(0.f, 0.f, 1.f);
    m_dir.Normalize();
    m_right = rotation.ToMatrix3() * Vec3(1.f, 0.f, 0.f);
    m_right.Normalize();
}

gi::ComponentTransform* gi::ComponentTransform::CreateComponentTransform(Entity* pOwner)
{
	// TODO (JIN) : Check pOwner has transform component.
	ComponentTransform* pTransform = new ComponentTransform(pOwner);

	return pTransform;
}

Vec3 gi::ComponentTransform::GetPositionVec() const
{
	return m_posVec;
}

Vec3 gi::ComponentTransform::GetOriginPosVec() const
{
    return m_originPosVec;
}

Vec3 gi::ComponentTransform::GetScaleVec() const
{
	return m_scaleVec;
}

Vec3 gi::ComponentTransform::GetRotationVec() const
{
	return m_rotVec;
}

Mat4 gi::ComponentTransform::GetTransformMat()
{
	Transform();

	return m_transform;
}

void gi::ComponentTransform::SetPosition(float x, float y, float z)
{
	m_posVec.Set(x, y, z);
}

void gi::ComponentTransform::SetPosition(const Vec3& pos)
{
	m_posVec = pos;
}

void gi::ComponentTransform::SetOriginPosition(const Vec3& originPos)
{
    m_originPosVec = originPos;
}

void gi::ComponentTransform::Translate(float x, float y, float z)
{
	m_posVec.Add(x, y, z);
}

void gi::ComponentTransform::Translate(const Vec3& translationVec)
{
	m_posVec += translationVec;
}

void gi::ComponentTransform::SetScale(float x, float y, float z)
{
	m_scaleVec.Set(x, y, z);
}

void gi::ComponentTransform::SetScale(const Vec3& scaleVec)
{
	m_scaleVec = scaleVec;
}

void gi::ComponentTransform::Scale(float x, float y, float z)
{
	m_scaleVec.Add(x, y, z);
}

void gi::ComponentTransform::Scale(const Vec3& scaleVec)
{
	m_scaleVec += scaleVec;
}

void gi::ComponentTransform::SetRotation(float x, float y, float z)
{
	m_rotVec.Set(x, y, z);
}

void gi::ComponentTransform::SetRotation(const Vec3& rotVec)
{
	m_rotVec = rotVec;
}

void gi::ComponentTransform::SetRotationX(float x)
{
    m_rotVec.x = x;
}

void gi::ComponentTransform::SetRotationY(float y)
{
    m_rotVec.y = y;

}

void gi::ComponentTransform::SetRotationZ(float z)
{
    m_rotVec.z = z;
}

void gi::ComponentTransform::Rotate(float x, float y, float z, float angle)
{
    m_angle = angle;
	m_rotVec.Add(x, y, z);
}

void gi::ComponentTransform::Rotate(const Vec3& rot, float angle)
{
    m_angle = angle;
	m_rotVec += rot;
}

void gi::ComponentTransform::AddRotationX(float x)
{
    m_rotVec.x += x;
}

void gi::ComponentTransform::AddRotationY(float y)
{
    m_rotVec.y += y;
}

void gi::ComponentTransform::AddRotationZ(float z)
{
    m_rotVec.z += z;
}

void gi::ComponentTransform::DrawComponent()
{
    if (ImGui::CollapsingHeader("Transform Component"))
    {
        ImGui::PushItemWidth(160);
        {
            ImGui::InputFloat("Position X", &m_posVec.x, 1.f, 10.f, 2);
            ImGui::InputFloat("Position Y", &m_posVec.y, 1.f, 10.f, 2);
            ImGui::InputFloat("Position Z", &m_posVec.z, 1.f, 10.f, 2);
            ImGui::InputFloat("Size x", &m_scaleVec.x, 0.05f, 2.0f, 2);
            ImGui::InputFloat("Size y", &m_scaleVec.y, 0.05f, 2.0f, 2);
            ImGui::InputFloat("Size z", &m_scaleVec.z, 0.05f, 2.0f, 2);
            ImGui::InputFloat("Rotation X", &m_rotVec.x, 1, 5, 2);
            ImGui::InputFloat("Rotation Y", &m_rotVec.y, 1, 5, 2);
            ImGui::InputFloat("Rotation Z", &m_rotVec.z, 1, 5, 2);
        }
        ImGui::PopItemWidth();
    }
}