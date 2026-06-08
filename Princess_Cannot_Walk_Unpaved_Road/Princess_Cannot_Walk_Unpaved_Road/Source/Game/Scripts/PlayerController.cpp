#include "PlayerController.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Core/Debug.h"

namespace Bisang
{
	void PlayerController::Start()
	{
		m_transform = m_ownerObj->GetComponent<Transform>();
		m_input = m_scene->GetInputManager();
	}

	void PlayerController::Update(float dT)
	{
		
		if (m_input->IsKeyDown(KeyCode::A))
		{
			m_dir = { -1, 0, 0 };
			DEBUG_LOG("updating");
		}
		else if (m_input->IsKeyDown(KeyCode::S))
		{
			m_dir = { 0, 1, 0 };
		}
		else if (m_input->IsKeyDown(KeyCode::D))
		{
			m_dir = { 1, 0, 0 };
		}
		else if (m_input->IsKeyDown(KeyCode::W))
		{
			m_dir = { 0, -1, 0 };
		}
		else
		{
			m_dir = { 0,0,0 };
		}

		m_transform->Translate(m_dir * moveSpeed);
	}

	void PlayerController::FixedUpdate()
	{
		// GameApp에서 설정된 고정 프레임 간격으로 호출
	}
}