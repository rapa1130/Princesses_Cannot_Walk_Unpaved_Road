#include "MonsterController.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/SpriteRenderer.h"
#include "Engine/Core/Layer.h"
#include "Game/Scripts/Blocks/BlockId.h"
#include "Game/Scripts/Camera/CameraController.h"
#include "Engine/Math/Math.h"

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

		m_camCtrl = FindGameObjectByName("Camera")->GetComponent<CameraController>();

		SetWorldPosbyBlockY(-100);
		SetMoveTerm(1.5f);
		SetLeapDistance(6);
		SetJumpHeight(60.0f);
		SetJumpDuration(0.7f);
		SetDestructRangeY(3);

		SetMinShakeDistY(300);
		SetShakePower(500.0f);
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
			ShakeCameraByDist();
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

	void MonsterController::ShakeCameraByDist()
	{
		if (!m_camCtrl || !m_transform)
			return;

		Transform* camTransform = m_camCtrl->GetOwner()->GetComponent<Transform>();
		if (!camTransform)
			return;

		Vector3 camPos = camTransform->GetPosition();
		Vector3 monsterPos = m_transform->GetPosition();

		float distY = std::abs(monsterPos.y - camPos.y);

		if (distY >= m_minShakeDistY)
			return;
		if (distY == 0) distY = 0.01f;

		float shakeRatio = 1.0f / distY ;
		shakeRatio = Bisang::fClamp(shakeRatio, 0, 300.0f);
		float shakePower = m_shakePower * shakeRatio;
		m_camCtrl->CameraShake(shakePower); 
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
	void MonsterController::SetMinShakeDistY(int minShakeDistY)
	{
		m_minShakeDistY = minShakeDistY;
	}
	void MonsterController::SetShakePower(int shakePower)
	{
		m_shakePower = shakePower;
	}
}