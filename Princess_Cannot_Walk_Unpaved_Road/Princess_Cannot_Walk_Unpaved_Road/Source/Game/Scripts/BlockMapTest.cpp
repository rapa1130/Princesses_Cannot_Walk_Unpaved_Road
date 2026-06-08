#include "BlockMapTest.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Components/BlockMap/BlockMap.h"
#include"Engine/Scene/Scene.h"
#include <iostream>

namespace Bisang
{
	void BlockMapTest::Start()
	{
		GameObject* bObj = m_scene->FindGameObjectByName("BlockMap");
		m_blockMap = bObj->GetComponent<BlockMap>();
		m_input = m_scene->GetInputManager();
	}

	void BlockMapTest::Update(float dT)
	{
		if (m_input->IsKeyDown(KeyCode::A))
		{
			m_blockMap->SetAngle(m_blockMap->GetAngle().x - dT * addPower, m_blockMap->GetAngle().y);
		}
		else if (m_input->IsKeyDown(KeyCode::S))
		{
			m_blockMap->SetAngle(m_blockMap->GetAngle().x , m_blockMap->GetAngle().y - dT * addPower);
		}
		else if (m_input->IsKeyDown(KeyCode::D))
		{
			m_blockMap->SetAngle(m_blockMap->GetAngle().x + dT * addPower, m_blockMap->GetAngle().y);
		}
		else if (m_input->IsKeyDown(KeyCode::W))
		{
			m_blockMap->SetAngle(m_blockMap->GetAngle().x, m_blockMap->GetAngle().y + dT * addPower);
		}

		float width = m_blockMap->GetBlockWidth();
		float height = m_blockMap->GetBlockHeight();
		float depth = m_blockMap->GetBlockDepth();

		if (m_input->IsKeyDown(KeyCode::G))
		{
			m_blockMap->SetBlockSize(width + dT* addPower, height + dT * addPower, depth + dT * addPower);

		}
		else if (m_input->IsKeyDown(KeyCode::H))
		{
			m_blockMap->SetBlockSize(width - dT* addPower, height - dT * addPower, depth - dT * addPower);

		}

		std::cout << m_blockMap->GetAngle().x << " " << m_blockMap->GetAngle().y << std::endl;
		std::cout << m_blockMap->GetBlockWidth() << " " << m_blockMap->GetBlockHeight() << " " << m_blockMap->GetBlockDepth() << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

	}

	void BlockMapTest::FixedUpdate()
	{
		// GameApp에서 설정된 고정 프레임 간격으로 호출
	}
}