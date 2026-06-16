#include "CameraController.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/Camera/Camara2D.h"
#include "Engine/Components/Transform.h"

namespace Bisang
{
	void CameraController::Start()
	{
		m_cam2D = m_ownerObj->GetComponent<Camera2D>();
	}

	void CameraController::Update(float dT)
	{
		if (m_target == nullptr) return;
		m_cam2D->SetCameraPostion(m_target->GetWorldPosition());
	}

	void CameraController::SetTarget(GameObject* target)
	{
		m_target = target->GetComponent<Transform>();
	}

}
