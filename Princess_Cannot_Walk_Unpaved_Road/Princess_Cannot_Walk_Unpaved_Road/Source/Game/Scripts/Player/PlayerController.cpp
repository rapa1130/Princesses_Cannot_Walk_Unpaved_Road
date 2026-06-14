#include "PlayerController.h"

#include "Engine/Core/Debug.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Components/SpriteRenderer.h"
#include "Engine/Components/Collider/BoxCollider.h"
#include "Engine/Components/Animation/Animator.h"

#include "Game/Scripts/Blocks/BlockInfoProvider.h"
#include "Game/Scripts/Blocks/BlockObjectInfoTable.h"

#include <iostream>

namespace Bisang
{
	void PlayerController::Start()
	{
		m_transform = m_ownerObj->GetComponent<Transform>();
		m_input = GetInputManager();
		m_blockMap = FindGameObjectByName("BlockMap")->GetComponent<BlockMap>();

        //moveSpeed = 300;
        m_maxSpeed = 200.f;
        m_acceleration = 3000.f;
        m_friction = 1000.0f;
        m_velocity = { 0,0,0 };

        SetToStartPostion();

        // BlockInfoTable 참조
        BlockObjectInfoProvider* blockObjectInfoProvider = 
            FindGameObjectByName("BlockMap")
            ->GetComponent<BlockObjectInfoProvider>();

        m_blockObjectInfoTable = blockObjectInfoProvider->GetTable();

        m_BoxCol = m_ownerObj->GetComponent<BoxCollider>();
        m_spriteRenderer = m_ownerObj->GetComponent<SpriteRenderer>();

	}

    void PlayerController::Update(float dT)
    {
        Move(dT);
    }

    void PlayerController::FixedUpdate() {}


    void PlayerController::Move(float dT)
    {
        UpdateVelocity(dT);

        float speed = m_velocity.Length();

        if (speed > m_maxSpeed)
        {
            m_velocity = m_velocity.Normalized() * m_maxSpeed;
        }

        Vector3 step = m_velocity * dT;

        if (step.Length() <= 0.0f)
            return;

        Vector3 nowPos = m_transform->GetPosition();

        if (CanMoveBoxArea(nowPos + step))
        {
            m_transform->Translate(step);
            return;
        }

        Vector2 axisX2 = m_blockMap->GetAxisX().Normalized();
        Vector2 axisY2 = m_blockMap->GetAxisY().Normalized();

        Vector3 axisX(axisX2.x, axisX2.y, 0.0f);
        Vector3 axisY(axisY2.x, axisY2.y, 0.0f);

        Vector2 step2D(step.x, step.y);

        Vector2 stepAxisX2 = axisX2 * Vector2::Dot(axisX2, step2D);
        Vector2 stepAxisY2 = axisY2 * Vector2::Dot(axisY2, step2D);

        Vector3 moveX(stepAxisX2.x, stepAxisX2.y, 0.0f);
        Vector3 moveY(stepAxisY2.x, stepAxisY2.y, 0.0f);


        bool movedX = false;
        bool movedY = false;

        if (CanMoveBoxArea(nowPos + moveX))
        {
            m_transform->Translate(moveX);
            nowPos = m_transform->GetPosition();
            movedX = true;
        }

        if (CanMoveBoxArea(nowPos + moveY))
        {
            m_transform->Translate(moveY);
            movedY = true;
        }

        if (!movedX)
        {
            float vDotX = m_velocity.x * axisX.x + m_velocity.y * axisX.y;
            m_velocity -= axisX * vDotX;
        }

        if (!movedY)
        {
            float vDotY = m_velocity.x * axisY.x + m_velocity.y * axisY.y;
            m_velocity -= axisY * vDotY;
        }
    }

    void PlayerController::UpdateVelocity(float dT)
    {
        const float stopThreshold = 0.01f;

        Vector3 inputDir{ 0.0f, 0.0f, 0.0f };

        if (m_input->IsKeyDown(KeyCode::Left))
        {
            Vector2 axis = m_blockMap->GetAxisY() * -1.0f;
            inputDir += Vector3(axis.x, axis.y, 0.0f);
        }

        if (m_input->IsKeyDown(KeyCode::Right))
        {
            Vector2 axis = m_blockMap->GetAxisY();
            inputDir += Vector3(axis.x, axis.y, 0.0f);
        }

        if (m_input->IsKeyDown(KeyCode::Up))
        {
            Vector2 axis = m_blockMap->GetAxisX();
            inputDir += Vector3(axis.x, axis.y, 0.0f);
        }

        if (m_input->IsKeyDown(KeyCode::Down))
        {
            Vector2 axis = m_blockMap->GetAxisX() * -1.0f;
            inputDir += Vector3(axis.x, axis.y, 0.0f);
        }

        if (m_input->IsKeyPressed(KeyCode::Space))
        {
            Instantiate("Player");
        }

        if (m_input->IsKeyPressed(KeyCode::Backspace))
        {
            Destory(FindGameObjectByName("Player"));
        }

        bool hasInput = inputDir.Length() > 0.0f;

        if (hasInput)
        {
            inputDir.Normalize();

            Vector3 accel = inputDir * m_acceleration;
            m_velocity += accel * dT;
        }
        else
        {
            // 입력이 없으면 감속
            float speed = m_velocity.Length();

            if (speed > 0.0f)
            {
                Vector3 velocityDir = m_velocity.Normalized();

                speed -= m_friction * dT;

                if (speed < stopThreshold)
                {
                    speed = 0.0f;
                }

                m_velocity = velocityDir * speed;
            }
        }
    }

    bool PlayerController::CanMoveBoxArea(const Vector3& center)
    {
        Vector2 axisX2 = m_blockMap->GetAxisX().Normalized();
        Vector2 axisY2 = m_blockMap->GetAxisY().Normalized();

        Vector3 axisX(axisX2.x, axisX2.y, 0.0f);
        Vector3 axisY(axisY2.x, axisY2.y, 0.0f);


        Vector2 colSize = m_BoxCol->GetSize();
        if (!CanMoveTo(center))
            return false;

        if (!CanMoveTo(center + axisX * colSize.x + axisY * colSize.y))
            return false;

        if (!CanMoveTo(center + axisX * colSize.x - axisY * colSize.y))
            return false;

        if (!CanMoveTo(center - axisX * colSize.x + axisY * colSize.y))
            return false;

        if (!CanMoveTo(center - axisX * colSize.x - axisY * colSize.y))
            return false;

        return true;
    }

	bool PlayerController::CanMoveTo(const Vector3& worldPos) const
	{
		Int3 blockPos;
		if (false == m_blockMap->WorldToBlock(worldPos, blockPos, playerZ))
		{
			return false;
		}
		
        BlockObject* block;

		// BlockMap에서 블럭 id 조회
		block = m_blockMap->GetBlock(blockPos);

        // 블럭 id로 info 조회
        BlockObjectInfo info = m_blockObjectInfoTable->Get(static_cast<BlockId>(block->id));

        // 벽 확인
		if (info.isSolid) return false;


        // 바닥 확인
        Int3 belowPos = blockPos + Int3{ 0, 0, -1 };
        block = m_blockMap->GetBlock(belowPos);
        info = m_blockObjectInfoTable->Get(static_cast<BlockId>(block->id));

        if (false == info.isSolid) return false;

		return true;
	}

	void PlayerController::SetToStartPostion()
	{
        Int3 startBlockPos = { 15, 10, 1 };
		Vector3 startWorldPos = m_blockMap->BlockToWorld(startBlockPos);
		m_transform->SetPosition(startWorldPos);
	}
}