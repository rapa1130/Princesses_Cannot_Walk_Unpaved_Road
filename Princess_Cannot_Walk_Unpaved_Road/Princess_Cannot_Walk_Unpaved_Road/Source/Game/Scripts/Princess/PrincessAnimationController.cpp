#include "PrincessAnimationController.h"

#include "Engine/Object/GameObject.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Components/Animation/Animator.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Resource/TextureResource.h"

#include "Game/Scripts/Player/PlayerStatus.h"
#include "Game/Scripts/Princess/PrincessController.h"

namespace Bisang
{
    void PrincessAnimationController::Start()
    {
        m_input = GetInputManager();
        m_animator = m_ownerObj->GetComponent<Animator>();
        m_prinController = m_ownerObj->GetComponent<PrincessController>();

        InitializeAnimator();
    }

    void PrincessAnimationController::Update(float dT)
    {
        UpdateAnimation();
    }

    void PrincessAnimationController::InitializeAnimator()
    {
        if (m_animator == nullptr)
            return;

        for (int i = 0; i < PrincessAnimCount; ++i)
        {
            AnimationClip clip;
            clip.name = m_nameArr[i];
            clip.loop = true;
            clip.frames.push_back({
                     GetResourceManager()->LoadTexture(
                         L"Assets/Textures/Characters/Princess/Princess_" + m_nameArr[i] + L".png")
                });

            m_animator->AddClip(clip);
        }

        m_animator->Play();
    }

    void PrincessAnimationController::UpdateAnimation()
    {
        if (m_input == nullptr || m_animator == nullptr)
            return;

        Int3 dir = m_prinController->GetMoveDirection();
        

        bool isFront = dir.x < 0;
        bool isBack = dir.x > 0;
        bool isLeft = dir.y < 0;
        bool isRight = dir.y > 0;

        if (isBack)         m_animator->SetClip(L"Back");
        else if (isFront)   m_animator->SetClip(L"Front");
        else if (isLeft)    m_animator->SetClip(L"Right");
        else if (isRight)   m_animator->SetClip(L"Left");

    }
}