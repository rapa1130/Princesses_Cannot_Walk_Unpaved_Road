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
#include "Game/Scripts/Player/PlayerStatus.h"
#include "Game/Scripts/Audio/AudioManager.h"
#include "Game/Scripts/Highlighter/Highlighter.h"

#include <iostream>

namespace Bisang
{
	void PlayerController::Start()
	{
        m_input = GetInputManager();
		m_transform = m_ownerObj->GetComponent<Transform>();
		m_blockMap = FindGameObjectByName("BlockMap")->GetComponent<BlockMap>();
        m_BoxCol = m_ownerObj->GetComponent<BoxCollider>();
        m_spriteRenderer = m_ownerObj->GetComponent<SpriteRenderer>();
        m_playerStatus = m_ownerObj->GetComponent<PlayerStatus>();
        m_audio = FindGameObjectByName("AudioManager")
            ->GetComponent<AudioManager>();

        // BlockInfoTable 참조
        BlockObjectInfoProvider* blockObjectInfoProvider = 
            FindGameObjectByName("BlockMap")
            ->GetComponent<BlockObjectInfoProvider>();

        m_blockObjectInfoTable = blockObjectInfoProvider->GetTable();

        UpdateCurrentPos();

        //m_highlighter = FindGameObjectByName("Highlighter")->GetComponent<Highlighter>();
	}

    void PlayerController::Update(float dT)
    {
        Move(dT);
        UpdateCurrentPos();

        Int3 interactableBlockPos;
        BlockId interatableBlockID;

        //int x = (int)m_faceDir.x;
        //int y = (int)m_faceDir.y;
        //Int3 FacePos = m_currentPos + Int3(-y,x,0);
        // m_highlighter->SetHighlightBlock(FacePos, BlockId::Dirt);
        
        bool bExistInteract = UpdateInteratable(interactableBlockPos,interatableBlockID);
        //m_highlighter->SetHighlightBlock(interactableBlockPos, interatableBlockID);
        Interact(interactableBlockPos);

        if(bExistInteract)
        {
            m_highlighter->SetHighlightBlock(interactableBlockPos, interatableBlockID);
        }
        else
        {
            m_highlighter->SetHighlightBlock(Int3(), BlockId::Empty);
        }
    }


    //*************************************************
    // 이동
    //************************************************* 

    

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
            float vDotY = m_velocity.x * axisY.x + m_velocity.y * axisY.y;

            m_velocity -= axisX * vDotX;
            m_velocity -= axisY * vDotY * m_collisionFrictionMultiplier;
        }

        if (!movedY)
        {
            float vDotX = m_velocity.x * axisX.x + m_velocity.y * axisX.y;
            float vDotY = m_velocity.x * axisY.x + m_velocity.y * axisY.y;
            m_velocity -= axisY * vDotY;
            m_velocity -= axisX * vDotX * m_collisionFrictionMultiplier;
        }
    }

    void PlayerController::UpdateVelocity(float dT)
    {
        const float stopThreshold = 0.01f;

        Vector3 inputDir{ 0.0f, 0.0f, 0.0f };
        Vector2 faceDir = { 0, 0 };

        bool left = m_input->IsKeyDown(KeyCode::Left);
        bool right = m_input->IsKeyDown(KeyCode::Right);
        bool up = m_input->IsKeyDown(KeyCode::Up);
        bool down = m_input->IsKeyDown(KeyCode::Down);

        int inputCount = 0;
        if (left)  inputCount++;
        if (right) inputCount++;
        if (up)    inputCount++;
        if (down)  inputCount++;

        if (inputCount > 2)
        {
            left = false;
            right = false;
            up = false;
            down = false;
        }

        if (left)
        {
            Vector2 axis = m_blockMap->GetAxisY() * -1.0f;
            inputDir += Vector3(axis.x, axis.y, 0.0f);
            faceDir += Vector2(-1, 0);
        }

        if (right)
        {
            Vector2 axis = m_blockMap->GetAxisY();
            inputDir += Vector3(axis.x, axis.y, 0.0f);
            faceDir += Vector2(1, 0);
        }

        if (up)
        {
            Vector2 axis = m_blockMap->GetAxisX();
            inputDir += Vector3(axis.x, axis.y, 0.0f);
            faceDir += Vector2(0, -1);
        }

        if (down)
        {
            Vector2 axis = m_blockMap->GetAxisX() * -1.0f;
            inputDir += Vector3(axis.x, axis.y, 0.0f);
            faceDir += Vector2(0, 1);
        }

        if (faceDir != Vector2{0, 0})
        {
            m_faceDir = faceDir;
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
		if (false == m_blockMap->WorldToBlock(worldPos, blockPos, m_playerZ))
		{
			return false;
		}
		
        int block;

		// BlockMap에서 블럭 id 조회
		block = m_blockMap->GetBlock(blockPos);

        // 블럭 id로 info 조회
        BlockObjectInfo info = m_blockObjectInfoTable->Get(static_cast<BlockId>(block));

        // 벽 확인
		if (info.isSolid) return false;


        // 바닥 확인
        Int3 belowPos = blockPos + Int3{ 0, 0, -1 };
        block = m_blockMap->GetBlock(belowPos);
        info = m_blockObjectInfoTable->Get(static_cast<BlockId>(block));

        if (false == info.isSolid) return false;

		return true;
	}

    void PlayerController::UpdateCurrentPos()
    {
        Int3 pos;
        if (false == m_blockMap->WorldToBlock(
            m_transform->GetPosition(),
            pos,
            m_playerZ
        )) return;

        m_currentPos = pos;
    }


    bool PlayerController::UpdateInteratable(Int3& blockPos,BlockId& outBlockID)
    {
        Vector2 faceDir = m_faceDir;
        if (faceDir == Vector2{ 1,-1 } ||
            faceDir == Vector2{ -1,-1 } ||
            faceDir == Vector2{ 1,1 } ||
            faceDir == Vector2{ -1,1 })
        {
            blockPos = m_currentPos;
            return false;
        }
        Int3 fwdPos = m_currentPos + Int3(-m_faceDir.y, m_faceDir.x, 0);
        Int3 fwdDownPos = fwdPos + Int3(0, 0, -1);

        BlockId currentBlock = static_cast<BlockId>(m_blockMap->GetBlock(m_currentPos));
        BlockId fwdBlock = static_cast<BlockId>(m_blockMap->GetBlock(fwdPos));
        BlockId fwdDownBlock = static_cast<BlockId>(m_blockMap->GetBlock(fwdDownPos));
        BlockId heldBlock = m_playerStatus->GetHeldBlockObj();

        if (heldBlock == BlockId::Empty)
        {
            switch (currentBlock)
            {
                case BlockId::Axe:
                case BlockId::PickAxe:
                case BlockId::Hammer:
                case BlockId::ClayResource:
                case BlockId::TreeResource:

                    blockPos = m_currentPos;
                    outBlockID = currentBlock;
                    return true;
            }
            switch (fwdBlock)
            {
                case BlockId::Axe:
                case BlockId::PickAxe:
                case BlockId::Hammer:
                case BlockId::ClayResource:
                case BlockId::TreeResource:

                    blockPos = fwdPos;
                    outBlockID = fwdBlock;
                    return true;
            }
        }

        else if(heldBlock == BlockId::Axe)
        {
            switch (fwdBlock)
            {
                case BlockId::Tree:
                case BlockId::OrcTree:
                    blockPos = fwdPos;
                    outBlockID = fwdBlock;
                    return true;
            }
            
            blockPos = m_currentPos;
            outBlockID = BlockId::Empty;
            return true;
        }

        else if (heldBlock == BlockId::PickAxe)
        {
            switch (fwdBlock)
            {
            case BlockId::Clay:
                blockPos = fwdPos;
                outBlockID = fwdBlock;
                return true;
            }

            blockPos = m_currentPos;
            outBlockID = BlockId::Empty;
            return true;

        }

        else if (heldBlock == BlockId::Hammer)
        {
            switch (currentBlock)
            {
            case BlockId::ClayResource:
                blockPos = m_currentPos;
                outBlockID = BlockId::RailPath;
                return true;
            }
            switch (fwdBlock)
            {
            case BlockId::ClayResource:
                blockPos = fwdPos;
                outBlockID = BlockId::RailPath;
                return true;
            }
            blockPos = m_currentPos;
            outBlockID = BlockId::Empty;
            return true;
        }
        else if (heldBlock == BlockId::ClayResource)
        {
            blockPos = m_currentPos;
            outBlockID = BlockId::Empty;
            return true;
        }
        else if (heldBlock == BlockId::TreeResource)
        {
            switch (fwdDownBlock)
            {
            case BlockId::Water:
                blockPos = fwdDownPos;
                outBlockID = BlockId::WoodBridge;
                return true;
            default:
                blockPos = m_currentPos;
                outBlockID = BlockId::Empty;
                return true;
            }
        }

        return false;
    }

    //*************************************************
    // 상호작용
    //************************************************* 

    void PlayerController::Interact(const Int3& blockPos)
    {
        if (false == m_input->IsKeyPressed(KeyCode::Space)) return;

        // 월드 -> 블럭맵 좌표 변환
        //Vector3 vCurrentPos = m_transform->GetPosition();
        //Int3 currentPos;
        //if (false == m_blockMap->WorldToBlock(vCurrentPos, currentPos, m_playerZ))
        //{
        //    return;
        //}

        // 현재 위치 블럭 오브젝트 조회
        int bObj = m_blockMap->GetBlock(blockPos);
        BlockObjectInfo info = m_blockObjectInfoTable->Get(static_cast<BlockId>(bObj));


        // 도구면 착용
        if ( info.kind == BlockObjectKind::Tool ||
             info.kind == BlockObjectKind::Material )
        {
            // 현재 손에 들고 있는 오브젝트 검사
            BlockId heldBObj = m_playerStatus->GetHeldBlockObj();
            
            // 착용
            m_playerStatus->PickUp(info.id);
            m_audio->PlayPickUpSound();

            if (heldBObj == BlockId::Empty)
            {
                m_blockMap->RemoveBlock(blockPos);
            }

            else
            {
                m_blockMap->SetBlock(
                    blockPos,
                    static_cast<int>(heldBObj)
                );
            }
        }

        if (info.id == BlockId::Empty)
        {
            // 현재 손에 들고 있는 오브젝트 검사
            BlockId heldBObj = m_playerStatus->GetHeldBlockObj();

            if (heldBObj != BlockId::Empty)
            {
                m_blockMap->SetBlock(
                    blockPos,
                    static_cast<int>(heldBObj)
                );

                m_playerStatus->PutDown();
                m_audio->PlayPutDownSound();
            }
        }

    }

}