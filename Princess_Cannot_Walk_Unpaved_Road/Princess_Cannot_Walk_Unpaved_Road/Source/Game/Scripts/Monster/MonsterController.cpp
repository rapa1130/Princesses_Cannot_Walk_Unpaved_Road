#include "MonsterController.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/SpriteRenderer.h"
#include "Engine/Core/Layer.h"
#include "Game/Scripts/Blocks/BlockId.h"

#include <iostream>

namespace Bisang
{
	void MonsterController::Start()
	{
		GameObject* bObj = FindGameObjectByName("BlockMap");
		m_blockMap = bObj->GetComponent<BlockMap>();
		m_transform = m_ownerObj->GetComponent<Transform>();

		m_spriteRenderer = m_ownerObj->GetComponent<SpriteRenderer>();
		m_spriteRenderer->SetLayer(Layer::Monster);
		m_transform->SetScale({ 0.75f,0.75f });

		SetWorldPosbyBlockY(-20);
		SetMoveTerm(1.5f);
		SetLeapDistance(6);
		SetJumpHeight(60.0f);
		SetJumpDuration(0.7f);
		SetDestructRangeY(3);
	}


	void MonsterController::Update(float dT)
	{
		Jump(dT);
	}

	void MonsterController::Jump(float dT)
	{
		static float waitTimer = 0.0f;

		if (!m_isJumping)
		{
			waitTimer += dT;

			if (waitTimer >= m_moveTerm)
			{
				waitTimer = 0.0f;

				m_jumpStartPos = m_transform->GetPosition();

				m_position.y += m_leapDistance;
				m_jumpTargetPos = m_blockMap->BlockToWorld(m_position);

				m_jumpTimer = 0.0f;
				m_isJumping = true;
			}

			return;
		}

		m_jumpTimer += dT;

		float t = m_jumpTimer / m_jumpDuration;

		if (t >= 1.0f)
		{
			t = 1.0f;
			m_isJumping = false;
			DestructArea();
		}

		Vector3 pos = m_jumpStartPos + (m_jumpTargetPos - m_jumpStartPos) * t;

		// 점프 높이. t가 0일 때 0, 0.5일 때 최대, 1일 때 다시 0
		float jumpOffset = std::sin(t * 3.141592f) * m_jumpHeight;

		pos.y -= jumpOffset;

		m_transform->SetPosition(pos);
	}

	void MonsterController::DestructArea()
	{
		int width = m_blockMap->GetWidth();
		for (int i = 0; i < width; i++)
		{
			int destructStartY = m_position.y - m_destructRangeY;
			int destructEndY = m_position.y + m_destructRangeY;
			for (int j = destructStartY; j < destructEndY; j++)
			{
				m_blockMap->SetBlock({ i,j,1 }, static_cast<int>(BlockId::Empty));
			}
		}
	}
	

	void MonsterController::SetWorldPosbyBlockY(int blockY)
	{
		m_position = { m_blockMap->GetWidth() / 2, blockY,1 };
		Vector3 worldPos = m_blockMap->BlockToWorld(m_position);
		m_transform->SetPosition(worldPos);
	}


	void MonsterController::SetMoveTerm(float moveTerm)
	{
		m_moveTerm = moveTerm;
	}
	void MonsterController::SetLeapDistance(int dist)
	{
		m_leapDistance = dist;
	}
	void MonsterController::SetJumpDuration(float duration)
	{
		m_jumpDuration = duration;
	}
	void MonsterController::SetJumpHeight(float height)
	{
		m_jumpHeight = height;
	}
	void MonsterController::SetDestructRangeY(int rangeY)
	{
		m_destructRangeY = rangeY;
	}
}