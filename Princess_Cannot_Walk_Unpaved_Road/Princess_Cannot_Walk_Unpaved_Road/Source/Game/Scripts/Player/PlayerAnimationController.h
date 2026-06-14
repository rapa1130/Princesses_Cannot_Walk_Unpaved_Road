#pragma once

#include "Engine/Components/Script.h"

#include <string>

#define PlayerAnimCount 8

namespace Bisang
{
    class InputManager;
    class Animator;

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
        InputManager* m_input = nullptr;
        Animator* m_animator = nullptr;

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
        };
    };
}