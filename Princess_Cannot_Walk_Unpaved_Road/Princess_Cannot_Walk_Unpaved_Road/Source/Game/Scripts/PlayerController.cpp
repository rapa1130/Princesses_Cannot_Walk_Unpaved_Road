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
		SetToStartPostion();
	}

	void PlayerController::Update(float dT)
	{
		Vector3 playerPos = m_transform->GetPosition();
		Int3 blockPos;
		if (false != m_blockMap->WorldToBlock(playerPos, blockPos, playerZ))
		{
			std::cout << "서있는 블럭위치 블럭위치 ( " << blockPos.x << ", " << blockPos.y << ", " << blockPos.z << " )" << std::endl;
		}
		Block* block = m_blockMap->GetBlock(blockPos);
		std::cout << (int)block->blockId << std::endl;

		m_dir = { 0, 0 };

		if (m_input->IsKeyDown(KeyCode::Left))
		{
			m_dir += (m_blockMap->GetAxisY() * -1);
		}
		if (m_input->IsKeyDown(KeyCode::Right))
		{
			m_dir += m_blockMap->GetAxisY();
		}
		if (m_input->IsKeyDown(KeyCode::Up))
		{
			m_dir += m_blockMap->GetAxisX();
		}
		if (m_input->IsKeyDown(KeyCode::Down))
		{
			m_dir += (m_blockMap->GetAxisX() * -1);
		}

		m_dir.Normalize();

		Vector3 step = Vector3(m_dir.x, m_dir.y, 0) * moveSpeed * dT;

		if (CanMoveTo(m_transform->GetPosition() + step))
		{
			m_transform->Translate(step);
		}
	}

	void PlayerController::FixedUpdate() {}

	bool PlayerController::CanMoveTo(const Vector3& worldPos) const
	{
		Int3 blockPos;
		if (false == m_blockMap->WorldToBlock(worldPos, blockPos, playerZ))
		{
			return false;
		}
		
		// 바닥 확인
		Block* block = m_blockMap->GetBlock(blockPos + Int3{ 0, 0, -1});
		
		if (block == nullptr ) return false;

		switch (block->blockId)
		{
		case  BlockId::Empty:
		case  BlockId::Water:
			return false;
		}


		// 벽 확인
		block = m_blockMap->GetBlock(blockPos);
		std::cout << "가려는 블럭위치 블럭위치 ( " << blockPos.x << ", " << blockPos.y << ", " << blockPos.z << " )" << std::endl;
		std::cout << (int)block->blockId << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

		if (block == nullptr)
		{
			return false;
		}

		switch (block->blockId)
		{
		case BlockId::Grass:
		case BlockId::Clay:
		case BlockId::Rock:
		case BlockId::Tree:
		case BlockId::OrcTree:
			return false;
		}
 		
		return true;
	}

	void PlayerController::SetToStartPostion()
	{
		Int3 startBlockPos = m_blockMap->GetStartPosition();
		Vector3 startWorldPos = m_blockMap->BlockToWorld(startBlockPos);
		m_transform->SetPosition(startWorldPos);
	}


}