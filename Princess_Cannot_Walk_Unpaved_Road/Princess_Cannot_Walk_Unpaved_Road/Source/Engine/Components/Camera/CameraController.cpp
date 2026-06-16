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
        if (!m_cam2D || !m_target)
            return;

        Vector3 cameraPos = m_target->GetPosition();

        if (m_isShaking)
        {
            m_shakeTimer += dT;

            float progress = m_shakeTimer / m_shakeDuration;

            if (progress >= 1.0f)
            {
                progress = 1.0f;
                m_isShaking = false;
                m_shakeTimer = 0.0f;
            }

            float power = m_shakePower * (1.0f - progress);

            float randX = static_cast<float>((std::rand() % 2001) - 1000) / 1000.0f;
            float randY = static_cast<float>((std::rand() % 2001) - 1000) / 1000.0f;

            cameraPos.x += randX * power;
            cameraPos.y += randY * power;
        }

        m_cam2D->SetCameraPostion(cameraPos);
	}
	void CameraController::CameraShake(float shakePower)
	{
        m_shakePower = shakePower;
		m_isShaking = true;
		m_shakeTimer = 0.0f;
	}

	void CameraController::SetTarget(GameObject* target)
	{
		m_target = target->GetComponent<Transform>();
	}

}
