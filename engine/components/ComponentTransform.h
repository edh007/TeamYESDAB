#pragma once
#include "base\Component.h"
#include "math\Math.h"

#include <string>

namespace gi
{
	class ComponentTransform : public Component
	{
	public:
		static const std::string COMPONENT_ID;

		static ComponentTransform* CreateComponentTransform(Entity* pOwner);

		Vec3 GetPositionVec() const;
		Vec3 GetScaleVec() const;
		Vec3 GetRotationVec() const;
        Vec3 GetOriginPosVec() const;

		Mat4 GetTransformMat();
		
		// =
		void SetPosition(float x, float y, float z);
		void SetPosition(const Vec3& pos);
        void SetOriginPosition(const Vec3& originPos);
		// +=
		void Translate(float x, float y = 0.f, float z = 0.f);
		void Translate(const Vec3& translationVec);

		// =
		void SetScale(float x, float y, float z);
		void SetScale(const Vec3& scaleVec);
		// +=
		void Scale(float x, float y, float z);
		void Scale(const Vec3& scaleVec);
		
		// =
		void SetRotation(float x, float y, float z);
		void SetRotation(const Vec3& rotVec);

        void SetRotationX(float x);
        void SetRotationY(float y);
        void SetRotationZ(float z);

		// +=
		void Rotate(float x, float y, float z, float angle);
		void Rotate(const Vec3& rot, float angle);

        void AddRotationX(float x);
        void AddRotationY(float y);
        void AddRotationZ(float z);

		explicit ComponentTransform(Entity* pObject);
		virtual ~ComponentTransform();
        void DrawComponent();

        Vec3 m_dir;
        Vec3 m_right;

	private:
		//explicit ComponentTransform(Entity* pObject);
		//virtual ~ComponentTransform();

		void Transform();

		Vec3 m_posVec;
		Vec3 m_scaleVec;
		Vec3 m_rotVec;
        Vec3 m_originPosVec;

		float m_angle;

        /*Vec3 m_dir;
        Vec3 m_right;*/

		Mat4 m_transform;

	};
}