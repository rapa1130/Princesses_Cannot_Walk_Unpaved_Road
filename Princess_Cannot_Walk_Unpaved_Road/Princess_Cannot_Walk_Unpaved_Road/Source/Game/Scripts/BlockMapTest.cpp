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
			m_blockMap->SetAngle(m_blockMap->GetAngle().x - dT * addPower, m_blockMap->GetAngle().y, m_blockMap->GetTheta());
		}
		else if (m_input->IsKeyDown(KeyCode::S))
		{
			m_blockMap->SetAngle(m_blockMap->GetAngle().x , m_blockMap->GetAngle().y - dT * addPower, m_blockMap->GetTheta());
		}
		else if (m_input->IsKeyDown(KeyCode::D))
		{
			m_blockMap->SetAngle(m_blockMap->GetAngle().x + dT * addPower, m_blockMap->GetAngle().y, m_blockMap->GetTheta());
		}
		else if (m_input->IsKeyDown(KeyCode::W))
		{
			m_blockMap->SetAngle(m_blockMap->GetAngle().x, m_blockMap->GetAngle().y + dT * addPower, m_blockMap->GetTheta());
		}

		float width = m_blockMap->GetBlockWidth();
		float height = m_blockMap->GetBlockHeight();
		float depth = m_blockMap->GetBlockDepth();

		if (m_input->IsKeyDown(KeyCode::T))
		{
			m_blockMap->SetBlockSize(width + dT* addPower, height , depth );

		}
		else if (m_input->IsKeyDown(KeyCode::Y))
		{
			m_blockMap->SetBlockSize(width - dT* addPower, height , depth );
		}
		else if (m_input->IsKeyDown(KeyCode::U))
		{
			m_blockMap->SetBlockSize(width, height , depth + dT * addPower);
		}
		else if (m_input->IsKeyDown(KeyCode::I))
		{
			m_blockMap->SetBlockSize(width , height , depth - dT * addPower);
		}
		else if (m_input->IsKeyDown(KeyCode::O))
		{
			m_blockMap->SetBlockSize(width, height + dT * addPower, depth );
		}
		else if (m_input->IsKeyDown(KeyCode::P))
		{
			m_blockMap->SetBlockSize(width, height - dT * addPower, depth );
		}

		if (m_input->IsKeyDown(KeyCode::J))
		{
			m_blockMap->SetAngle(m_blockMap->GetAngle().x, m_blockMap->GetAngle().y, m_blockMap->GetTheta() + dT * addPower);
		}
		if (m_input->IsKeyDown(KeyCode::K))
		{
			m_blockMap->SetAngle(m_blockMap->GetAngle().x, m_blockMap->GetAngle().y, m_blockMap->GetTheta() - dT * addPower);
		}


		// Yaw
		// Pitch
		// Theta
		// BlockWidth
		// BlockHeight
		// BlockDepth
		
		std::cout << "Yaw    : " << m_blockMap->GetAngle().x << std::endl;
		std::cout << "Pitch  : " << m_blockMap->GetAngle().y << std::endl;
		std::cout << "theta  : " << m_blockMap->GetTheta() << std::endl;
		std::cout << "width  : " << m_blockMap->GetBlockWidth() << std::endl;
		std::cout << "height : " << m_blockMap->GetBlockHeight() << std::endl;
		std::cout << "depth  : " << m_blockMap->GetBlockDepth() << std::endl;

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;

	}

	void BlockMapTest::FixedUpdate()
	{
		// GameApp에서 설정된 고정 프레임 간격으로 호출
	}
}