#pragma once

#include "Engine/Components/Script.h"

#include <string>

#define PlayerAnimCount 16

namespace Bisang
{
    class InputManager;
    class Animator;
    class PlayerStatus;
    class PlayerController;

    class PlayerAnimationController : public Script
    {
    public:
        PlayerAnimationController(GameObject* ownerObj) : Script(ownerObj) {}

        void Start() override;
        void Update(float dT) override;

    private:
        void InitializeAnimator();
        void UpdateAnimation();

    private:
        Animator* m_animator = nullptr;
        PlayerController* m_controller = nullptr;
        PlayerStatus* m_playerStatus = nullptr;

        std::wstring m_nameArr[PlayerAnimCount] =
        {
            L"FrontLeft",
            L"FrontRight",
            L"BackLeft",
            L"BackRight",
            L"Front",
            L"Back",
            L"Left",
            L"Right",
            L"HandsUp_FrontLeft",
            L"HandsUp_FrontRight",
            L"HandsUp_BackLeft",
            L"HandsUp_BackRight",
            L"HandsUp_Front",
            L"HandsUp_Back",
            L"HandsUp_Left",
            L"HandsUp_Right"
        };
    };
}