#include "PlayerController.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Core/Debug.h"
#include "Engine/Components/BlockMap/BlockMap.h"
#include <iostream>


namespace Bisang
{
	void PlayerController::Start()
	{
		m_transform = m_ownerObj->GetComponent<Transform>();
		m_input = m_scene->GetInputManager();
		m_blockMap = m_scene->FindGameObjectByName("BlockMap")->GetComponent<BlockMap>();
	}

	void PlayerController::Update(float dT)
	{
		m_dir = { 0, 0 };

		if (m_input->IsKeyDown(KeyCode::A))
		{
			m_dir += (m_blockMap->GetAxisY() * -1);
		}
		if (m_input->IsKeyDown(KeyCode::D))
		{
			m_dir += m_blockMap->GetAxisY();
		}
		if (m_input->IsKeyDown(KeyCode::W))
		{
			m_dir += m_blockMap->GetAxisX();
		}
		if (m_input->IsKeyDown(KeyCode::S))
		{
			m_dir += (m_blockMap->GetAxisX() * -1);
		}

		m_dir.Normalize();

		m_transform->Translate(Vector3(m_dir.x, m_dir.y, 0) * moveSpeed);


		///////////////////////////////////////////////////////////////////////////////////////////////////
		Vector3 blockPos = m_blockMap->BlockToWorld({ 1, 1 ,1 });
		Vector3 playerPos = m_transform->GetPosition();
		std::cout << "블럭위치 ( " << blockPos.x+100 << ", " << blockPos.y+700 << ", " << blockPos.z << " )" << std::endl;
		std::cout << "사람위치 ( " << playerPos.x << ", " << playerPos.y << ", " << playerPos.z << " )" << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
	}

	void PlayerController::FixedUpdate()
	{
		// GameApp에서 설정된 고정 프레임 간격으로 호출
	}
}