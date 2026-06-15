#include "CameraController.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/Camera/Camara2D.h"
#include "Engine/Components/Transform.h"

namespace Bisang
{
	void CameraController::Start()
	{
		m_cam2D = m_ownerObj->GetComponent<Camera2D>();
		GameObject* princess = FindGameObjectByName("Princess");
		m_princessTransform = princess->GetComponent<Transform>();
		m_initailPrincessPos = m_princessTransform->GetPosition();
	}

	void CameraController::Update(float dT)
	{
		m_cam2D->SetCameraPostion(m_princessTransform->GetWorldPosition());
	}
}
