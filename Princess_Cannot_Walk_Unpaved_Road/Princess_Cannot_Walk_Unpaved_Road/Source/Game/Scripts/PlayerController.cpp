#include "PlayerController.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Core/Debug.h"
#include "Engine/Components/BlockMap/BlockMap.h"
#include <iostream>
#include "Engine/Prefab/PrefabFactory.h"
#include "Engine/Components/SpriteRenderer.h"


namespace Bisang
{
	void PlayerController::Start()
	{
		
		m_transform = m_ownerObj->GetComponent<Transform>();
		m_input = GetInputManager();
		m_blockMap = FindGameObjectByName("BlockMap")->GetComponent<BlockMap>();
		SetToStartPostion();
		m_velocity = { 0,0,0 };
		
		//moveSpeed = 300;
		m_maxSpeed = 200.f;
		m_acceleration = 3000.f;
        m_friction = 1000.0f;
        m_spriteRenderer = m_ownerObj->GetComponent<SpriteRenderer>();

	}

	void PlayerController::Update(float dT)
	{

		Move(dT);
        UpdateAnimation();
        
	}


	void PlayerController::FixedUpdate() {}


	void PlayerController::Move(float dT)
	{
        UpdateVelocity(dT);

        // 최대 속도 제한
        float speed = m_velocity.Length();

        if (speed > m_maxSpeed)
        {
            m_velocity = m_velocity.Normalized() * m_maxSpeed;
        }

        // 실제 이동량은 velocity * dT
        Vector3 step = m_velocity * dT;

        if (step.Length() <= 0.0f)
            return;

        Vector3 nowPos = m_transform->GetPosition();
        Vector3 nextPos = nowPos + step;

        if (CanMoveTo(nextPos))
        {
            m_transform->Translate(step);
        }
        else
        {
            Int3 nextBlockPos;
            if (false == m_blockMap->WorldToBlock(nextPos, nextBlockPos, playerZ))
            {
                DEBUG_ERROR("캐릭터 바라보는 방향에 블럭 없음");
                return;
            }
            
            Int3 nowBlockPos;
            if (false == m_blockMap->WorldToBlock(nowPos, nowBlockPos, playerZ))
            {
                DEBUG_ERROR("현재 캐릭터 위치에 블럭 없음");
                return;
            }

            Int3 deltaBlockPos = nextBlockPos - nowBlockPos;

            if (deltaBlockPos != Int3(0,0,0))
            {
                std::cout << deltaBlockPos.x << ", " << deltaBlockPos.y << ", " << deltaBlockPos.z << ", " << std::endl;
            }

            Vector2 xAxisNorm = m_blockMap->GetAxisX().Normalized();
            Vector2 yAxisNorm = m_blockMap->GetAxisY().Normalized();

            Vector2 stepAxisX = xAxisNorm *Vector2::Dot(xAxisNorm, step) ;
            Vector2 stepAxisY = yAxisNorm *Vector2::Dot(yAxisNorm, step) ;

            if (CanMoveTo(nowPos + stepAxisX))  m_transform->Translate(stepAxisX);
            if (CanMoveTo(nowPos + stepAxisY)) m_transform->Translate(stepAxisY);
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

    void PlayerController::UpdateAnimation()
    {
        bool isFront = m_input->IsKeyDown(KeyCode::Down);
        bool isBack = m_input->IsKeyDown(KeyCode::Up);
        bool isLeft = m_input->IsKeyDown(KeyCode::Left);
        bool isRight = m_input->IsKeyDown(KeyCode::Right);

        if (isFront && isLeft)
        {
            m_spriteRenderer->SetSprite(L"Assets/Textures/Characters/Player/Player_FrontLeft.png");
        }
        else if (isFront && isRight)
        {
            m_spriteRenderer->SetSprite(L"Assets/Textures/Characters/Player/Player_FrontRight.png");
        }
        else if (isBack && isLeft)
        {
            m_spriteRenderer->SetSprite(L"Assets/Textures/Characters/Player/Player_BackLeft.png");
        }
        else if (isBack && isRight)
        {
            m_spriteRenderer->SetSprite(L"Assets/Textures/Characters/Player/Player_BackRight.png");

        }
        else if (isBack)
        {
            m_spriteRenderer->SetSprite(L"Assets/Textures/Characters/Player/Player_Back.png");

        }
        else if (isFront)
        {
            m_spriteRenderer->SetSprite(L"Assets/Textures/Characters/Player/Player_Front.png");

        }
        else if (isLeft)
        {
            m_spriteRenderer->SetSprite(L"Assets/Textures/Characters/Player/Player_Right.png");

        }
        else if (isRight)
        {
            m_spriteRenderer->SetSprite(L"Assets/Textures/Characters/Player/Player_Left.png");

        }


        /*
        
        m_resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_Front.png")->SetPivot({ -20, -40, 0 });
        m_resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_Back.png")->SetPivot({ -20, -40, 0 });
        m_resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_Left.png")->SetPivot({ -20, -40, 0 });
        m_resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_Right.png")->SetPivot({ -20, -40, 0 });
        m_resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_BackLeft.png")->SetPivot({ -20, -40, 0 });
        m_resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_BackRight.png")->SetPivot({ -20, -40, 0 });
        m_resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_FrontLeft.png")->SetPivot({ -20, -40, 0 });
        m_resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_FrontRight.png")->SetPivot({ -20, -40, 0 });


        sr->SetSprite(L"Assets/Textures/Characters/Player/Player_Front.png");

        */

    }


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
		if (m_blockMap->IsWalkableFloor(block->blockId) == false) return false;

		// 벽 확인
		block = m_blockMap->GetBlock(blockPos);
		//std::cout << "가려는 블럭위치 블럭위치 ( " << blockPos.x << ", " << blockPos.y << ", " << blockPos.z << " )" << std::endl;
		//std::cout << (int)block->blockId << std::endl;
		//std::cout << std::endl;
		//std::cout << std::endl;
		//std::cout << std::endl;
		//std::cout << std::endl;
		//std::cout << std::endl;

		if (block == nullptr) return false;
		if (m_blockMap->IsBlocking(block->blockId)) return false;
 		
		return true;
	}

	void PlayerController::SetToStartPostion()
	{
		Int3 startBlockPos = m_blockMap->GetStartPosition();
		Vector3 startWorldPos = m_blockMap->BlockToWorld(startBlockPos);
		m_transform->SetPosition(startWorldPos);
	}


}