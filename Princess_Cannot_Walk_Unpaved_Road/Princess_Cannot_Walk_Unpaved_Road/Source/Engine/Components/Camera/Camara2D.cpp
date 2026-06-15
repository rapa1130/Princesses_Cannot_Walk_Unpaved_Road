#include "Camara2D.h"
#include "Engine/Math/Vector.h"
#include "Engine//Object/GameObject.h"
#include "Engine/Components/Transform.h"


namespace Bisang
{
	Camera2D::Camera2D(GameObject* ownerObj)
		: Component(ownerObj) 
	{
		m_transform = ownerObj->GetComponent<Transform>();
	}

	D2D1::Matrix3x2F Camera2D::GetViewMatrix() const
	{
		D2D1::Matrix3x2F mxView;

		Vector3 camPos = m_transform->GetPosition();
		float camRot = m_transform->GetRotation();
		Vector3 camScale = m_transform->GetScale();

		D2D1::Matrix3x2F mxScale = D2D1::Matrix3x2F::Scale(camScale.x, camScale.y);
		D2D1::Matrix3x2F mxRot = D2D1::Matrix3x2F::Rotation(camRot);
		D2D1::Matrix3x2F mxTranslate = D2D1::Matrix3x2F::Translation(-camPos.x, -camPos.y);

		mxView = mxScale * mxRot * mxTranslate;

		return mxView;
	}
	void Camera2D::SetCameraPostion(const Vector3& pos)
	{
		m_transform->SetPosition(pos);
	}

	void Camera2D::SetCameraRotation(float rot)
	{
		m_transform->SetRotation(rot);
	}

	void Camera2D::SetCameraScale(const Vector3& scale)
	{
		m_transform->SetScale(scale);
	}

	Vector3 Camera2D::GetCameraPosition() const
	{
		return m_transform->GetPosition();
	}
	float Camera2D::GetCameraRotation() const
	{
		return m_transform->GetRotation();
	}
	Vector3 Camera2D::GetCameraScale() const
	{
		return m_transform->GetScale();
	}

}
