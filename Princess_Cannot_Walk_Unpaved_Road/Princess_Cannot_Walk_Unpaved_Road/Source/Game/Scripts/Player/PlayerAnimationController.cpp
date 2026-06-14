#include "PlayerAnimationController.h"

#include "Engine/Object/GameObject.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Components/Animation/Animator.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Resource/TextureResource.h"

#include "Game/Scripts/Player/PlayerStatus.h"

namespace Bisang
{
    void PlayerAnimationController::Start()
    {
        m_input = GetInputManager();
        m_animator = m_ownerObj->GetComponent<Animator>();
        m_playerStatus = m_ownerObj->GetComponent<PlayerStatus>();

        InitializeAnimator();
    }

    void PlayerAnimationController::Update(float dT)
    {
        UpdateAnimation();
    }

    void PlayerAnimationController::InitializeAnimator()
    {
        if (m_animator == nullptr)
            return;

        for (int i = 0; i < 16; ++i)
        {
            AnimationClip clip;
            clip.name = m_nameArr[i];
            clip.loop = true;

            if (i < 8)
            {
                clip.frames.push_back({
                    GetResourceManager()->LoadTexture(
                        L"Assets/Textures/Characters/Player/Default/Player_" + m_nameArr[i] + L".png")
                });
            }

            else
            {
                clip.frames.push_back({
                    GetResourceManager()->LoadTexture(
                        L"Assets/Textures/Characters/Player/HandsUp/Player_" + m_nameArr[i] + L".png")
                    });
            }


            m_animator->AddClip(clip);
        }

        m_animator->Play();
    }

    void PlayerAnimationController::UpdateAnimation()
    {
        if (m_input == nullptr || m_animator == nullptr)
            return;

        bool isFront = m_input->IsKeyDown(KeyCode::Down);
        bool isBack = m_input->IsKeyDown(KeyCode::Up);
        bool isLeft = m_input->IsKeyDown(KeyCode::Left);
        bool isRight = m_input->IsKeyDown(KeyCode::Right);
  
        if (m_playerStatus->GetHeldBlockObj() == BlockId::Empty)
        {
            if (isFront && isLeft)          m_animator->SetClip(L"FrontLeft");
            else if (isFront && isRight)    m_animator->SetClip(L"FrontRight");
            else if (isBack && isLeft)      m_animator->SetClip(L"BackLeft");
            else if (isBack && isRight)     m_animator->SetClip(L"BackRight");
            else if (isBack)                m_animator->SetClip(L"Back");
            else if (isFront)               m_animator->SetClip(L"Front");
            else if (isLeft)                m_animator->SetClip(L"Right");
            else if (isRight)               m_animator->SetClip(L"Left");
        }

        else
        {
            if (isFront && isLeft)          m_animator->SetClip(L"HandsUp_FrontLeft");
            else if (isFront && isRight)    m_animator->SetClip(L"HandsUp_FrontRight");
            else if (isBack && isLeft)      m_animator->SetClip(L"HandsUp_BackLeft");
            else if (isBack && isRight)     m_animator->SetClip(L"HandsUp_BackRight");
            else if (isBack)                m_animator->SetClip(L"HandsUp_Back");
            else if (isFront)               m_animator->SetClip(L"HandsUp_Front");
            else if (isLeft)                m_animator->SetClip(L"HandsUp_Right");
            else if (isRight)               m_animator->SetClip(L"HandsUp_Left");
        }
    }
}